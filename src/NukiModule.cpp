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
    logDebugP("Start Bluetooth Scanner");
    scanner = new BleScanner::Scanner();
    // interval=160 (100ms), window=48 (30ms) → 30% duty cycle.
    // Default was interval=window=23 → 100% duty cycle (radio permanently on).
    // 30% is sufficient to catch Nuki advertisements (~200ms interval).
    scanner->initialize("blescanner", true, 160, 48);

    NUKChannelOwnerModule::setup();

    // Clear BLE whitelist before initializing channels.
    // The NimBLE whitelist lives only in BLE controller RAM — it does not survive a reboot.
    // Each channel's initialize() will re-add its paired device address.
    NimBLEDevice::whiteListClear();

    for (uint8_t i = 0; i < getNumberOfUsedChannels(); i++)
    {
        auto channel = (NukiChannel*) getChannel(i);
        if (channel == nullptr)
        {
            continue;
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
            auto channelIndex = data[1];
            if (channelIndex < 0 || channelIndex >= getNumberOfChannels())
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
            if (channel->pairDevice())
            {
                resultData[0] = 2;
                resultLength = 1;
                return true;
            }
            else
            {
                resultData[0] = 3;
                resultLength = 1;
                return true;
            }
            resultData[0] = 2;
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