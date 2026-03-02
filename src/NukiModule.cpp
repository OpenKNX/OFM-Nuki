#include "NukiModule.h"
#include "BleScanner.h"
#include "NukiConstants.h"
#include "NukiOpenerChannel.h"
#include "NukiSmartLockChannel.h"
#include "driver/gpio.h"

#ifdef NUKI_ASYNC_LOOP1

#ifndef NUKI_LOOP1_STACK_SIZE
// 16 KB — BLE operations can be stack-heavy (ECDH + AES-CBC + HMAC). Larger stack needed to avoid overflows.
#define NUKI_LOOP1_STACK_SIZE 16384
#endif
// Static storage: stack in .bss, never on the heap.
static StackType_t nukiLoop1StackBuffer[NUKI_LOOP1_STACK_SIZE / sizeof(StackType_t)];
static StaticTask_t nukiLoop1TCB;
static void nukiModuleLoop1Task(void* param)
{
    auto* mod = static_cast<NukiModule*>(param);
    for (;;)
    {
        // Iterate all channels and call loopBle() on each NukiChannel.
        // loopBle() is framework-independent (runs on single-core and dual-core targets)
        // and is the only place where BLE work is done in NukiModule and its channels.
        uint8_t n = mod->getNumberOfChannels();
        for (uint8_t i = 0; i < n; i++)
        {
            auto* ch = static_cast<NukiChannel*>(mod->getChannel(i));
            if (ch != nullptr)
                ch->loopBle();
        }

        // Check if BLE scan duty cycle switch is requested by any channel (e.g. after initial state fetch).
        if (mod->_requestLowPowerScan)
        {
            mod->_requestLowPowerScan = false;
            auto bleScan = NimBLEDevice::getScan();
            if (bleScan != nullptr)
            {
                bleScan->setInterval(BLE_SCAN_INTERVAL_LP);
                bleScan->setWindow(BLE_SCAN_WINDOW_LP);
                printf("[NukiLP] BLE scan switched to low-power (%d/%d)\n",
                       BLE_SCAN_INTERVAL_LP, BLE_SCAN_WINDOW_LP);
            }
        }
#ifdef OPENKNX_DEBUG
        uint32_t iteration = 0;
        if (++iteration % 2000 == 0)
        {
            UBaseType_t hwm = uxTaskGetStackHighWaterMark(NULL);
            printf("[NukiHWM] NukiLoop1 stack: %u bytes free (configured=%d)\n",
                   (unsigned)hwm * sizeof(StackType_t), NUKI_LOOP1_STACK_SIZE);
            TaskHandle_t nimbleTask = xTaskGetHandle("nimble_host");
            if (nimbleTask != nullptr)
            {
                UBaseType_t nHwm = uxTaskGetStackHighWaterMark(nimbleTask);
                printf("[NukiHWM] NimBLE host stack: %u bytes free (configured=%d)\n",
                       (unsigned)nHwm * sizeof(StackType_t),
                       CONFIG_BT_NIMBLE_HOST_TASK_STACK_SIZE);
            }
            else
            {
                printf("[NukiHWM] NimBLE host task not found by name 'nimble_host'\n");
            }
            fflush(stdout);
        }
        ++iteration;
#endif
        vTaskDelay(1); // yield — allows KNX main loop to run between BLE ops
    }
}
#endif

const std::string NukiModule::name()
{
    return "Nuki";
}

void NukiModule::showInformations()
{
}

const std::string NukiModule::version()
{
#ifdef MODULE_Nuki_Version
    return MODULE_Nuki_Version;
#else
    // hides the module in the version output on the console, because the firmware version is sufficient.
    return "";
#endif
}

// class NukiLogger : public Print
// {
//     std::string buffer = "";
//     size_t write(uint8_t c) override
//     {
//         buffer += static_cast<char>(c);
//         if (c == '\n' || buffer.length() == OPENKNX_MAX_LOG_MESSAGE_LENGTH - 20)
//         {
//             logError("Nuki", "%s", buffer.c_str());
//             buffer = "";
//         }
//         return 1;
//     }
// };

// NukiLogger nukiLogger = NukiLogger();

void NukiModule::setup()
{
#ifdef OKNXHW_OPENKNXIAO_ESP32C6
    // XIAO ESP32-C6: FM8625H SP2T RF switch — pins from Xiao.h:
    //   OKNXHW_OPENKNXIAO_RF_POWER_PIN  (GPIO3)  LOW=switch ON,  HIGH=switch OFF
    //   OKNXHW_OPENKNXIAO_RF_SWITCH_PIN (GPIO14) LOW=internal PCB antenna, HIGH=external u.FL
    // Sequence: always power ON first, then select antenna.
    // Default: internal PCB antenna. Add -D NUKI_BLE_ANTENNA_EXTERNAL for external u.FL.
    // ToDo: OKNXHW_OPENKNXIAO_ESP32C6 interferences with KNX RX lane and NCN5130 EMI resets -> 0x17 bytes
    //       100 pF Capacitator from KNX_RX-Pin to GND on NanoBCU.
    gpio_reset_pin((gpio_num_t)OKNXHW_OPENKNXIAO_RF_POWER_PIN);
    gpio_set_direction((gpio_num_t)OKNXHW_OPENKNXIAO_RF_POWER_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level((gpio_num_t)OKNXHW_OPENKNXIAO_RF_POWER_PIN, 0); // switch power ON
#ifdef NUKI_BLE_ANTENNA_EXTERNAL
    const int _antSelect = 1; // RF2: Using external u.FL antenna
#else
    const int _antSelect = 0; // RF1: Using internal Ceramic PCB antenna
#endif
    gpio_reset_pin((gpio_num_t)OKNXHW_OPENKNXIAO_RF_SWITCH_PIN);
    gpio_set_direction((gpio_num_t)OKNXHW_OPENKNXIAO_RF_SWITCH_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level((gpio_num_t)OKNXHW_OPENKNXIAO_RF_SWITCH_PIN, _antSelect);
    logInfoP("OPENKNXIAO ESP32-C6 RF switch: power=GPIO%d(ON), select=GPIO%d=%d (%s antenna)",
             OKNXHW_OPENKNXIAO_RF_POWER_PIN, OKNXHW_OPENKNXIAO_RF_SWITCH_PIN,
             _antSelect, _antSelect ? "external u.FL" : "internal Ceramic PCB");
#endif
    NUKChannelOwnerModule::initialize(ParamNUK_VisibleChannels);
    NUKChannelOwnerModule::setup();

#ifdef NUKI_ASYNC_LOOP1
    xTaskCreateStatic(nukiModuleLoop1Task, "NukiLoop1",
                      NUKI_LOOP1_STACK_SIZE, // bytes (ESP-IDF FreeRTOS uses bytes)
                      this, 1,
                      nukiLoop1StackBuffer, &nukiLoop1TCB);
    logInfoP("All %d channel(s) loop1 running as single FreeRTOS task (stack=%d bytes, static .bss)",
             (int)getNumberOfChannels(), NUKI_LOOP1_STACK_SIZE);
#endif
    _bleInitDeadline = millis() + BLE_INIT_DELAY_MS;
    logDebugP("BLE scanner start deferred by %dms for supply stabilization", BLE_INIT_DELAY_MS);
}

void NukiModule::initializeBleScanner()
{
    // The NimBLE whitelist lives only in BLE controller RAM and is always empty after a
    // reboot — no explicit clear needed. Each channel's initialize() adds its paired address.
    for (uint8_t i = 0; i < getNumberOfUsedChannels(); i++)
    {
        auto channel = (NukiChannel*)getChannel(i);
        if (channel == nullptr)
            continue;
        if (scanner == nullptr)
        {
            logDebugP("Start Bluetooth Scanner");
            scanner = new BleScanner::Scanner();
            // Boot: 100% duty cycle (interval=window=23) for fast initial connection.
            // Switches to 30% in loop() once all paired channels have fetched their
            // state, or after 60s fallback (Nuki out of range / battery dead).
            scanner->initialize("blescanner", true, BLE_SCAN_INTERVAL_BOOT, BLE_SCAN_WINDOW_BOOT);
#ifdef NUKI_BLE_TX_POWER_DBM
            // Reduce BLE TX power after NimBLEDevice::init() to limit RF emissions
            if (NimBLEDevice::setPower(NUKI_BLE_TX_POWER_DBM))
                logInfoP("BLE TX power set to %d dBm (EMI reduction, default was +9 dBm)", (int)NUKI_BLE_TX_POWER_DBM);
            else
                logErrorP("BLE TX power set to %d dBm FAILED", (int)NUKI_BLE_TX_POWER_DBM);
#endif
            _initialStateFetchDeadline = millis() + BLE_INITIAL_STATE_TIMEOUT_MS;
        }
        logDebugP("Initialize channel %d", i);
        channel->initialize(*scanner);
    }

    // Activate HW whitelist filter after all channels have registered their addresses.
    // Only enable if at least one address is in the list — an empty whitelist with USE_WL
    // would block all advertisements.
    if (NimBLEDevice::getWhiteListCount() > 0)
    {
        logDebugP("Enabling BLE whitelist filter (%d address(es))", NimBLEDevice::getWhiteListCount());
        NimBLEDevice::getScan()->setFilterPolicy(BLE_HCI_SCAN_FILT_USE_WL);
    }
    else
    {
        logDebugP("No paired devices — BLE whitelist filter not activated");
    }
}

void NukiModule::loop()
{
    // Deferred BLE startup: wait for supply to stabilize before starting the BLE stack.
    if (_bleInitDeadline != 0 && millis() >= _bleInitDeadline)
    {
        _bleInitDeadline = 0;
        logDebugP("Boot stabilization done — initializing BLE scanner");
        initializeBleScanner();
    }

    // Switch from 100% to 30% BLE duty cycle once all paired channels have their initial
    // state, or after 60s fallback so we don't scan at full power indefinitely.
    if (_initialStateFetchDeadline != 0)
    {
        bool allFetched = true;
        for (uint8_t i = 0; i < getNumberOfUsedChannels(); i++)
        {
            auto ch = (NukiChannel*)getChannel(i);
            if (ch != nullptr && !ch->isInitialStateFetched())
            {
                allFetched = false;
                break;
            }
        }
        if (allFetched || millis() >= _initialStateFetchDeadline)
        {
            _initialStateFetchDeadline = 0;
            if (allFetched)
            {
                logDebugP("All channels ready — switching BLE scan to low-power mode (30%% duty)");
            }
            else
            {
                logDebugP("Initial state timeout — switching BLE scan to low-power mode (30%% duty)");
            }
            _requestLowPowerScan = true;
        }
    }
    if (scanner != nullptr)
    {
        scanner->update();
    }
    NUKChannelOwnerModule::loop();
}

bool NukiModule::processFunctionProperty(uint8_t objectIndex, uint8_t propertyId, uint8_t length, uint8_t* data, uint8_t* resultData, uint8_t& resultLength)
{
    if (!knx.configured())
        return false;
    if (objectIndex != 160) // arbitrary, must match the object index used in the ETS script for function property commands
        return false;
    if (propertyId != 9) // arbitrary, must match the property ID used in the ETS script for function property commands
        return false;
    if (length < 1) // at least 1 byte needed for command ID
        return false;

    logHexTraceP(data, length);
    auto cmd = data[0];

    switch (cmd)
    {
        case 1: // pair command
        {
            if (length != 2)
                return false;
            int channelIndex = data[1];
            if (channelIndex >= getNumberOfChannels())
            {
                logErrorP("Channel %d not available", channelIndex + 1);
                resultData[0] = 4;
                resultLength = 1;
                return true;
            }
            auto channel = (NukiChannel*)getChannel(channelIndex); // channelIndex is 0-based, ETS script uses 1-based indexing — adjust accordingly
            if (channel == nullptr)
            {
                logErrorP("Channel %d disabled", channelIndex + 1);
                resultData[0] = 5;
                resultLength = 1;
                return true;
            }
            resultData[0] = channel->pairDevice() ? 2 : 3;
            resultLength = 1;
            return true;
        }
    }
    resultData[0] = 1;
    resultLength = 1;
    return false;
}

OpenKNX::Channel* NukiModule::createChannel(uint8_t _channelIndex /* this parameter is used in macros, do not rename */)
{
    if (ParamNUK_CHChannelDisabled)
    {
        logDebugP("Channel %d is temporarily disabled", _channelIndex);
        return nullptr;
    }
    OpenKNX::Channel* channel = nullptr;
    // <Enumeration Text="Deaktiviert" Value="0" Id="%ENID%" />
    // <Enumeration Text="Smart Lock" Value="1" Id="%ENID%" />
    // <Enumeration Text="Opener" Value="2" Id="%ENID%" />
    switch (ParamNUK_CHChannelType)
    {
        case 0: // disabled
            logInfoP("Channel %d disabled", _channelIndex);
            break;
        case 1: // Smart Lock
            logInfoP("Channel %d Smart Lock creating", _channelIndex);
            channel = new NukiSmartLockChannel(_channelIndex);
            break;
        case 2: // Opener
            logInfoP("Channel %d Opener creating", _channelIndex);
            channel = new NukiOpenerChannel(_channelIndex);
            break;
        default:
            logErrorP("Channel %d not implemented", _channelIndex);
            break;
    }
    return channel;
}

void NukiModule::showHelp()
{
    openknx.console.printHelpLine("nuki<channel>", "Show informations");
    openknx.console.printHelpLine("nuki<channel> pair", "Pair Nuki device");
    openknx.console.printHelpLine("nuki<channel> ?", "Show help of channel");
}

bool NukiModule::processCommand(const std::string cmd, bool diagnoseKo)
{
    if (cmd.rfind("nuki", 0) == 0)
    {
        auto subCmd = cmd.substr(4);
        if (subCmd.length() == 0)
        {
            logInfoP("Nuki Module with %d channels", getNumberOfUsedChannels());
            return true;
        }
        int channelIndex = 0;
        auto pos = subCmd.find(" ");
        if (pos != std::string::npos)
        {
            try
            {
                channelIndex = std::stoi(subCmd.substr(0, pos));
            }
            catch (...)
            {
                logErrorP("Invalid channel index %s", subCmd.substr(0, pos).c_str());
                return true;
            }
            subCmd = subCmd.substr(pos + 1);
        }
        else
        {
            try
            {
                channelIndex = std::stoi(subCmd);
            }
            catch (...)
            {
                logErrorP("Invalid channel index %s", subCmd.c_str());
                return true;
            }
            subCmd = "";
        }
        if (channelIndex < 1 || channelIndex > getNumberOfChannels())
        {
            logInfoP("Channel %d not available", channelIndex);
            return true;
        }
        auto channel = (NukiChannel*)getChannel(channelIndex - 1);
        if (channel == nullptr)
        {
            logErrorP("Channel %d not found", channelIndex);
        }
        else
        {
            return channel->processCommand(subCmd, diagnoseKo);
        }
        return true;
    }
    return false;
}

NukiModule openknxNukiModule;