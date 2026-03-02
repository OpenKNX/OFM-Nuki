#pragma once
#include "BleScanner.h"
#include "NukiChannel.h"
#include "NukiLock.h"
#include "freertos/portmacro.h"  // portMUX_TYPE, portMUX_INITIALIZER_UNLOCKED

enum NukiCountDownType
{
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
    
    // volatile: processInputKo() runs on Core 1, loop1() runs on Core 0.
    // Without volatile the compiler may cache _lockAction in a register and
    // Core 0 never sees the value written by Core 1 — lock/unlock commands
    // would be silently dropped.

    volatile NukiLock::LockAction _lockAction = NukiLock::LockAction::Undefined;
    unsigned long _retryKeyTurnStateRequestMs = 0;
    volatile unsigned long _lastNotificationReceivedTimestamp = 0;
    volatile unsigned long _lastKeyTurnerStateRequest = 0;
    volatile unsigned long _lockActionTimerStart = 0;
    unsigned long _lockActionTimerWaitTime = 0;
    void startLockActionTimer(bool locking, unsigned long waitTimeMs);
    void stopLockActionTimer();

    NukiLock::NukiLock _smartLock;
    NukiLock::Config _config = {0};
    volatile bool _paired = false;
    volatile bool _unlockedByOFM_Nuki = false;
    NukiLock::KeyTurnerState _keyTurnerState;
    portMUX_TYPE _kts_spinlock = portMUX_INITIALIZER_UNLOCKED;
    volatile unsigned long _lockTimerStartTime = 0;
    unsigned long _lockTimerDuration = 0;
    volatile unsigned long _lockTimerWaitTimeMs = 0;
    volatile NukiCountDownType _countDownType = NukiCountDownType::NukiCountDownType_NotRunning;
    volatile bool _doorOpen = false;
    volatile bool _doorOpenBreak = false;
    volatile bool _isNight = false;
    unsigned long _lastNightCalcMs = 0; // last calculateIsNight() call — 60 s cache
    bool _nightCalcCache = false;       // cached result of calculateIsNight()
    volatile bool _checkBurglarAlarm = false;
    char _textState[15] = {}; // DPT_String_8859_1 = 14 chars + null; avoids heap allocs
    volatile bool _updateTextState = false; // written by Core 0 (loop1), read/cleared by Core 1 (loop)
    long _remaining = 0;
    long _remainingSeconds = 0;
    volatile bool _keyTurnerStateInitialized = false;
    BleScanner::Scanner* _bleScanner = nullptr;

    NukiLock::LockAction getCurrentValidConfiguredLockAction();
    void lockAction(NukiLock::LockAction action);
    bool isNightTimeWindow();
    bool calculateIsNight();
    bool updateConfig();
    bool updateKeyTurnerState();
    void updateInternalStateFromKeyTurnerState(bool lockNGoTimerStartAllowed);
    const char* lockStateToString(NukiLock::LockState state);
    volatile bool _initialized = false; // written by Core 0 (loop1), read by Core 1 (loop)
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
#ifdef OPENKNX_DUALCORE
    virtual void loop1() override; // delegates to loopBle()
#endif
    virtual void loopBle() override; // BLE work — used by OPENKNX_DUALCORE loop1() and NUKI_ASYNC_LOOP1 task
    void updateStates(unsigned long now);
    virtual bool pairDevice() override;
    virtual void processInputKo(GroupObject& ko) override;
    virtual bool processCommand(const std::string cmd, bool diagnoseKo) override;
    virtual void showInformations() override;
    virtual void handleEvent(Nuki::EventType eventType) override;
    virtual bool isInitialStateFetched() const override;
};
