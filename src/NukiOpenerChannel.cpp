#include "NukiOpenerChannel.h"
// <!-- Batteriestatus -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%000_R-%TT%%CC%00001" RefId="%AID%_O-%TT%%CC%000" ObjectSize="1 Bit" DatapointType="DPST-5-1" Text="%C%: Batterieladung" FunctionText="{{0:-}} Batterieladung" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" ReadFlag="Enabled" TransmitFlag="Enabled" />
// <!-- Aufsperren -->
// <ComObjectRef Id="%AID%_O-%TT%%CC%001_R-%TT%%CC%00101" RefId="%AID%_O-%TT%%CC%001" ObjectSize="1 Bit" DatapointType="DPST-1-17" Text="%C%: Aufsperren" FunctionText="{{0:-}} Aufsperren" TextParameterRefId="%AID%_P-%TT%%CC%000_R-%TT%%CC%00000" WriteFlag="Enabled" />

#define KoNUK_BatteryEmpty KoNUK_CHKO0 
#define KoNUK_Unlock KoNUK_CHKO1 

#define NUK_KoBatteryState NUK_KoCHKO0
#define NUK_KoUnlock NUK_KoCHKO1

NukiOpenerChannel::NukiOpenerChannel(uint8_t _channelIndex) : NukiChannel(_channelIndex, "Opener"),
  _opener(_deviceName, 2035000 + _channelIndex)
{
}

void NukiOpenerChannel::setup()
{
    NukiChannel::setup();
}

void NukiOpenerChannel::handleEvent(Nuki::EventType eventType)
{
    _lastBatteryRequest = 0;
    _openerStateInitialized = true; // first event means Nuki is connected and state is known
}

bool NukiOpenerChannel::isInitialStateFetched() const
{
    // Not paired: nothing to wait for.
    // Paired: wait until handleEvent() fires at least once (Nuki connected & state known).
    return !_paired || _openerStateInitialized;
}

void NukiOpenerChannel::initialize(BleScanner::Scanner& scanner)
{
    NukiChannel::initialize(scanner);
    //_opener.registerLogger(&nukiLogger);
    _opener.setEventHandler(this);
    _opener.registerBleScanner(&scanner);
    _opener.initialize();
    _paired = _opener.isPairedWithLock();
    // Whitelist paired device so BLE controller hardware filters out
    // all other BLE advertisements — biggest power saver with antenna connected.
    if (_paired)
    {
        auto addr = _opener.getBleAddress();
        if (addr != BLEAddress("", 0))
        {
            logInfoP("Whitelisting paired Opener: %s", addr.toString().c_str());
            scanner.whitelist(addr);
        }
    }
}

void NukiOpenerChannel::loop()
{
    NukiChannel::loop();
    if (_paired)
    {
        if (_lastBatteryRequest == 0 || (millis() - _lastBatteryRequest > NUKI_OPENER_BATTERY_CHECK_INTERVAL_MS))
        {
            _lastBatteryRequest = millis();
            logDebugP("Requesting battery status from opener");
            NukiOpener::BatteryReport report;
            if (_opener.requestBatteryReport(&report) == Nuki::CmdResult::Success)
            {
                logDebugP("Battery status request sent");
                _openerStateInitialized = true; // first successful BLE contact: initial state known
                KoNUK_BatteryEmpty.valueCompare((uint8_t) report.criticalBatteryState, DPT_Alarm);
            }
            else
            {
                logErrorP("Battery status request failed");
            }
        }
    }
}

bool NukiOpenerChannel::pairDevice()
{
    // Save old address before unpairing so we can remove it from the whitelist later
    auto oldAddr = _opener.getBleAddress();

    // Temporarily disable whitelist filter so we can discover new devices
    NimBLEDevice::getScan()->setFilterPolicy(BLE_HCI_SCAN_FILT_NO_WL);

    _opener.unPairNuki();
    if (_opener.pairNuki() == Nuki::PairingResult::Success)
    {
        _paired = true;
        logInfoP("Nuki Opener paired");
        auto addr = _opener.getBleAddress();
        // Remove old device from whitelist (different address = device replaced)
        if (oldAddr != BLEAddress("", 0) && oldAddr != addr)
        {
            logInfoP("Removing old Opener from whitelist: %s", oldAddr.toString().c_str());
            NimBLEDevice::whiteListRemove(oldAddr);
        }
        // Whitelist newly paired device for BLE hardware filtering
        if (addr != BLEAddress("", 0))
        {
            logInfoP("Whitelisting paired Opener: %s", addr.toString().c_str());
            NimBLEDevice::whiteListAdd(addr);
        }
        // Always re-enable whitelist filter — even if addr is empty
        NimBLEDevice::getScan()->setFilterPolicy(BLE_HCI_SCAN_FILT_USE_WL);
        return true;
    }
    else
    {
        _paired = _opener.isPairedWithLock();
        logErrorP("Nuki Opener pairing failed");
        // Re-enable whitelist filter after failed pairing
        NimBLEDevice::getScan()->setFilterPolicy(BLE_HCI_SCAN_FILT_USE_WL);
        return false;
    }
}

void NukiOpenerChannel::processInputKo(GroupObject &ko)
{
    NukiChannel::processInputKo(ko);
    switch (NUK_KoCalcIndex(ko.asap()))
    {
        case NUK_KoUnlock:
        if (ko.value(DPT_Trigger))
        {
            logInfoP("Unlock command received via KNX");
            if (_opener.lockAction(NukiOpener::LockAction::ElectricStrikeActuation) == Nuki::CmdResult::Success)
                logInfoP("Unlock command sent");
            else
                logErrorP("Unlock command failed");
        }
        break;
    }
}

void NukiOpenerChannel::showInformations()
{
    if (_paired)
    {
        logInfoP("Nuki Opener is paired");
    }
    else
    {
        logInfoP("Nuki Opener is not paired");
    }
}