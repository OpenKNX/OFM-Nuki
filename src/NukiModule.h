#pragma once
#include "OpenKNX.h"
#include "ChannelOwnerModule.h"
#include "BleScanner.h"

class NukiModule : public NUKChannelOwnerModule
{
  private:
    BleScanner::Scanner* scanner = nullptr;
    
  public:
    const std::string name() override;
    const std::string version() override;
    virtual OpenKNX::Channel* createChannel(uint8_t _channelIndex /* this parameter is used in macros, do not rename */) override; 

    void setup() override;
    void loop() override;
    void showInformations() override;
    void showHelp() override;
    bool processCommand(const std::string cmd, bool diagnoseKo) override;
 
};

extern NukiModule openknxNukiModule;