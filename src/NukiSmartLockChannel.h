#pragma once
#include "NukiChannel.h"
#include "NukiLock.h"
#include "BleScanner.h"

class NukiSmartLockChannel : public NukiChannel
{
    unsigned long _retryInitialization = 0;
    unsigned long _lastKeyTurnerStateRequest = 0;
    unsigned long _retryKeyTurnStateRequestMs = 0;
    NukiLock::NukiLock _smartLock;
    NukiLock::Config _config = {0};
    bool _paired = false;
    NukiLock::KeyTurnerState _keyTurnerState;
    unsigned long _lockTimerStartTime = 0;
    unsigned long _lockTimerDuration = 0;
    unsigned long _lockTimerWaitTimeMs = 0;
    bool _doorOpen = false;
    bool _lockAndGoDoorOpen = false;

 
    bool updateConfig();
    bool updateKeyTurnerState();
    bool _initialized = false;
  
public:
    NukiSmartLockChannel(uint8_t _channelIndex);
    virtual void initialize(BleScanner::Scanner& scanner) override;
    virtual void setup() override;
    virtual void loop() override;
    virtual bool pairDevice() override;
    virtual void processInputKo(GroupObject &ko) override;
    virtual bool processCommand(const std::string cmd, bool diagnoseKo) override;
    virtual void showInformations() override;
    virtual void handleEvent(Nuki::EventType eventType) override;
};