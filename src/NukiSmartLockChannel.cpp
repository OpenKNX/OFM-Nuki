#include "NukiSmartLockChannel.h"
// <!-- KO Batteriestatus -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%000_R-%TT%%CC%00000" RefId="%AID%_O-%TT%%CC%000" ObjectSize="1 Bit" DatapointType="DPST-5-1" Text="%C%: Batterieladung" FunctionText="{{0:-}} Batterieladung" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" ReadFlag="Enabled" TransmitFlag="Enabled" />
// <!-- KO Auf/Zu -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%001_R-%TT%%CC%00100" RefId="%AID%_O-%TT%%CC%001" ObjectSize="1 Bit" DatapointType="DPST-1-9" Text="%C%: Dauerhaft Auf/Zu" FunctionText="{{0:-}} Dauerhaft Auf/Zu" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" WriteFlag="Enabled" />
// <!-- KO Auf/Zu Status -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%002_R-%TT%%CC%00200" RefId="%AID%_O-%TT%%CC%002" ObjectSize="1 Bit" DatapointType="DPST-1-11" Text="%C%: Unversperrt" FunctionText="{{0:-}} Unversperrt" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" ReadFlag="Enabled" TransmitFlag="Enabled" />
// <!-- KO Unlatch -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%003_R-%TT%%CC%00300" RefId="%AID%_O-%TT%%CC%003" ObjectSize="1 Bit" DatapointType="DPST-1-17" Text="%C%: Falle ziehen" FunctionText="{{0:-}} Falle ziehen" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" WriteFlag="Enabled" />
// <!-- KO Unlatch Status -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%004_R-%TT%%CC%00400" RefId="%AID%_O-%TT%%CC%004" ObjectSize="1 Bit" DatapointType="DPST-1-11" Text="%C%: Falle gezogen" FunctionText="{{0:-}} Falle gezogen" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" ReadFlag="Enabled" TransmitFlag="Enabled" />
// <!-- KO Nuki Lock`n`Go -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%005_R-%TT%%CC%00500" RefId="%AID%_O-%TT%%CC%005" ObjectSize="1 Bit" DatapointType="DPST-1-9" Text="%C%: Nuki Lock'n'Go" FunctionText="{{0:-}} Nuki Lock'n'Go" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" WriteFlag="Enabled" />
// <!-- KO Nuki Lock`n`Go Aktiv -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%006_R-%TT%%CC%00600" RefId="%AID%_O-%TT%%CC%006" ObjectSize="1 Bit" DatapointType="DPST-1-11" Text="%C%: Nuki Lock'n'Go Aktiv" FunctionText="{{0:-}} Nuki Lock'n'Go Aktiv" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" ReadFlag="Enabled" TransmitFlag="Enabled" />
// <!-- KO OpenKNX Lock`n`Go -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%007_R-%TT%%CC%00700" RefId="%AID%_O-%TT%%CC%007" ObjectSize="1 Bit" DatapointType="DPST-1-9" Text="%C%: OpenKNX Lock'n'Go" FunctionText="{{0:-}} OpenKNX Lock'n'Go" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" WriteFlag="Enabled" />
// <!-- KO OpenKNX Lock`n`Go Aktiv -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%008_R-%TT%%CC%00800" RefId="%AID%_O-%TT%%CC%008" ObjectSize="1 Bit" DatapointType="DPST-1-11" Text="%C%: OpenKNX Lock'n'Go Aktiv" FunctionText="{{0:-}} OpenKNX Lock'n'Go Aktiv" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" ReadFlag="Enabled" TransmitFlag="Enabled" />
// <!-- KO Verbleibend Sekunden-->
// <ComObjectRef Id="%AID%_O-%TT%%CC%009_R-%TT%%CC%00900" RefId="%AID%_O-%TT%%CC%009" ObjectSize="1 Byte" DatapointType="DPST-5-10"    Text="%C%: Verbleibend Offen"  FunctionText="{{0:-}} Verbleibend Offen Sekunden" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" ReadFlag="Enabled" TransmitFlag="Enabled" />
// <!-- KO Verbleibend Minuten -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%009_R-%TT%%CC%00910" RefId="%AID%_O-%TT%%CC%009" ObjectSize="1 Byte" DatapointType="DPST-5-10"    Text="%C%: Verbleibend Offen"  FunctionText="{{0:-}} Verbleibend Offen Minuten" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" ReadFlag="Enabled" TransmitFlag="Enabled" />
// <!-- KO Status Text -->  
// <ComObjectRef Id="%AID%_O-%TT%%CC%010_R-%TT%%CC%01000" RefId="%AID%_O-%TT%%CC%010" ObjectSize="14 Bytes" DatapointType="DPST-16-1"    Text="%C%: Status Text"        FunctionText="{{0:-}} Status Text"               TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" ReadFlag="Enabled" TransmitFlag="Enabled" />
// <!-- KO Lock Command -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%011_R-%TT%%CC%01100" RefId="%AID%_O-%TT%%CC%011" ObjectSize="1 Byte" DatapointType="DPST-5-10" Text="%C%: Befehl" FunctionText="{{0:-}} Befehl" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" WriteFlag="Enabled" />
// <!-- KO Lock State -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%012_R-%TT%%CC%01200" RefId="%AID%_O-%TT%%CC%012" ObjectSize="1 Byte" DatapointType="DPST-1-11" Text="%C%: Status" FunctionText="{{0:-}} Status" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" ReadFlag="Enabled" TransmitFlag="Enabled" />
// <!-- KO Door open feedback -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%013_R-%TT%%CC%01300" RefId="%AID%_O-%TT%%CC%013" ObjectSize="1 Bit" DatapointType="DPST-1-19" Text="%C%: Tür geöffnet Eingang" FunctionText="{{0:-}} Tür geöffnet Eingang" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" WriteFlag="Enabled" UpdateFlag="Enabled" />


#define KoNUK_BatteryState KoNUK_CHKO0 
#define KoNUK_LockUnlock KoNUK_CHKO1 
#define KoNUK_UnLockState KoNUK_CHKO2
#define KoNUK_Unlatch KoNUK_CHKO3 
#define KoNUK_UnlatchState KoNUK_CHKO4 
#define KoNUK_NukiLocknGo KoNUK_CHKO5
#define KoNUK_NukiLocknGoState KoNUK_CHKO6 
#define KoNUK_OpenKNXLocknGo KoNUK_CHKO7 
#define KoNUK_OpenKNXLocknGoState KoNUK_CHKO8 
#define KoNUK_RemainingOpenTime KoNUK_CHKO9 
#define KoNUK_StatusText KoNUK_CHKO10
#define KoNUK_LockCommand KoNUK_CHKO11
#define KoNUK_LockState KoNUK_CHK12 
#define KoNUK_DoorOpenFeedback KoNUK_CHK13

#define NUK_KoBatteryState NUK_KoCHKO0
#define NUK_KoLockUnlock NUK_KoCHKO1
#define NUK_KoUnLockState NUK_KoCHKO2
#define NUK_KoUnlatch NUK_KoCHKO3
#define NUK_KoUnlatchState NUK_KoCHKO4
#define NUK_KoNukiLocknGo NUK_KoCHKO5
#define NUK_KoNukiLocknGoState NUK_KoCHKO6
#define NUK_KoOpenKNXLocknGo NUK_KoCHKO7
#define NUK_KoOpenKNXLocknGoState NUK_KoCHKO8
#define NUK_KoRemainingOpenTime NUK_KoCHKO9
#define NUK_KoStatusText NUK_KoCHK10
#define NUK_KoLockCommand NUK_KoCHK11
#define NUK_KoLockState NUK_KoCHK12
#define NUK_KoDoorOpenFeedback NUK_KoCHK13


NukiSmartLockChannel::NukiSmartLockChannel(uint8_t _channelIndex) : NukiChannel(_channelIndex, "SmartLock"),
  _smartLock(_deviceName, 2025000 + _channelIndex)
{

}



void NukiSmartLockChannel::showInformations()
{
    logInfoP("Initialized: %s", _initialized ? "yes" : "no");
    if (_paired)
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
        KoNUK_BatteryState.valueCompare(_smartLock.getBatteryPerc(), DPT_Scaling);
        switch (_keyTurnerState.lockState)    
        {
            case NukiLock::LockState::Unlocked:
            case NukiLock::LockState::Unlocking:
            case NukiLock::LockState::UnlockedLnga:
                KoNUK_UnLockState.valueCompare((uint8_t) 1, DPT_Switch);
                KoNUK_UnlatchState.valueCompare((uint8_t) 0, DPT_Switch);
                break;
            case NukiLock::LockState::Unlatching:
            case NukiLock::LockState::Unlatched:
                KoNUK_UnLockState.valueCompare((uint8_t) 1, DPT_Switch);
                KoNUK_UnlatchState.valueCompare((uint8_t) 1, DPT_Switch);
                break;
            default: // all other
                KoNUK_UnLockState.valueCompare((uint8_t) 0, DPT_Switch); 
                KoNUK_UnlatchState.valueCompare((uint8_t) 0, DPT_Switch);
                break;
        }
        KoNUK_LockState.valueCompare((uint8_t) _keyTurnerState.lockState, DPT_Value_1_Ucount);
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
    _paired = _smartLock.isPairedWithLock();
}

void NukiSmartLockChannel::setup()
{
    NukiChannel::setup();
}

void NukiSmartLockChannel::processInputKo(GroupObject &ko)
{
    NukiChannel::processInputKo(ko);
    switch (NUK_KoCalcIndex(ko.asap()))
    {
        case NUK_KoLockUnlock:
        if (ko.value(DPT_Switch))
        {
            logInfoP("Lock command received via KNX");
            if (_smartLock.lockAction(NukiLock::LockAction::Lock) == Nuki::CmdResult::Success)
                logInfoP("Lock command sent");
            else
                logErrorP("Lock command failed");
        }
        else
        {
            logInfoP("Unlock command received via KNX");
            if (_smartLock.lockAction(NukiLock::LockAction::Unlock) == Nuki::CmdResult::Success)
                logInfoP("Unlock command sent");
            else
                logErrorP("Unlock command failed");
        }
        break;
        case NUK_KoUnlatch:
        if (ko.value(DPT_Trigger))
        {
            logInfoP("Unlatch command received via KNX");
            if (_smartLock.lockAction(NukiLock::LockAction::Unlatch) == Nuki::CmdResult::Success)
                logInfoP("Unlatch command sent");
            else
                logErrorP("Unlatch command failed");
        }
        break;
        case NUK_KoNukiLocknGo:
        if (ko.value(DPT_Trigger))
        {
            logInfoP("Nuki Lock'n'Go command received via KNX");
            if (_smartLock.lockAction(NukiLock::LockAction::LockNgo) == Nuki::CmdResult::Success)
                logInfoP("Nuki Lock'n'Go command sent");
            else
                logErrorP("Nuki Lock'n'Go command failed");
        }
        break;
        case NUK_KoLockCommand:
        {
            uint8_t cmd = ko.value(DPT_Value_1_Ucount);
            logInfoP("Lock command %d received via KNX", cmd);
            if (_smartLock.lockAction((NukiLock::LockAction ) cmd) == Nuki::CmdResult::Success)
                logInfoP("Lock command %d sent", cmd);
            else
                logErrorP("Lock command %d failed", cmd);
            
        }
        break;
        case NUK_KoOpenKNXLocknGo:
        {
            if (ko.value(DPT_Trigger))
            {
                logInfoP("OpenKNX Lock'n'Go command received via KNX");
                // <Enumeration Text="Entsperren" Value="0" Id="%ENID%" />
                // <Enumeration Text="Lasche ziehen" Value="1" Id="%ENID%" />
                if (ParamNUK_CHLockNGoMode)
                {
                    if (_smartLock.lockAction(NukiLock::LockAction::Unlock) == Nuki::CmdResult::Success)
                        logInfoP("OpenKNX Lock'n'Go (unlock) command sent");
                    else
                        logErrorP("OpenKNX Lock'n'Go (unlock) command failed");
                }
                else
                {
                    if (_smartLock.lockAction(NukiLock::LockAction::Unlatch) == Nuki::CmdResult::Success)
                        logInfoP("OpenKNX Lock'n'Go (unlatch) command sent");
                    else
                        logErrorP("OpenKNX Lock'n'Go (unlatch) command failed");
                }
                _openKNXLockAndGoStartTime = max(1UL, millis());
            }
        }
    }
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
    _smartLock.unPairNuki();
    if (_smartLock.pairNuki() == Nuki::PairingResult::Success)
    {
        _paired = true;
        logInfoP("Nuki Smart Lock paired");
        return true;
    }
    else
    {
        _paired = _smartLock.isPairedWithLock();
        logErrorP("Nuki Smart Lock pairing failed");
        return false;
    }
}

void NukiSmartLockChannel::handleEvent(Nuki::EventType eventType)
{
    if (_paired)
    {
        logDebugP("Notification received, updating keyturner state");
        _retryKeyTurnStateRequestMs = 0;
    }
}

void NukiSmartLockChannel::loop()
{
    NukiChannel::loop();
    if (!_initialized && _paired && (_retryInitialization == 0 || millis() - _retryInitialization > 600000))
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
    auto now = max(1UL, millis());
    if (_openKNXLockAndGoStartTime != 0 && now - _openKNXLockAndGoStartTime >= ParamNUK_CHLockNGoDelayTimeMS)
    {
        logInfoP("OpenKNX Lock'n'Go period ended");
        _openKNXLockAndGoStartTime = 0;
        if (_smartLock.lockAction(NukiLock::LockAction::Lock) == Nuki::CmdResult::Success)
            logInfoP("OpenKNX Lock'n'Go (lock) command sent");
        else
            logErrorP("OpenKNX Lock'n'Go (lock) command failed");
    }
}
