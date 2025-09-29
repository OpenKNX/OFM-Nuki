#include "NukiSmartLockChannel.h"


NukiSmartLockChannel::NukiSmartLockChannel(uint8_t _channelIndex) : NukiChannel(_channelIndex, "SmartLock"),
  _smartLock(_name, 2025000 + _channelIndex)
{

}

void NukiSmartLockChannel::notify(Nuki::EventType eventType)
{
    logDebugP("Event received: %d", (int)eventType);
    _notified = true;
}

void NukiSmartLockChannel::showInformations()
{
    logInfoP("Initialized: %s", _initialized ? "yes" : "no");
    if (_smartLock.isPairedWithLock())
    {
        logInfoP("Nuki Smart Lock is paired");
        logInfoP("Nuki ID: %u", _config.nukiId);
        logInfoP("Name: %s", _config.name);
        if (_config.firmwareVersion[0] != 0 || _config.firmwareVersion[1] != 0 || _config.firmwareVersion[2] != 0)
        {
            logInfoP("Firmware Version: %d.%d.%d", _config.firmwareVersion[0], _config.firmwareVersion[1], _config.firmwareVersion[2]);
        }
        if (_config.hardwareRevision[0] != 0 || _config.hardwareRevision[1] != 0)
        {
            logInfoP("Hardware Revision: %d.%d", _config.hardwareRevision[0], _config.hardwareRevision[1]);
        }
        if (_config.latitude != 0 || _config.longitude != 0)
        {
            logInfoP("Location: %f/%f", _config.latitude, _config.longitude);
        }
        if (_config.autoUnlatch != 255)
        {
            logInfoP("Auto Unlatch: %s", _config.autoUnlatch ? "enabled" : "disabled");
        }
        if (_config.pairingEnabled != 255)
        {
            logInfoP("Pairing: %s", _config.pairingEnabled ? "enabled" : "disabled");
        }
        if (_config.buttonEnabled != 255)
        {
            logInfoP("Button: %s", _config.buttonEnabled ? "enabled" : "disabled");
        }
        if (_config.ledEnabled != 255)
        {
            logInfoP("LED: %s", _config.ledEnabled ? "enabled" : "disabled");
        }
        if (_config.ledBrightness != 255)
        {
            logInfoP("LED Brightness: %d", _config.ledBrightness);
        }
        if (_config.hasFob != 255)
        {
            logInfoP("Fob: %s", _config.hasFob ? "yes" :
                                        "no");  
        }
        if (_config.hasKeypad != 255)
        {
            logInfoP("Keypad: %s", _config.hasKeypad ? "yes" :
                                        "no");  
        }
        if (_config.hasKeypadV2 != 255)
        {
            logInfoP("Keypad V2: %s", _config.hasKeypadV2 ? "yes" :
                                        "no");  
        }
        if (_config.timeZoneId != Nuki::TimeZoneId::None)
        {
            logInfoP("Time Zone ID: %d", (int)_config.timeZoneId);
        }       
        if (_config.advertisingMode != Nuki::AdvertisingMode::Unknown)
        {
            logInfoP("Advertising Mode: %d", (int)_config.advertisingMode);
        }
        if (_config.homeKitStatus != 255)
        {
            logInfoP("HomeKit Status: %d", _config.homeKitStatus);
        }
        if (_config.matterStatus != 255)
        {
            logInfoP("Matter Status: %d", _config.matterStatus);
        }
        if (_config.productVariant != 255)
        {
            logInfoP("Product Variant: %d", _config.productVariant);
        }
        if (_keyTurnerState.nukiState != NukiLock::State::Uninitialized)
        {
            logInfoP("Lock State: %d", (int)_keyTurnerState.lockState);
            logInfoP("Last Action: %d", (int)_keyTurnerState.lastLockAction);
            logInfoP("Last Action Trigger: %d", (int)_keyTurnerState.lastLockActionTrigger);
            logInfoP("Last Action Status: %d", (int)_keyTurnerState.lastLockActionCompletionStatus);
            logInfoP("Door Sensor State: %d", (int)_keyTurnerState.doorSensorState);
            logInfoP("Battery Percentage: %d", _smartLock.getBatteryPerc());
        }
        else
        {
            logInfoP("Key Turner State not available");
        }
    }
    else
    {
        logInfoP("Nuki Smart Lock is not paired");
    }
}


bool NukiSmartLockChannel::updateConfig()
{
    if (_smartLock.requestConfig(&_config) == 1)
    {
        logDebugP("Name: %s", _config.name);
        return true;
    }
    else
    {
        _config = {0};
        logDebugP("getConfig failed");
        return false;
    }
}

bool NukiSmartLockChannel::getKeyTurnerState()
{
    uint8_t result = _smartLock.requestKeyTurnerState(&_keyTurnerState);
    if (result == 1)
    {
        logInfoP("lock state: %d %02d:%02d:%02d Bat crit: %d, Bat perc:%d ",
         _keyTurnerState.lockState, _keyTurnerState.currentTimeHour,
        _keyTurnerState.currentTimeMinute, _keyTurnerState.currentTimeSecond, _smartLock.isBatteryCritical(), _smartLock.getBatteryPerc());
    }
    else
    {
        _keyTurnerState.nukiState = NukiLock::State::Uninitialized;
        logErrorP("cmd failed: %d", result);
    }
    return result;
}

void NukiSmartLockChannel::initialize(BleScanner::Scanner& scanner)
{
    NukiChannel::initialize(scanner);
    _smartLock.setEventHandler(this);
    //_smartLock.registerLogger(&nukiLogger);
    _smartLock.registerBleScanner(&scanner);
    _smartLock.initialize();

}

void NukiSmartLockChannel::setup()
{
    NukiChannel::setup();
}

bool NukiSmartLockChannel::processCommand(const std::string cmd, bool diagnoseKo)
{
    if (NukiChannel::processCommand(cmd, diagnoseKo))
        return true;
    if (cmd == "?")
    {
        openknx.console.printHelpLine("nuki<channel> unlock", "Unlock the door");
        openknx.console.printHelpLine("nuki<channel> lock", "Lock the door");
        return true;
    }
    if (cmd == "unlock")
    {
        if (_smartLock.lockAction(NukiLock::LockAction::Unlock) == 1)
            logInfoP("Unlock command sent");
        else
            logErrorP("Unlock command failed");
        return true;
    }
    if (cmd == "lock")
    {
        if (_smartLock.lockAction(NukiLock::LockAction::Lock) == 1)
            logInfoP("Lock command sent");
        else
            logErrorP("Lock command failed");
        return true;
    }
    return false;
}

bool NukiSmartLockChannel::pairDevice()
{
    if (_smartLock.pairNuki() == Nuki::PairingResult::Success)
    {
        logInfoP("Nuki Smart Lock paired");
        return true;
    }
    else
    {
        logErrorP("Nuki Smart Lock pairing failed");
        return false;
    }
}

void NukiSmartLockChannel::loop()
{
    NukiChannel::loop();
    if (_notified)
    {
        _notified = false;
        if (_smartLock.isPairedWithLock())
        {
            logDebugP("Notification received, updating keyturner state");
            _retryKeyTurnStateRequestMs = 0;
        }
    }
    if (!_initialized && _smartLock.isPairedWithLock() && (_retryInitialization == 0 || millis() - _retryInitialization > 600000))
    {
        if (!updateConfig())
        {
            _retryInitialization = max(1UL, millis());
            return;
        }
        _initialized = true;
    }
    if (_initialized)
    {
        if (_lastKeyTurnerStateRequest == 0 || (millis() - _lastKeyTurnerStateRequest > _retryKeyTurnStateRequestMs))
        {
            logDebugP("Requesting keyturner state");
            _lastKeyTurnerStateRequest = max(1UL, millis());
            if (getKeyTurnerState())
            {
                _retryKeyTurnStateRequestMs = 600000*12; // 12 hours
            }
            else
            {
                _retryKeyTurnStateRequestMs = 60000; // 1 minute
            }
        }
    }
}
