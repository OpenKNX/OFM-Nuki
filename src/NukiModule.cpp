#include "NukiModule.h"
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
    scanner->initialize();

    NUKChannelOwnerModule::setup();

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
 }

void NukiModule::loop()
{
    if (scanner != nullptr)
        scanner->update();
   
    NUKChannelOwnerModule::loop();
   
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
            channelIndex = std::stoi(subCmd.substr(0, pos));
            subCmd = subCmd.substr(pos + 1);
        }
        else
        {
            channelIndex = std::stoi(subCmd);
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