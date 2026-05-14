#include "NukiModule.h"
#include "BleScanner.h"
#include "NukiConstants.h"
#include "NukiSmartLockChannel.h"
#include "NukiOpenerChannel.h"



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
    NUKChannelOwnerModule::initialize(ParamNUK_VisibleChannels);
    NUKChannelOwnerModule::setup();

    // Defer BLE scanner initialization to loop() to let the supply voltage settle after
    // boot before the BLE stack draws its startup current peak.
    // Triggered channels exist but are not yet connected to the scanner.
    _bleInitDeadline = millis() + BLE_INIT_DELAY_MS;
    logDebugP("BLE scanner start deferred by %dms for supply stabilization", BLE_INIT_DELAY_MS);
}

void NukiModule::initializeBleScanner()
{
    // The NimBLE whitelist lives only in BLE controller RAM and is always empty after a
    // reboot — no explicit clear needed. Each channel's initialize() adds its paired address.
    for (uint8_t i = 0; i < getNumberOfUsedChannels(); i++)
    {
        auto channel = (NukiChannel*) getChannel(i);
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
            _channelInitDeadline = millis() + CHANNEL_INIT_DELAY_MS;
            return;
        }
    }
}

void NukiModule::initializeChannels()
{
    for (uint8_t i = 0; i < getNumberOfUsedChannels(); i++)
    {
        auto channel = (NukiChannel*) getChannel(i);
        if (channel == nullptr)
            continue;
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
    _initialStateFetchDeadline = millis() + BLE_INITIAL_STATE_TIMEOUT_MS;
}

void NukiModule::loop()
{
    // Deferred BLE startup: wait for supply to stabilize before starting the BLE stack.
    if (_bleInitDeadline != 0)
    {
        if (millis() >= _bleInitDeadline)
        {
            _bleInitDeadline = 0;
            logDebugP("Boot stabilization done — initializing BLE scanner");
            initializeBleScanner();
        }
        else
        {
            // Still waiting for boot stabilization — skip BLE processing.
            return;
        }
    }
    if (_channelInitDeadline != 0 && millis() >= _channelInitDeadline)
    {
        _channelInitDeadline = 0;
        initializeChannels();
    }

    // Switch from 100% to 30% BLE duty cycle once all paired channels have their initial
    // state, or after 60s fallback so we don't scan at full power indefinitely.
    if (_initialStateFetchDeadline != 0)
    {
        bool allFetched = true;
        for (uint8_t i = 0; i < getNumberOfUsedChannels(); i++)
        {
            auto ch = (NukiChannel*) getChannel(i);
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
                logDebugP("All channels ready — switching BLE scan to low-power mode (30%% duty)");
            else
                logDebugP("Initial state timeout — switching BLE scan to low-power mode (30%% duty)");
            auto bleScan = NimBLEDevice::getScan();
            #ifdef BLE_SCAN_INTERVAL_LP
                bleScan->setInterval(BLE_SCAN_INTERVAL_LP); // default 100ms
            #endif
            #ifdef BLE_SCAN_WINDOW_LP
                 bleScan->setWindow(BLE_SCAN_WINDOW_LP);     // default 30ms → 30% duty cycle
            #endif
        }
    }
    if (scanner != nullptr)
        scanner->update();
   
    NUKChannelOwnerModule::loop();
}

bool NukiModule::processFunctionProperty(uint8_t objectIndex, uint8_t propertyId, uint8_t length, uint8_t *data, uint8_t *resultData, uint8_t &resultLength)
{
    if (!knx.configured()) return false;
    if (objectIndex != 160) return false;
    if (propertyId != 9) return false;
    if (length < 1) return false;
 
    logHexTraceP(data, length);
    auto cmd = data[0];

    switch (cmd)
    {
        case 1:
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
            auto channel = (NukiChannel*) getChannel(channelIndex);
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
        case 0:
        logInfoP("Channel %d disabled", _channelIndex);
        break;
    case 1:
        logInfoP("Channel %d Smart Lock creating", _channelIndex);
        channel = new NukiSmartLockChannel(_channelIndex);
        break;
    case 2:
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
        auto channel = (NukiChannel*) getChannel(channelIndex - 1);
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