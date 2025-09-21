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
        logDebug("Nuki", "getConfig failed");
    }
}

bool NukiModule::keyTurnerState()
{
    uint8_t result = nukiLock->requestKeyTurnerState(&retrievedKeyTurnerState);
    if (result == 1)
    {
        logDebug("Nuki", "Bat crit: %d, Bat perc:%d lock state: %d %d:%d:%d",
                 nukiLock->isBatteryCritical(), nukiLock->getBatteryPerc(), retrievedKeyTurnerState.lockState, retrievedKeyTurnerState.currentTimeHour,
                 retrievedKeyTurnerState.currentTimeMinute, retrievedKeyTurnerState.currentTimeSecond);
    }
    else
    {
        logDebug("Nuki", "cmd failed: %d", result);
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

void NukiModule::setup(bool configured)
{
    logDebugP("Start Bluetooth Scanner");
    scanner = new BleScanner::Scanner();
    scanner->initialize();
    nukiLock = new NukiLock::NukiLock(deviceName, deviceId);
    nukiLock->setEventHandler(nullptr);
    
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
                log_d("paired");
                nukiLock->setEventHandler(&notifyHandler);

                getConfig();
            }
        }
        if (notifyHandler.notified)
        {
            notifyHandler.notified = false;
            if (keyTurnerState())
            {
               
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

    return false;
}

NukiModule openknxNukiModule;