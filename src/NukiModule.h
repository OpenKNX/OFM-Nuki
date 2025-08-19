#pragma once
#include "OpenKNX.h"

class NukiModule : public OpenKNX::Module
{
  public:
    const std::string name() override;
    const std::string version() override;
    void showInformations() override;
    void showHelp() override;
    bool processCommand(const std::string cmd, bool diagnoseKo) override;
 
};

extern NukiModule openknxNukiModule;