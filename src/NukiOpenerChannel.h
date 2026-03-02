#pragma once
#include "NukiChannel.h"
#include "NukiOpener.h"

class NukiOpenerChannel : public NukiChannel
{
    NukiOpener::NukiOpener _opener;
    unsigned long _lastBatteryRequest = 0;
    volatile bool _paired = false;                 // true if we have valid credentials and are paired with a Nuki Opener; false if not paired or pairing failed
    volatile bool _openerStateInitialized = false; // becomes true once we have successfully contacted the Nuki Opener after boot, either via loopBle() or handleEvent() — means we know the initial state of the Opener and can switch BLE scan duty cycle from 100% to 30%
    volatile bool _pendingElectricStrike = false;  // true if an unlock command was received via KNX and is pending execution

  public:
    NukiOpenerChannel(uint8_t _channelIndex);
    virtual void setup() override;
    virtual void initialize(BleScanner::Scanner &scanner) override;
    virtual void loop() override;
    virtual void loopBle() override; // LoopBle: Supports both dual-core (loop1) and single-core (loop) targets; delegates to loopBle() for actual BLE work to avoid concurrent BLE calls from the wrong task (undefined behaviour in NimBLE stack)
#ifdef OPENKNX_DUALCORE
    virtual void loop1() override; // delegates to loopBle() on dual-core targets
#endif
    virtual bool pairDevice() override;
    virtual void processInputKo(GroupObject &ko) override;
    virtual void showInformations() override;
    virtual void handleEvent(Nuki::EventType eventType) override;
    virtual bool isInitialStateFetched() const override;
};
