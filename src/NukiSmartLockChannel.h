#pragma once
#include "NukiChannel.h"
#include "NukiLock.h"
#include "BleScanner.h"

enum NukiCountDownType {
    NukiCountDownType_NotRunning = 0,
    NukiCountDownType_AutoLock = 1,
    NukiCountDownType_NukiLockNGo = 2,
    NukiCountDownType_OpenKNXLockNGo = 3,
};

class NukiSmartLockChannel : public NukiChannel
{
    static const unsigned long KeyTurnTimeMs;
    unsigned long _retryInitialization = 0;
    int _retryRequestKeyTurnerState = 0;
    unsigned long _lastKeyTurnerStateRequest = 0;
    NukiLock::LockAction _lockAction = NukiLock::LockAction::Undefined;
    unsigned long _retryKeyTurnStateRequestMs = 0;
    unsigned long _lastNotificationReceivedTimestamp = 0;
    unsigned long _lockActionTimerStart = 0;
    unsigned long _lockActionTimerWaitTime = 0;
    void startLockActionTimer(bool locking, unsigned long waitTimeMs);
    void stopLockActionTimer();

    

    NukiLock::NukiLock _smartLock;
    NukiLock::Config _config = {0};
    bool _paired = false;
    bool _unlockedByOFM_Nuki = false;
    NukiLock::KeyTurnerState _keyTurnerState;
    unsigned long _lockTimerStartTime = 0;
    unsigned long _lockTimerDuration = 0;
    unsigned long _lockTimerWaitTimeMs = 0;
    NukiCountDownType _countDownType = NukiCountDownType::NukiCountDownType_NotRunning;
    bool _doorOpen = false;
    bool _doorOpenBreak = false;
    bool _isNight = false;
    bool _checkBurglarAlarm = false;
    std::string _textState;
    bool _updateTextState = false;
    long _remaining = 0;
    long _remainingSeconds = 0;
    bool _keyTurnerStateInitialized = false;
    BleScanner::Scanner* _bleScanner = nullptr;

 
    NukiLock::LockAction getCurrentValidConfiguredLockAction();
    void lockAction(NukiLock::LockAction action);
    bool isNightTimeWindow();
    bool calculateIsNight();
    bool updateConfig();
    bool updateKeyTurnerState();
    void updateInternalStateFromKeyTurnerState(bool lockNGoTimerStartAllowed);
    const char* lockStateToString(NukiLock::LockState state);
    bool _initialized = false;
    void updateTextState();
    void startOpenKNXLockNGoCloseTimer(const char* reason);
    bool useCountDownKoAndStateText();
    void checkAndStartAutoLock();
    void setLockTimer(NukiCountDownType type, unsigned long waitTime, const char* reason);
  
public:
    NukiSmartLockChannel(uint8_t _channelIndex);
    virtual void initialize(BleScanner::Scanner& scanner) override;
    virtual void setup() override;
    virtual void loop() override;
#ifndef OPENKNX_DUALCORE
    virtual void loop1();
#else
    virtual void loop1() override;
#endif
    void updateStates(unsigned long now);
    virtual bool pairDevice() override;
    virtual void processInputKo(GroupObject &ko) override;
    virtual bool processCommand(const std::string cmd, bool diagnoseKo) override;
    virtual void showInformations() override;
    virtual void handleEvent(Nuki::EventType eventType) override;
    virtual bool isInitialStateFetched() const override;
};
