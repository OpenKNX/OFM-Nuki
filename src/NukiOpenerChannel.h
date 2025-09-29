#pragma once
#include "NukiChannel.h"
#include "NukiOpener.h"

class NukiOpenerChannel : public NukiChannel 
{
    NukiOpener::NukiOpener _opener;
public:
    NukiOpenerChannel(uint8_t _channelIndex);
 
    virtual void setup() override;
    virtual void initialize(BleScanner::Scanner& scanner) override;
    virtual void loop() override;
    virtual bool pairDevice() override;
    virtual void showInformations() override;

};