#include "NukiModule.h"
#include "NukiConstants.h"

uint32_t deviceId = 2020001;
std::string deviceName = "frontDoor";
NukiLock::NukiLock* nukiLock = nullptr;

void getConfig()
{
    NukiLock::Config config;
    if (nukiLock->requestConfig(&config) == 1)
    {
        logDebug("Nuki", "Name: %s", config.name);
    }
    else
    {
        logError("Nuki", "getConfig failed");
    }
}

bool NukiModule::keyTurnerState()
{
    uint8_t result = nukiLock->requestKeyTurnerState(&retrievedKeyTurnerState);
    if (result == 1)
    {
        logInfo("Nuki", "Bat crit: %d, Bat perc:%d lock state: %d %d:%d:%d",
                 nukiLock->isBatteryCritical(), nukiLock->getBatteryPerc(), retrievedKeyTurnerState.lockState, retrievedKeyTurnerState.currentTimeHour,
                 retrievedKeyTurnerState.currentTimeMinute, retrievedKeyTurnerState.currentTimeSecond);
    }
    else
    {
        logError("Nuki", "cmd failed: %d", result);
    }
    return result;
}

const std::string NukiModule::name()
{
    return "Nuki";
}

void NukiModule::showInformations()
{
}

const std::string NukiModule::version()
{
#ifdef MODULE_NukiModule_Version
    return MODULE_NukiModule_Version;
#else
    // hides the module in the version output on the console, because the firmware version is sufficient.
    return "";
#endif
}

class NukiLogger : public Print
{
    std::string buffer = "";
    size_t write(uint8_t c) override
    {
        buffer += static_cast<char>(c);
        if (c == '\n' || buffer.length() == OPENKNX_MAX_LOG_MESSAGE_LENGTH - 20)
        {
            logError("Nuki", "%s", buffer.c_str());
            buffer = "";
        }
        return 1;
    }
};

NukiLogger nukiLogger = NukiLogger();

void NukiModule::setup(bool configured)
{
    logDebugP("Start Bluetooth Scanner");
    scanner = new BleScanner::Scanner();
    scanner->initialize();
    nukiLock = new NukiLock::NukiLock(deviceName, deviceId);
    nukiLock->setEventHandler(&notifyHandler);

    nukiLock->registerLogger(&nukiLogger);
    nukiLock->registerBleScanner(scanner);
    nukiLock->initialize();
}

void NukiModule::loop(bool configured)
{
    if (scanner != nullptr)
        scanner->update();
    if (nukiLock != nullptr)
    {
        if (!nukiLock->isPairedWithLock())
        {
            if (nukiLock->pairNuki() == Nuki::PairingResult::Success)
            {
                logDebugP("Nuki is paired");
       
                

                getConfig();

   
            }
        }
        if (notifyHandler.notified)
        {
            notifyHandler.notified = false;
            if (nukiLock->isPairedWithLock())
            {
                if (keyTurnerState())
                {
                }
            }
        }
    }
}

void NukiModule::showHelp()
{
}

bool NukiModule::processCommand(const std::string cmd, bool diagnoseKo)
{
    if (cmd == "nuki unlock")
    {
        nukiLock->lockAction(NukiLock::LockAction::Unlock);
        return true;
    }
    if (cmd == "nuki lock")
    {
        nukiLock->lockAction(NukiLock::LockAction::Lock);
        return true;
    }
    if (cmd == "nuki state")
    {
        keyTurnerState();
        return true;
    }
    if (cmd == "nuki pair")
    {
        // unpair -> this atomatically starts pairing again
        nukiLock->unPairNuki();
        return true;
    }
    if (cmd == "nuki init")
    {
         nukiLock->setAdvertisingMode(Nuki::AdvertisingMode::Normal);

    }
    return false;
}

NukiModule openknxNukiModule;