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
    unsigned long _retryInitialization = 0;
    int _retryRequestKeyTurnerState = 0;
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
    bool isNightTimeWindow();
    bool calculateIsNight();
    bool updateConfig();
    bool updateKeyTurnerState(bool lockNGoTimerStartAllowed);
    const char* lockStateToString(NukiLock::LockState state);
    bool _initialized = false;
    void updateTextState();
    void startLockNGoCloseTimer();
    bool useCountDownKoAndStateText();
    void checkAndStartAutoLock();
    void setLockTimer(NukiCountDownType type, unsigned long waitTime);
  
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
};