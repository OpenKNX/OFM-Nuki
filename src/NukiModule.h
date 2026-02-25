#pragma once
#include "OpenKNX.h"
#include "ChannelOwnerModule.h"

#if !defined(OPENKNX_DUALCORE)
#warning "It is strongly recommended to enable OPENKNX_DUALCORE for NukiModule"
#endif

namespace BleScanner {
    class Scanner;
}

class NukiModule : public NUKChannelOwnerModule
{
  private:
    BleScanner::Scanner* scanner = nullptr;
    unsigned long _startFastBLEScanningTimer = 0;
    
  public:
    const std::string name() override;
    const std::string version() override;
    virtual OpenKNX::Channel* createChannel(uint8_t _channelIndex /* this parameter is used in macros, do not rename */) override; 

    void setup() override;
    void loop() override;
    void showInformations() override;
    void showHelp() override;
    bool processCommand(const std::string cmd, bool diagnoseKo) override;
    bool processFunctionProperty(uint8_t objectIndex, uint8_t propertyId, uint8_t length, uint8_t *data, uint8_t *resultData, uint8_t &resultLength) override;
 
};

extern NukiModule openknxNukiModule;