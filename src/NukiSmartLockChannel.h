#pragma once
#include "NukiChannel.h"
#include "NukiLock.h"
#include "BleScanner.h"

class NukiSmartLockChannel : public NukiChannel
{
    unsigned long _retryInitialization = 0;
    unsigned long _lastKeyTurnerStateRequest = 0;
    NukiLock::LockAction _lockAction = NukiLock::LockAction::Undefined;
    unsigned long _retryKeyTurnStateRequestMs = 0;
    NukiLock::NukiLock _smartLock;
    NukiLock::Config _config = {0};
    bool _paired = false;
    NukiLock::KeyTurnerState _keyTurnerState;
    unsigned long _lockTimerStartTime = 0;
    unsigned long _lockTimerDuration = 0;
    unsigned long _lockTimerWaitTimeMs = 0;
    bool _doorOpen = false;
    bool _doorOpenBreak = false;
    bool _nukiLockNgoActive = false;
    bool _isNight = false;
    bool _checkBurglarAlarm = false;
    std::string _textState;
    bool _updateTextState = false;
    long _remaining = 0;
    long _remainingSecOrMin = 0;

 
    NukiLock::LockAction getCurrentValidConfiguredLockAction();
    bool isNightTimeWindow();
    bool calculateIsNight();
    bool updateConfig();
    bool updateKeyTurnerState();
    const char* lockStateToString(NukiLock::LockState state);
    bool _initialized = false;
    void updateTextState();
  
public:
    NukiSmartLockChannel(uint8_t _channelIndex);
    virtual void initialize(BleScanner::Scanner& scanner) override;
    virtual void setup() override;
    virtual void loop() override;
    virtual void loop1() override;
    void updateStates(unsigned long now);
    virtual bool pairDevice() override;
    virtual void processInputKo(GroupObject &ko) override;
    virtual bool processCommand(const std::string cmd, bool diagnoseKo) override;
    virtual void showInformations() override;
    virtual void handleEvent(Nuki::EventType eventType) override;
};