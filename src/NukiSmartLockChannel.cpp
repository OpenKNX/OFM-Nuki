#include "NukiSmartLockChannel.h"

// <!-- KO Batteriestatus -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%000_R-%TT%%CC%00000" RefId="%AID%_O-%TT%%CC%000" ObjectSize="1 Byte" DatapointType="DPST-5-1" Text="%C%: Batterieladung" FunctionText="{{0:-}} Batterieladung" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" ReadFlag="Enabled" TransmitFlag="Enabled" />
// <!-- KO Auf/Zu -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%001_R-%TT%%CC%00100" RefId="%AID%_O-%TT%%CC%001" ObjectSize="1 Bit" DatapointType="DPST-1-9" Text="%C%: Zusperren/Aufsperren" FunctionText="{{0:-}} Zusperren/Aufsperren" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" WriteFlag="Enabled" />
// <!-- KO Auf/Zu Status -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%002_R-%TT%%CC%00200" RefId="%AID%_O-%TT%%CC%002" ObjectSize="1 Bit" DatapointType="DPST-1-19" Text="%C%: Entsperrt Status" FunctionText="{{0:-}} Entsperrt Status" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" ReadFlag="Enabled" TransmitFlag="Enabled" />
// <!-- KO Unlatch -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%003_R-%TT%%CC%00300" RefId="%AID%_O-%TT%%CC%003" ObjectSize="1 Bit" DatapointType="DPST-1-17" Text="%C%: Falle ziehen" FunctionText="{{0:-}} Falle ziehen" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" WriteFlag="Enabled" />
// <!-- KO Unlatch Status -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%004_R-%TT%%CC%00400" RefId="%AID%_O-%TT%%CC%004" ObjectSize="1 Bit" DatapointType="DPST-1-11" Text="%C%: Falle gezogen" FunctionText="{{0:-}} Falle gezogen" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" ReadFlag="Enabled" TransmitFlag="Enabled" />
// <!-- KO Nuki Lock`n`Go -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%005_R-%TT%%CC%00500" RefId="%AID%_O-%TT%%CC%005" ObjectSize="1 Bit" DatapointType="DPST-1-17" Text="%C%: Nuki Lock'n'Go" FunctionText="{{0:-}} Nuki Lock'n'Go" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" WriteFlag="Enabled" />
// <!-- KO Motor Blocked-->
// <ComObjectRef Id="%AID%_O-%TT%%CC%006_R-%TT%%CC%00600" RefId="%AID%_O-%TT%%CC%006" ObjectSize="1 Bit" DatapointType="DPST-1-11" Text="%C%: Motor blockiert" FunctionText="{{0:-}} Motor blockiert" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" ReadFlag="Enabled" TransmitFlag="Enabled" />
// <!-- KO OpenKNX Lock`n`Go -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%007_R-%TT%%CC%00700" RefId="%AID%_O-%TT%%CC%007" ObjectSize="1 Bit" DatapointType="DPST-1-17" Text="%C%: OpenKNX Lock'n'Go" FunctionText="{{0:-}} OpenKNX Lock'n'Go" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" WriteFlag="Enabled" />
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
// <ComObjectRef Id="%AID%_O-%TT%%CC%012_R-%TT%%CC%01200" RefId="%AID%_O-%TT%%CC%012" ObjectSize="1 Byte" DatapointType="DPST-5-10" Text="%C%: Sperr-Status" FunctionText="{{0:-}} Sperr-Status" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" ReadFlag="Enabled" TransmitFlag="Enabled" />
// <!-- KO Door open feedback -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%013_R-%TT%%CC%01300" RefId="%AID%_O-%TT%%CC%013" ObjectSize="1 Bit" DatapointType="DPST-1-19" Text="%C%: Tür geöffnet Eingang" FunctionText="{{0:-}} Tür geöffnet Eingang" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" WriteFlag="Enabled" UpdateFlag="Enabled" />
// <!-- KO Burglar Alarm -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%014_R-%TT%%CC%01400" RefId="%AID%_O-%TT%%CC%014" ObjectSize="1 Bit" DatapointType="DPST-1-5" Text="%C%: Einbruchsalarm Aktiv" FunctionText="{{0:-}} Einbruchsalarm Aktiv" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" ReadFlag="Enabled" TransmitFlag="Enabled" />
// <!-- KO Night -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%015_R-%TT%%CC%01500" RefId="%AID%_O-%TT%%CC%015" ObjectSize="1 Bit" DatapointType="DPST-1-24" Text="%C%: Nacht Eingang" FunctionText="{{0:-}} Nacht Eingang" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" WriteFlag="Enabled" UpdateFlag="Enabled" />
// <!-- KO Unlocking -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%016_R-%TT%%CC%01600" RefId="%AID%_O-%TT%%CC%016" ObjectSize="1 Bit" DatapointType="DPST-1-19" Text="{{0:Nuki %C%}}: Aufsperren durch Aktor aktiv" FunctionText="Nuki %C%: Ausgang, Inaktiv=0 / Aktiv=1" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" WriteFlag="Enabled" UpdateFlag="Enabled" />
// <!-- KO Locking -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%017_R-%TT%%CC%01700" RefId="%AID%_O-%TT%%CC%017" ObjectSize="1 Bit" DatapointType="DPST-1-19" Text="{{0:Nuki %C%}}: Zusperren durch Aktor aktiv" FunctionText="Nuki %C%: Ausgang, Inaktiv=0 / Aktiv=1" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" WriteFlag="Enabled" UpdateFlag="Enabled" />



#define KoNUK_BatteryState KoNUK_CHKO0 
#define KoNUK_LockUnlock KoNUK_CHKO1 
#define KoNUK_UnLockState KoNUK_CHKO2
#define KoNUK_Unlatch KoNUK_CHKO3 
#define KoNUK_UnlatchState KoNUK_CHKO4 
#define KoNUK_NukiLocknGo KoNUK_CHKO5
#define KoNUK_MotorBlocked KoNUK_CHKO6 
#define KoNUK_OpenKNXLocknGo KoNUK_CHKO7 
#define KoNUK_OpenKNXLocknGoState KoNUK_CHKO8 
#define KoNUK_RemainingOpenTime KoNUK_CHKO9 
#define KoNUK_StatusText KoNUK_CHK10
#define KoNUK_LockCommand KoNUK_CHK11
#define KoNUK_LockState KoNUK_CHK12 
#define KoNUK_DoorOpenFeedback KoNUK_CHK13
#define KoNUK_BurglarAlarm KoNUK_CHK14
#define KoNUK_NightInput KoNUK_CHK15
#define KoNUK_Unlocking KoNUK_CHK16
#define KoNUK_Locking KoNUK_CHK17

#define NUK_KoBatteryState NUK_KoCHKO0
#define NUK_KoLockUnlock NUK_KoCHKO1
#define NUK_KoUnLockState NUK_KoCHKO2
#define NUK_KoUnlatch NUK_KoCHKO3
#define NUK_KoUnlatchState NUK_KoCHKO4
#define NUK_KoNukiLocknGo NUK_KoCHKO5
#define NUK_KoNuMotorBlocked NUK_KoCHKO6
#define NUK_KoOpenKNXLocknGo NUK_KoCHKO7
#define NUK_KoOpenKNXLocknGoState NUK_KoCHKO8
#define NUK_KoRemainingOpenTime NUK_KoCHKO9
#define NUK_KoStatusText NUK_KoCHK10
#define NUK_KoLockCommand NUK_KoCHK11
#define NUK_KoLockState NUK_KoCHK12
#define NUK_KoDoorOpenFeedback NUK_KoCHK13
#define NUK_KoBurglarAlarm NUK_KoCHK14
#define NUK_KoNightInput NUK_KoCHK15
#define NUK_KoUnlocking NUK_KoCHK16
#define NUK_KoLocking NUK_KoCHK17


const unsigned long NukiSmartLockChannel::KeyTurnTimeMs = 2500;

NukiSmartLockChannel::NukiSmartLockChannel(uint8_t _channelIndex) : NukiChannel(_channelIndex, "SmartLock"),
  _smartLock(_deviceName, 2025000 + _channelIndex)
{

}



void NukiSmartLockChannel::showInformations()
{
    logInfoP("Initialized: %s", _initialized ? "yes" : "no");
    logInfoP("Is night mode: %s", _isNight ? "yes" : "no");
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

const char* NukiSmartLockChannel::lockStateToString(NukiLock::LockState state)
{
    switch (state)
    {
        case NukiLock::LockState::Uncalibrated: return "Uncalibrated";
        case NukiLock::LockState::Locked: return "Locked";
        case NukiLock::LockState::Unlocking: return "Unlocking";
        case NukiLock::LockState::Unlocked: return "Unlocked";
        case NukiLock::LockState::Locking: return "Locking";
        case NukiLock::LockState::Unlatched: return "Unlatched";
        case NukiLock::LockState::UnlockedLnga: return "Unlocked (Lock'n'Go)";
        case NukiLock::LockState::Unlatching: return "Unlatching";
        case NukiLock::LockState::Calibration: return "Calibration";
        case NukiLock::LockState::BootRun: return "Boot Run";
        case NukiLock::LockState::MotorBlocked: return "Motor Blocked";
        case NukiLock::LockState::Undefined: return "Undefined";
        default: return "Unknown";
    }
}

void NukiSmartLockChannel::setLockTimer(NukiCountDownType type, unsigned long waitTime)
{
    _countDownType = type;
    if (_countDownType == NukiCountDownType::NukiCountDownType_NotRunning)
        _lockTimerStartTime = 0;
    else
        _lockTimerStartTime = max(1UL, millis());
    _lockTimerWaitTimeMs = waitTime;
    logDebugP("Set close timer: type=%d, waitTime=%lu, startTime=%lu", (int)_countDownType, _lockTimerWaitTimeMs, _lockTimerStartTime);
}


bool NukiSmartLockChannel::updateKeyTurnerState(bool lockNGoTimerStartAllowed)
{
    _lastKeyTurnerStateRequest = max(1UL, millis());
     if (_lastNotificationReceivedTimestamp != 0) // Nuki does not notify after a notification happens for some time
        _retryKeyTurnStateRequestMs = 30000; // 30 seconds 
    else
        _retryKeyTurnStateRequestMs = 600000*12; // 12 hours

    Nuki::CmdResult result = _smartLock.requestKeyTurnerState(&_keyTurnerState);
    if (result == Nuki::CmdResult::Success)
    {
        _keyTurnerStateInitialized = true;
        _retryRequestKeyTurnerState = 0;
        logInfoP("Lock state: %d (%s)", _keyTurnerState.lockState, lockStateToString(_keyTurnerState.lockState));
        logInfoP("Trigger: %d", (int) _keyTurnerState.trigger);
        logInfoP("Last Lock Action Trigger: %d", (int)_keyTurnerState.lastLockActionTrigger);
        logInfoP("Nuki time: %02d:%02d:%02d", (int) _keyTurnerState.currentTimeHour, (int) _keyTurnerState.currentTimeMinute, (int) _keyTurnerState.currentTimeSecond);
        logInfoP("Nuki timeoffset: %d", (int) _keyTurnerState.timeZoneOffset);
        logInfoP("Battery critical: %s", _smartLock.isBatteryCritical() ? "yes" : "no");
        logInfoP("Battery: %d%%",  (int) _smartLock.getBatteryPerc());
        logInfoP("Lock'n'Go start allowed: %s", lockNGoTimerStartAllowed ? "yes" : "no");
       
        KoNUK_BatteryState.valueCompare(_smartLock.getBatteryPerc(), DPT_Scaling);
        bool unlockingOrUnlocked = false;
        switch (_keyTurnerState.lockState)    
        {
            case NukiLock::LockState::Unlocking:
                _retryKeyTurnStateRequestMs = 5000; // 5 seconds
                KoNUK_UnLockState.valueCompare((uint8_t) 1, DPT_Switch);
                KoNUK_UnlatchState.valueCompare((uint8_t) 0, DPT_Switch);
                unlockingOrUnlocked = true;
                break;
            case NukiLock::LockState::Unlocked:  
            case NukiLock::LockState::UnlockedLnga:
                KoNUK_UnLockState.valueCompare((uint8_t) 1, DPT_Switch);
                KoNUK_UnlatchState.valueCompare((uint8_t) 0, DPT_Switch);
                unlockingOrUnlocked = true;
                stopLockActionTimer();
                break;
            case NukiLock::LockState::Unlatching:
                _retryKeyTurnStateRequestMs = 5000; // 5 seconds
                KoNUK_UnLockState.valueCompare((uint8_t) 1, DPT_Switch);
                KoNUK_UnlatchState.valueCompare((uint8_t) 1, DPT_Switch);
                break;
            case NukiLock::LockState::Unlatched:
                KoNUK_UnLockState.valueCompare((uint8_t) 1, DPT_Switch);
                KoNUK_UnlatchState.valueCompare((uint8_t) 1, DPT_Switch);
                unlockingOrUnlocked = true;
                stopLockActionTimer();
                break;
            case NukiLock::LockState::Locking:
                _retryKeyTurnStateRequestMs = 5000; // 5 seconds
                KoNUK_UnLockState.valueCompare((uint8_t) 1, DPT_Switch);
                KoNUK_UnlatchState.valueCompare((uint8_t) 0, DPT_Switch);
                break;
            case NukiLock::LockState::Locked:
                KoNUK_UnLockState.valueCompare((uint8_t) 0, DPT_Switch); 
                KoNUK_UnlatchState.valueCompare((uint8_t) 0, DPT_Switch);
                stopLockActionTimer();
                break;
            default: // all other
                KoNUK_UnLockState.valueCompare((uint8_t) 0, DPT_Switch); 
                KoNUK_UnlatchState.valueCompare((uint8_t) 0, DPT_Switch);
                break;
        }
        KoNUK_MotorBlocked.valueCompare((_keyTurnerState.lockState == NukiLock::LockState::MotorBlocked) ? (uint8_t) 1 : (uint8_t) 0, DPT_Switch);
        checkAndStartAutoLock();
        auto nukiLockNgoActive = _keyTurnerState.lockNgoTimer > 0 && _keyTurnerState.lockNgoTimer < 255;
        if (nukiLockNgoActive)
        {
            logDebugP("Lock'n'Go active for %d seconds", (int)_keyTurnerState.lockNgoTimer);
            setLockTimer(NukiCountDownType::NukiCountDownType_NukiLockNGo, _keyTurnerState.lockNgoTimer * 1000);
        }
        else if (_countDownType == NukiCountDownType::NukiCountDownType_NukiLockNGo)
        {
            logDebugP("Nuki Lock'n'Go no longer active");
            setLockTimer(NukiCountDownType::NukiCountDownType_NotRunning, 0);
        }
        if (_keyTurnerState.lockState == NukiLock::LockState::Locked)
        {
            setLockTimer(NukiCountDownType::NukiCountDownType_NotRunning, 0);
            if (ParamNUK_CHOpenKNXLockNgo)
                KoNUK_OpenKNXLocknGoState.valueCompare((uint8_t) 0, DPT_Switch);
        }
        KoNUK_LockState.valueCompare((uint8_t) _keyTurnerState.lockState, DPT_Value_1_Ucount);
        _updateTextState = true;
        if (lockNGoTimerStartAllowed &&
            (_keyTurnerState.lockState == NukiLock::LockState::Unlocking ||
            _keyTurnerState.lockState == NukiLock::LockState::Unlocked ||
            _keyTurnerState.lockState == NukiLock::LockState::Unlatching ||
            _keyTurnerState.lockState == NukiLock::LockState::Unlatched) &&
            ((_keyTurnerState.lastLockActionTrigger == NukiLock::Trigger::Manual && ParamNUK_CHLockNGoByManual) ||
            (_keyTurnerState.lastLockActionTrigger == NukiLock::Trigger::Button && ParamNUK_CHLockNGoByButton) ||
            (_keyTurnerState.lastLockActionTrigger == NukiLock::Trigger::System && ParamNUK_CHLockNGoByApp)
            ) && 
            _countDownType != NukiCountDownType::NukiCountDownType_OpenKNXLockNGo &&
            _countDownType != NukiCountDownType::NukiCountDownType_NukiLockNGo &&
            ParamNUK_CHOpenKNXLockNgo) 
        {
            logInfoP("Starting OpenKNX Lock'n'Go timer");
            startOpenKNXLockNGoCloseTimer();
        }
    }
    else
    {
        _keyTurnerState.nukiState = NukiLock::State::Uninitialized;
        if (_retryRequestKeyTurnerState > 0)
            logErrorP("cmd failed: %d", result);
        else
            logDebugP("cmd failed: %d", result);
        if (_retryRequestKeyTurnerState < 60)
            _retryRequestKeyTurnerState++;
        _retryKeyTurnStateRequestMs = 1000 * _retryRequestKeyTurnerState; 
    }
    return result == Nuki::CmdResult::Success;
}

void NukiSmartLockChannel::checkAndStartAutoLock()
{
    if (((ParamNUK_CHLockModeNightEnable && (_isNight ? ParamNUK_CHAutoLockNight : ParamNUK_CHAutoLock)) ||
            (!ParamNUK_CHLockModeNightEnable && ParamNUK_CHAutoLock)) &&
        _lockTimerStartTime == 0 && 
        _keyTurnerState.lockState != NukiLock::LockState::Locked && 
        _keyTurnerState.lockState != NukiLock::LockState::Locking)
    {
        if (ParamNUK_CHLockModeNightEnable && _isNight)
            setLockTimer(NukiCountDownType::NukiCountDownType_AutoLock, ParamNUK_CHAutoLockNightDelayTimeMS);
        else
            setLockTimer(NukiCountDownType::NukiCountDownType_AutoLock, ParamNUK_CHAutoLockDelayTimeMS);
    }
}

void NukiSmartLockChannel::initialize(BleScanner::Scanner& scanner)
{
    NukiChannel::initialize(scanner);
    _bleScanner = &scanner;
    _smartLock.setEventHandler(this);
    //_smartLock.registerLogger(&nukiLogger);
    _smartLock.registerBleScanner(&scanner);
    _smartLock.initialize();
    _paired = _smartLock.isPairedWithLock();
}

void NukiSmartLockChannel::setup()
{ 
    NukiChannel::setup();
    if (ParamNUK_CHKnxDoorSensor && !KoNUK_DoorOpenFeedback.initialized())
        KoNUK_DoorOpenFeedback.requestObjectRead();


    // <Enumeration Text="Deaktiviert" Value="0" Id="%ENID%" />
    // <Enumeration Text="Nuki Einstellung" Value="1" Id="%ENID%" />
    // <Enumeration Text="Zeitfenster" Value="2" Id="%ENID%" />
    // <Enumeration Text="Objekt" Value="3" Id="%ENID%" />
    // <Enumeration Text="Objekt UND Zeitfenster" Value="4" Id="%ENID%" />
    // <Enumeration Text="Objekt ODER Zeitfenster" Value="5" Id="%ENID%" />
    if (ParamNUK_CHLockModeNightEnable && (ParamNUK_CHNightSelection == 3 || ParamNUK_CHNightSelection == 4 || ParamNUK_CHNightSelection == 5) && !KoNUK_NightInput.initialized())
        KoNUK_NightInput.requestObjectRead();
  

    // <Enumeration Text="Keines" Value="0" Id="%ENID%" />
    // <Enumeration Text="Sekunden" Value="1" Id="%ENID%" />
    // <Enumeration Text="Minuten" Value="2" Id="%ENID%" />
    if (ParamNUK_CHCountDownKoType != 0)
        KoNUK_RemainingOpenTime.value((uint8_t) 0, DPT_Value_1_Ucount);

    // <Enumeration Text="nicht aktiv" Value="0" Id="%ENID%" />
    // <Enumeration Text="wenn Tür offen und Nuki versperrt" Value="1" Id="%ENID%" />
    // <Enumeration Text="wenn Tür offen und Nuki manuell geöffnet" Value="2" Id="%ENID%" />
    if (ParamNUK_CHBurglarAlarm != 0)
        KoNUK_BurglarAlarm.value((uint8_t) 0, DPT_Switch);

    KoNUK_LockState.value((uint8_t) NukiLock::LockState::Undefined, DPT_Value_1_Ucount);
    if (ParamNUK_CHOpenKNXLockNgo)
        KoNUK_OpenKNXLocknGoState.value((uint8_t) 0, DPT_Switch);

    KoNUK_UnlatchState.value((uint8_t) 0, DPT_Switch);
    KoNUK_Locking.value((uint8_t) 0, DPT_Switch);
    KoNUK_Unlocking.value((uint8_t) 0, DPT_Switch);

    _isNight = calculateIsNight();
  

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
            lockAction(NukiLock::LockAction::Lock);
        }
        else
        {
            logInfoP("Unlock command received via KNX");
            lockAction(NukiLock::LockAction::Unlock);
        }
        break;
        case NUK_KoUnlatch:
        if (ko.value(DPT_Trigger))
        {
            logInfoP("Unlatch command received via KNX");
            lockAction(NukiLock::LockAction::Unlatch);
        }
        break;
        case NUK_KoNukiLocknGo:
        if (ko.value(DPT_Trigger))
        {
            logInfoP("Nuki Lock'n'Go command received via KNX");
            lockAction(NukiLock::LockAction::LockNgo);
        }
        break;
        case NUK_KoLockCommand:
        {
            uint8_t cmd = ko.value(DPT_Value_1_Ucount);
            logInfoP("Lock command %d received via KNX", cmd);
            lockAction((NukiLock::LockAction) cmd);
        }
        break;
        case NUK_KoOpenKNXLocknGo:
        {
            if (ko.value(DPT_Trigger))
            {
                logInfoP("OpenKNX Lock'n'Go command received via KNX");
                if (_countDownType == NukiCountDownType::NukiCountDownType_NukiLockNGo)
                {
                    logWarningP("OpenKNX Lock'n'Go command received via KNX while Nuki Lock'n'Go running, ignored");
                    return;
                }
                if (_countDownType == NukiCountDownType::NukiCountDownType_OpenKNXLockNGo)
                {
                    // <Enumeration Text="Nichts" Value="0" Id="%ENID%" />
                    // <Enumeration Text="Zeit neu starten" Value="1" Id="%ENID%" />
                    // <Enumeration Text="Versperren" Value="2" Id="%ENID%" />
                    //<Enumeration Text="Dauerhaft entsperren" Value="3" Id="%ENID%" />
                    switch (ParamNUK_CHLockNGoRepeat)
                    {
                        case 1: 
                            logInfoP("Restart OpenKNX Lock'n'Go time");
                            setLockTimer(NukiCountDownType::NukiCountDownType_OpenKNXLockNGo, ParamNUK_CHLockNGoDelayTimeMS);
                            _lockTimerDuration = 0;
                            break;
                        case 2: 
                            logInfoP("OpenKNX Lock'n'Go stop");
                            setLockTimer(NukiCountDownType::NukiCountDownType_OpenKNXLockNGo, 0); // set wait time to 0 to trigger lock
                            break;
                         case 3:
                            logInfoP("OpenKNX Lock'n'Go set to indefinite unlock");
                            setLockTimer(NukiCountDownType::NukiCountDownType_NotRunning, 0);
                            KoNUK_OpenKNXLocknGoState.valueCompare((uint8_t) 0, DPT_Switch);
                            checkAndStartAutoLock();
                            break;
                    }
                    return;
                }
                
                startOpenKNXLockNGoCloseTimer();
                // <Enumeration Text="Entsperren" Value="0" Id="%ENID%" />
                // <Enumeration Text="Lasche ziehen" Value="1" Id="%ENID%" />
                if (ParamNUK_CHLockNGoMode)
                {
                    lockAction(NukiLock::LockAction::Unlatch);
                }
                else
                {
                    lockAction(NukiLock::LockAction::Unlock);
                }

            }
            else
            {
                // <Enumeration Text="Nichts" Value="0" Id="%ENID%" />
                // <Enumeration Text="Versperren" Value="1" Id="%ENID%" />
                // <Enumeration Text="Dauerhaft entsperren wenn aktiv, sonst versperren" Value="2" Id="%ENID%" />
                // <Enumeration Text="Dauerhaft entsperren wenn aktiv" Value="2" Id="%ENID%" />
                switch (ParamNUK_CHLockNGoOff)
                {
                    case 1:
                        logInfoP("OpenKNX Lock'n'Go OFF received via KNX");
                        _lockTimerWaitTimeMs = 0;
                        break;
                    case 2:
                        if (_countDownType == NukiCountDownType::NukiCountDownType_OpenKNXLockNGo)
                        {
                            logInfoP("OpenKNX Lock'n'Go OFF received via KNX, set to indefinite unlock");
                            setLockTimer(NukiCountDownType::NukiCountDownType_NotRunning, 0);
                            KoNUK_OpenKNXLocknGoState.valueCompare((uint8_t) 0, DPT_Switch);
                            checkAndStartAutoLock();
                        }
                        else
                        {
                            logInfoP("OpenKNX Lock'n'Go OFF received via KNX, but not active, lock");
                            setLockTimer(NukiCountDownType::NukiCountDownType_AutoLock, 0);
                        }
                        break;
                    case 3:
                        if (_countDownType == NukiCountDownType::NukiCountDownType_OpenKNXLockNGo)
                        {
                            logInfoP("OpenKNX Lock'n'Go OFF received via KNX, set to indefinite unlock");
                            setLockTimer(NukiCountDownType::NukiCountDownType_NotRunning, 0);
                            KoNUK_OpenKNXLocknGoState.valueCompare((uint8_t) 0, DPT_Switch);
                            checkAndStartAutoLock();
                        }
                        break;
                }
            }
        }
        break;
        case NUK_KoDoorOpenFeedback:
        {
            _doorOpen = ko.value(DPT_Switch);
            if (_doorOpen && _keyTurnerState.lockState == NukiLock::LockState::Locked)
                _lastKeyTurnerStateRequest = 0; // force update
           
            _updateTextState = true;
            _checkBurglarAlarm = true;
        }
        break;
    }
}

void NukiSmartLockChannel::startOpenKNXLockNGoCloseTimer()
{
    setLockTimer(NukiCountDownType::NukiCountDownType_OpenKNXLockNGo, ParamNUK_CHLockNGoDelayTimeMS);
    _doorOpenBreak = _doorOpen;
    KoNUK_OpenKNXLocknGoState.value((uint8_t)1, DPT_Switch);
    updateStates(_lockTimerStartTime);
}

NukiLock::LockAction NukiSmartLockChannel::getCurrentValidConfiguredLockAction()
{
    if (ParamNUK_CHLockModeNightEnable && _isNight)
    {
        // <Enumeration Text="Sperren" Value="0" Id="%ENID%" />
        // <Enumeration Text="Vollsperren" Value="1" Id="%ENID%" />
        return ParamNUK_CHLockModeNight ? NukiLock::LockAction::FullLock : NukiLock::LockAction::Lock;
    }
    else
    {
        // <Enumeration Text="Sperren" Value="0" Id="%ENID%" />
        // <Enumeration Text="Vollsperren" Value="1" Id="%ENID%" />
        return ParamNUK_CHLockMode ? NukiLock::LockAction::FullLock : NukiLock::LockAction::Lock;
    }
}

bool NukiSmartLockChannel::calculateIsNight()
{
    // <Enumeration Text="Deaktiviert" Value="0" Id="%ENID%" />
    // <Enumeration Text="Nuki Einstellung" Value="1" Id="%ENID%" />
    // <Enumeration Text="Zeitfenster" Value="2" Id="%ENID%" />
    // <Enumeration Text="Objekt" Value="3" Id="%ENID%" />
    // <Enumeration Text="Objekt UND Zeitfenster" Value="4" Id="%ENID%" />
    // <Enumeration Text="Objekt ODER Zeitfenster" Value="5" Id="%ENID%" />
    switch (ParamNUK_CHNightSelection)
    {
        case 0: // disabled
            return false;
        case 2: 
            return isNightTimeWindow();
        case 3: // object
            return KoNUK_NightInput.value(DPT_Switch);
        case 4: // object AND time window
            return KoNUK_NightInput.value(DPT_Switch) && isNightTimeWindow();
        case 5: // object OR time window
            return KoNUK_NightInput.value(DPT_Switch) || isNightTimeWindow();

    }
    return false;
}

bool NukiSmartLockChannel::isNightTimeWindow()
{
    auto now = openknx.time.getLocalTime();
    uint16_t currentMinutes = now.hour * 60 + now.minute;
    uint16_t startMinutes = knx.paramWord(NUK_ParamCalcIndex(NUK_CHNightStart));
    uint16_t endMinutes = knx.paramWord(NUK_ParamCalcIndex(NUK_CHNightEnd));
    bool isNightTimeWindow = (currentMinutes >= startMinutes || currentMinutes < endMinutes);
    return isNightTimeWindow;
}

bool NukiSmartLockChannel::processCommand(const std::string cmd, bool diagnoseKo)
{
    if (NukiChannel::processCommand(cmd, diagnoseKo))
        return true;
    if (cmd == "?")
    {
        openknx.console.printHelpLine("nuki<channel> unlock", "Unlock");
        openknx.console.printHelpLine("nuki<channel> lock", "Lock");
        openknx.console.printHelpLine("nuki<channel> lockngo", "Lock'n'Go");
        openknx.console.printHelpLine("nuki<channel> olockngo", "OpenKNX Lock'n'Go");
        openknx.console.printHelpLine("nuki<channel> update", "Update the keyturner state");
        openknx.console.printHelpLine("nuki<channel> door open", "Simulate door open");
        openknx.console.printHelpLine("nuki<channel> door close", "Simulate door close");
        return true;
    }
    if (cmd == "update")
    {
        _lastKeyTurnerStateRequest = 0;
        return true;
    }
    if (cmd == "unlock")
    {
        lockAction(NukiLock::LockAction::Unlock);
        return true;
    }
    if (cmd == "lockngo")
    {
        lockAction(NukiLock::LockAction::LockNgo);
        return true;
    }
    if (cmd == "olockngo")
    {
        if (ParamNUK_CHOpenKNXLockNgo)
        {
            KoNUK_NukiLocknGo.valueNoSend((uint8_t) 1, DPT_Trigger);
            processInputKo(KoNUK_NukiLocknGo);
        }
        else
        {
            logErrorP("OpenKNX Lock'n'Go not enabled");
        }
        return true;
    }
    if (cmd == "lock")
    {
        lockAction(NukiLock::LockAction::Lock);
        return true;
    }
    if (cmd == "door open")
    {
        if (ParamNUK_CHKnxDoorSensor)
        {
            KoNUK_DoorOpenFeedback.valueNoSend((uint8_t) 1, DPT_Switch);
            processInputKo(KoNUK_DoorOpenFeedback);
        }
        else
        {
            logErrorP("Door open feedback KNX object not enabled");
        }
        return true;
    }
    if (cmd == "door close")
    {
        if (ParamNUK_CHKnxDoorSensor)
        {
            KoNUK_DoorOpenFeedback.valueNoSend((uint8_t) 0, DPT_Switch);
            processInputKo(KoNUK_DoorOpenFeedback);
        }
        else
        {
            logErrorP("Door open feedback KNX object not enabled");
        }
        return true;
    }
    return false;
}

bool NukiSmartLockChannel::pairDevice()
{
    logInfoP("Unpair Nuki Smart Lock");
    _smartLock.unPairNuki();
    logInfoP("Pairing Nuki Smart Lock...");
    _paired = false;

    int counter = 60;
    while (!_smartLock.isPairedWithLock()) 
    {
        if (_smartLock.pairNuki(Nuki::AuthorizationIdType::App) == Nuki::PairingResult::Success) 
        {
          
            break;
        }
        counter--;
        if (counter == 0)
        {
            logErrorP("Nuki Smart Lock pairing failed");
            return false;
        }
        if (_bleScanner != nullptr)
            _bleScanner->update();
        vTaskDelay(500);
    }
    logInfoP("Nuki Smart Lock paired");
    _paired = true;
    return true;

}

void NukiSmartLockChannel::handleEvent(Nuki::EventType eventType)
{
    _lastNotificationReceivedTimestamp = max(1UL, millis());
    if (_paired)
    {
        logInfoP("Notification received, updating keyturner state");
        _lastKeyTurnerStateRequest = 0;
    }
}

bool NukiSmartLockChannel::useCountDownKoAndStateText()
{
    switch (_countDownType)
    {
        case NukiCountDownType::NukiCountDownType_NotRunning:
            return false;
        case NukiCountDownType::NukiCountDownType_AutoLock:
            // <Enumeration Text="Nein" Value="0" Id="%ENID%" />
            // <Enumeration Text="Ja" Value="1" Id="%ENID%" />
            // <Enumeration Text="Nur die letzte Minute" Value="2" Id="%ENID%" />
            switch (ParamNUK_CHUseCountDownForAutoLock)
            {
                case 1:
                    return true;
                case 2:
                    return _remainingSeconds <= 60;
                default:
                    return false;
            }
        default:
            return true;
    }
}

void NukiSmartLockChannel::updateTextState()
{
    if (useCountDownKoAndStateText())
    {
        _textState = "Offen ";
        if (_remainingSeconds >= 60)
        {
            auto remain = std::to_string((int) (_remainingSeconds + 59) / 60);
            if (_doorOpenBreak)
                _textState += std::string(remain.length(), '-');
            else
                _textState += remain;
            _textState += " min";
        }
        else
        {
             auto remain = std::to_string(_remainingSeconds);
             if (_doorOpenBreak)
                _textState += std::string(remain.length(), '-');
            else
                _textState += remain;
            _textState += " s";
        }
    }
    else if (_doorOpen)
        _textState = "T\xFCr offen";
    else if (!_smartLock.isPairedWithLock())
        _textState = "Nicht gekopp.";
    else if (!_initialized)
        _textState = "Init";
    else if (KoNUK_BurglarAlarm.initialized() && (bool) KoNUK_BurglarAlarm.value(DPT_Switch))
        _textState = "Einbruchsalarm";
    else 
    {
        switch (_keyTurnerState.lockState)
        {
            case NukiLock::LockState::Uncalibrated:
                _textState = "Unkalibriert";
                break;
            case NukiLock::LockState::Locked:
                if (_smartLock.isBatteryCritical())
                {
                    _textState = "Batterie ";
                    _textState += std::to_string(_smartLock.getBatteryPerc());
                    _textState += "%";
                }
                else
                    _textState = "Versperrt";
                break;
            case NukiLock::LockState::Unlocking:
                _textState = "Entsperren";
                break;
            case NukiLock::LockState::Unlocked:
                _textState = "Entsperrt";
                break;
            case NukiLock::LockState::Locking:
                _textState = "Versperren";
                break;
            case NukiLock::LockState::Unlatched:
                _textState = "Lasche gezogen";
                break;
            case NukiLock::LockState::UnlockedLnga:
                _textState = "Lock'n'Go";
                break;
            case NukiLock::LockState::Unlatching:
                _textState = "Lasche ziehen";
                break;
            case NukiLock::LockState::Calibration:
                _textState = "Kalibrierung";
                break;
            case NukiLock::LockState::BootRun:
                _textState = "Startvorgang";
                break;
            case NukiLock::LockState::MotorBlocked:
                _textState = "Blockiert";
                break;
            default:
                _textState = "Unbekannt";
                break;
        }
    }
    if (KoNUK_StatusText.valueCompare(_textState.c_str(), DPT_String_8859_1))
    {
        logDebugP("Status text: %s", _textState.c_str());
    }
}

void NukiSmartLockChannel::startLockActionTimer(bool locking, unsigned long actionTimeMs)
{
    logDebugP("Starting lock action timer for action %s, time %lu ms", locking ? "locking" : "unlocking", actionTimeMs);
    _lockActionTimerStart = max(1UL, millis());
    _lockActionTimerWaitTime = actionTimeMs;
    if (locking)
    {
        KoNUK_Locking.valueCompare((uint8_t) 1, DPT_Switch);
        KoNUK_Unlocking.valueCompare((uint8_t) 0, DPT_Switch);
    }
    else
    {
        KoNUK_UnLockState.valueCompare((uint8_t) 1, DPT_Switch);
        KoNUK_Locking.valueCompare((uint8_t) 0, DPT_Switch);
        KoNUK_Unlocking.valueCompare((uint8_t) 1, DPT_Switch);
    }
}

void NukiSmartLockChannel::stopLockActionTimer()
{
    if (_lockActionTimerStart != 0)
    {
        logDebugP("Stopping lock action timer");
        _lockActionTimerStart = 0;
    }
    KoNUK_Locking.valueCompare((uint8_t) 0, DPT_Switch);
    KoNUK_Unlocking.valueCompare((uint8_t) 0, DPT_Switch);
}

void NukiSmartLockChannel::lockAction(NukiLock::LockAction action)
{
    switch (action)
    {
        case NukiLock::LockAction::Lock:
        case NukiLock::LockAction::FullLock:
            logInfoP("Lock action requested: Lock");
            if (_keyTurnerState.lockState != NukiLock::LockState::Locked)
            {
                startLockActionTimer(true, 10000); // 10 seconds, because we query the state after 5 seconds
            }
            break;
        case NukiLock::LockAction::Unlock:
        case NukiLock::LockAction::LockNgo:
        case NukiLock::LockAction::Unlatch:
            if (_keyTurnerState.lockState != NukiLock::LockState::Unlocked &&
                _keyTurnerState.lockState != NukiLock::LockState::UnlockedLnga &&
                _keyTurnerState.lockState != NukiLock::LockState::Unlatched)
            {
                if (_keyTurnerState.lastLockAction == NukiLock::LockAction::FullLock)
                    startLockActionTimer(false,  KeyTurnTimeMs * 2);
                else
                    startLockActionTimer(false, KeyTurnTimeMs);
            }
            break;
    }
    _lockAction = action;
   
}

void NukiSmartLockChannel::loop1()
{
    if (_lastNotificationReceivedTimestamp != 0 && millis() - _lastNotificationReceivedTimestamp > 120000) // Last notification older than 2 minutes, we expect to receive notifications again
    {
        _lastNotificationReceivedTimestamp = 0;
    }
    if (!_initialized && _paired && (_retryInitialization == 0 || millis() - _retryInitialization > 600000))
    {
        if (!updateConfig())
        {
            _retryInitialization = max(1UL, millis());
            return;
        }
        _initialized = true;
        _updateTextState = true;
    }
    if (_initialized)
    {
        if (_lockAction != NukiLock::LockAction::Undefined ||  _lastKeyTurnerStateRequest == 0 || (millis() - _lastKeyTurnerStateRequest > _retryKeyTurnStateRequestMs))
        {
            logDebugP("Requesting keyturner state");
            if (updateKeyTurnerState(_lastKeyTurnerStateRequest == 0 && _keyTurnerStateInitialized))
            {
                switch (_keyTurnerState.lockState)
                {
                    case NukiLock::LockState::Locked:
                        if (_lockAction == NukiLock::LockAction::Lock)
                        {
                            logInfoP("Lock action ingored, already locked");
                            _lockAction = NukiLock::LockAction::Undefined;
                        }
                        break;
                    case NukiLock::LockState::Locking:
                        if (_lockAction == NukiLock::LockAction::Lock)
                        {
                            logInfoP("Lock action ingored, locking already in progress");
                            _lockAction = NukiLock::LockAction::Undefined;
                        }
                        break;
                    case NukiLock::LockState::Unlocking:
                        if (_lockAction == NukiLock::LockAction::Unlock)
                        {
                            logInfoP("Unlock action ingored, unlocking already in progress");
                            _lockAction = NukiLock::LockAction::Undefined;
                        }
                        break;
                    case NukiLock::LockState::Unlocked:
                        if (_lockAction == NukiLock::LockAction::Unlock)
                        {
                            logInfoP("Unlock action ingored, already unlocked");
                            _lockAction = NukiLock::LockAction::Undefined;
                        }
                        break;   
                    case NukiLock::LockState::Unlatched:
                        if (_lockAction == NukiLock::LockAction::Unlatch || _lockAction == NukiLock::LockAction::Unlock)
                        {
                            logInfoP("Unlatch action ingored, already unlatched");
                            _lockAction = NukiLock::LockAction::Undefined;
                        }
                        break;
                    case NukiLock::LockState::UnlockedLnga:
                        logWarningP("Lock'n'Go action ingored, Nuki Lock'n'Go active, this can not be interrupted");
                        _lockAction = NukiLock::LockAction::Undefined;
                         break;
                    case NukiLock::LockState::Unlatching:
                        if (_lockAction == NukiLock::LockAction::Unlatch || _lockAction == NukiLock::LockAction::Unlock)
                        {
                            logInfoP("Unlatch action ingored, unlatching already in progress");
                            _lockAction = NukiLock::LockAction::Undefined;
                        }
                        break;
                }
            }
        }
        if (_lockAction != NukiLock::LockAction::Undefined)
        {
            logDebugP("Processing pending lock action %d", (int)_lockAction);
            int maxRetries = 3;
            auto lockAction = _lockAction;
            for (int i = 0; i < maxRetries; i++)
            {
                if (_smartLock.lockAction(lockAction) == Nuki::CmdResult::Success)
                {
                    logInfoP("Pending lock action %d sent", (int)lockAction);
                    _lockAction = NukiLock::LockAction::Undefined;
                    lockAction = NukiLock::LockAction::Undefined;
                    break;
                }
                else
                {
                    logErrorP("Pending lock action %d failed", (int)lockAction);
                }
            }
            if (lockAction != NukiLock::LockAction::Undefined)
                logErrorP("Pending lock action %d failed after %d retries, giving up", (int)lockAction, maxRetries);
            _retryKeyTurnStateRequestMs = 0;
           
        }
    }
    if (_checkBurglarAlarm)
    {
        logInfoP("Door open feedback received via KNX: %s", _doorOpen ? "open" : "closed");
        // <Enumeration Text="nicht aktiv" Value="0" Id="%ENID%" />
        // <Enumeration Text="wenn Tür offen und Nuki versperrt" Value="1" Id="%ENID%" />
        // <Enumeration Text="wenn Tür offen und Nuki manuell geöffnet" Value="2" Id="%ENID%" />
        switch (ParamNUK_CHBurglarAlarm)
        {
            case 1:
            if (_doorOpen && _keyTurnerState.lockState == NukiLock::LockState::Locked)
            {  
                if (KoNUK_BurglarAlarm.valueCompare((uint8_t) 1, DPT_Switch))
                    logInfoP("Burglar alarm activated");
            }
            else
            {
                if (KoNUK_BurglarAlarm.valueCompare((uint8_t) 0, DPT_Switch))
                    logInfoP("Burglar alarm deactivated");
            }
            break;
            case 2:
            if (_doorOpen && _keyTurnerState.trigger == NukiLock::Trigger::Manual && (_keyTurnerState.lockState == NukiLock::LockState::Unlocked || _keyTurnerState.lockState == NukiLock::LockState::Unlatched))
            {
                if (KoNUK_BurglarAlarm.valueCompare((uint8_t) 1, DPT_Switch))
                    logInfoP("Burglar alarm activated");
            }
            else
            {
                if (KoNUK_BurglarAlarm.valueCompare((uint8_t) 0, DPT_Switch))
                    logInfoP("Burglar alarm deactivated");
            }
            break;
        
        default:
            break;
        }
        _checkBurglarAlarm = false;
    }
}


void NukiSmartLockChannel::loop()
{
#ifndef OPENKNX_DUALCORE
    loop1();
#endif
    NukiChannel::loop();
    if (_updateTextState)
    {
        _updateTextState = false;
        updateTextState();
    }
    if (!_initialized)
        return;
 
    auto now = max(1UL, millis());
    auto isNight = calculateIsNight();
    if (_isNight != isNight)
    {
        _isNight = !_isNight;
        logInfoP("Night mode changed: %s", _isNight ? "yes" : "no");
        // <Enumeration Text="keine Aktion" Value="0" Id="%ENID%" />
        // <Enumeration Text="einfach versperren" Value="1" Id="%ENID%" />
        // <Enumeration Text="2-fach versperren" Value="2" Id="%ENID%" />
        // <Enumeration Text="entsperren" Value="3" Id="%ENID%" />
        switch (_isNight ? ParamNUK_CHNightStartAction : ParamNUK_CHNightEndAction)
        {
            case 1: // lock
                lockAction(getCurrentValidConfiguredLockAction());
                break;
            case 2: // full lock
                lockAction(NukiLock::LockAction::FullLock);
                break;
            case 3: // unlock
                lockAction(NukiLock::LockAction::Unlock);
                break;
        }
    }
    updateStates(now);
   
}

void NukiSmartLockChannel::updateStates(unsigned long now)
{
    if (_lockActionTimerStart != 0)
    {
        if (now - _lockActionTimerStart >= _lockActionTimerWaitTime)
        {
            stopLockActionTimer();
        }
    }
    if (_lockTimerStartTime != 0)
    {
        if (_countDownType != NukiCountDownType::NukiCountDownType_NukiLockNGo)
        {
            if (!_doorOpenBreak && now - _lockTimerStartTime >= _lockTimerWaitTimeMs)
            {
                logInfoP("OpenKNX Lock'n'Go period ended");
                _lockTimerStartTime = 0;   
                _countDownType = NukiCountDownType::NukiCountDownType_NotRunning;
                lockAction(getCurrentValidConfiguredLockAction());
            }
            else
            {
                if (_doorOpen != _doorOpenBreak)
                {
                    _doorOpenBreak = _doorOpen;
                    logInfoP("Door state changed %s", _doorOpen ? "open" : "closed");
                    if (_doorOpen)
                    {
                        _lockTimerDuration = now - _lockTimerStartTime;
                    }
                    else
                    {
                        // <Enumeration Text="Versperrwartezeit fortsetzen" Value="0" Id="%ENID%" />
                        // <Enumeration Text="Versperrwartezeit neu starten" Value="1" Id="%ENID%" />
                        // <Enumeration Text="Versperren nach" Value="2" Id="%ENID%" />
                        // <Enumeration Text="bei OpenKNX Lock'n'Go versperren nach"3" Id="%ENID%" />
                        switch (ParamNUK_CHDoorMode)
                        {
                            case 0: // continue
                                logInfoP("Continuing OpenKNX Lock'n'Go timer");
                                if (_lockTimerWaitTimeMs > _lockTimerDuration)
                                    _lockTimerWaitTimeMs = _lockTimerWaitTimeMs - _lockTimerDuration;
                                else
                                    _lockTimerWaitTimeMs = 0;
                                if (_countDownType != NukiCountDownType::NukiCountDownType_NotRunning)
                                    _lockTimerStartTime = now; 
                                break;
                            case 1: // restart
                                logInfoP("Restarting OpenKNX Lock'n'Go timer");
                                if (_countDownType != NukiCountDownType::NukiCountDownType_NotRunning)
                                    _lockTimerStartTime = now;
                                break;
                            case 2: // lock after wait time time
                                if (_countDownType == NukiCountDownType::NukiCountDownType_NotRunning)
                                    setLockTimer(NukiCountDownType::NukiCountDownType_AutoLock, ParamNUK_CHWaitTimeDelayTimeMS);
                                else
                                    setLockTimer(_countDownType, ParamNUK_CHWaitTimeDelayTimeMS);
                                logInfoP("Locking after %d", (int) (_lockTimerWaitTimeMs / 1000));
                                break;
                             case 3: // lock after wait time time, if OpenKNX Lock'n'Go active
                                if (_countDownType == NukiCountDownType::NukiCountDownType_OpenKNXLockNGo)
                                {
                                    _lockTimerWaitTimeMs = ParamNUK_CHWaitTimeDelayTimeMS;
                                    logInfoP("Locking after %d", (int) (_lockTimerWaitTimeMs / 1000));
                                    _lockTimerStartTime = now;
                                }
                                else
                                {
                                    logInfoP("Continuing OpenKNX Lock'n'Go timer");
                                    if (_lockTimerWaitTimeMs > _lockTimerDuration)
                                        _lockTimerWaitTimeMs = _lockTimerWaitTimeMs - _lockTimerDuration;
                                    else
                                        _lockTimerWaitTimeMs = 0;
                                    if (_countDownType != NukiCountDownType::NukiCountDownType_NotRunning)
                                        _lockTimerStartTime = now; 
                                    break;
                                }
                                break;
                        }
                    }
                    updateTextState();
                }
            }
        }
        else
        {
            // Nuki Lock'n'go ends
            setLockTimer(NukiCountDownType::NukiCountDownType_NotRunning, 0);
            checkAndStartAutoLock();
            startLockActionTimer(true, KeyTurnTimeMs);
        }
        if (!_doorOpenBreak)
        {
            auto elapsed = now - _lockTimerStartTime;
            _remaining = _lockTimerWaitTimeMs - elapsed;
            if (_remaining < 0)
                _remaining = 0;
            uint8_t remainingSeconds = min((_remaining / 1000), 255l);
            if (_remainingSeconds != remainingSeconds)
            {
                _remainingSeconds = remainingSeconds;
                _updateTextState = true;
            }

            if (useCountDownKoAndStateText())
            {
                // <Enumeration Text="Keines" Value="0" Id="%ENID%" />
                // <Enumeration Text="Sekunden" Value="1" Id="%ENID%" />
                // <Enumeration Text="Minuten" Value="2" Id="%ENID%" />
                switch (ParamNUK_CHCountDownKoType)
                {
                    case 1: // seconds
                    {
                        if (KoNUK_RemainingOpenTime.valueCompare((uint8_t) remainingSeconds, DPT_Value_1_Ucount))
                            logInfoP("Remaining Open Time (seconds): %d", remainingSeconds);
                    }
                    break;
                    case 2:
                    {
                        uint8_t remainingMinutes = (remainingSeconds + 59) / 60;
                        if (KoNUK_RemainingOpenTime.valueCompare((uint8_t) remainingMinutes, DPT_Value_1_Ucount))
                            logInfoP("Renumaining Open Time (minutes): %d", remainingMinutes);
                    }
                    break;
                }
            }
        }    
    }
    else
    {
        if (ParamNUK_CHCountDownKoType != 0)
        {
            if (KoNUK_RemainingOpenTime.valueCompare((uint8_t) 0, DPT_Value_1_Ucount))
                logInfoP("Remaining Open Time: 0");
        }
    }
}