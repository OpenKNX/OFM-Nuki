#pragma once
#include "OpenKNX.h"
#include "NukiConstants.h"
#include "BleScanner.h"


class NukiChannel : public OpenKNX::Channel
{   
protected:
    std::string _name;
public:
    virtual const std::string name() override;
    NukiChannel(uint8_t channelIndex, const char* type);
    virtual void initialize(BleScanner::Scanner& scanner);
    void setup() override;
    void loop() override;
    virtual void processInputKo(GroupObject &ko) override;
    virtual bool processCommand(const std::string cmd, bool diagnoseKo);
    virtual void showInformations() = 0;
    virtual bool pairDevice() = 0;
}; 