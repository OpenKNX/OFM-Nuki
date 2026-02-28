#pragma once
#include "NukiChannel.h"
#include "NukiOpener.h"

class NukiOpenerChannel : public NukiChannel
{
    NukiOpener::NukiOpener _opener;
    unsigned long _lastBatteryRequest = 0;
    bool _paired = false;
    bool _openerStateInitialized = false;

public:
    NukiOpenerChannel(uint8_t _channelIndex); 
    virtual void setup() override;
    virtual void initialize(BleScanner::Scanner& scanner) override;
    virtual void loop() override;
    virtual bool pairDevice() override;
    virtual void processInputKo(GroupObject &ko) override;
    virtual void showInformations() override;
    virtual void handleEvent(Nuki::EventType eventType) override;
    virtual bool isInitialStateFetched() const override;
};