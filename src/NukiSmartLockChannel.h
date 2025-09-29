#pragma once
#include "NukiChannel.h"
#include "NukiLock.h"
#include "BleScanner.h"

class NukiSmartLockChannel : public NukiChannel, Nuki::SmartlockEventHandler
{
    bool _notified = false;
    unsigned long _retryInitialization = 0;
    unsigned long _lastKeyTurnerStateRequest = 0;
    unsigned long _retryKeyTurnStateRequestMs = 0;
    NukiLock::NukiLock _smartLock;
    NukiLock::Config _config = {0};
    NukiLock::KeyTurnerState _keyTurnerState;
 
    void notify(Nuki::EventType eventType) override;
    bool updateConfig();
    bool getKeyTurnerState();
    bool _initialized = false;
  
public:
    NukiSmartLockChannel(uint8_t _channelIndex);
    virtual void initialize(BleScanner::Scanner& scanner) override;
    virtual void setup() override;
    virtual void loop() override;
    virtual bool pairDevice() override;
    virtual bool processCommand(const std::string cmd, bool diagnoseKo) override;
    virtual void showInformations() override;

};