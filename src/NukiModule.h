#pragma once
#include "OpenKNX.h"
#include "BleScanner.h"
#include "NukiConstants.h"
#include "NukiLock.h"

class NukiNotifyHandler : public Nuki::SmartlockEventHandler
{
  public:
    bool notified = false;
  public:
    void notify(Nuki::EventType eventType) override
    {
        notified = true;
    }
};

class NukiModule : public OpenKNX::Module
{
  private:
    NukiNotifyHandler notifyHandler = NukiNotifyHandler();
    NukiLock::KeyTurnerState retrievedKeyTurnerState;

    BleScanner::Scanner* scanner = nullptr;
    
    bool keyTurnerState();
  public:
    const std::string name() override;
    const std::string version() override;
    void setup(bool configured) override;
    void loop(bool configured) override;
    void showInformations() override;
    void showHelp() override;
    bool processCommand(const std::string cmd, bool diagnoseKo) override;
 
};

extern NukiModule openknxNukiModule;