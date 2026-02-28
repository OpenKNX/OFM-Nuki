#pragma once
#include "OpenKNX.h"
#include "ChannelOwnerModule.h"

// Delay in ms after boot before the BLE stack is initialized.
// Allows supply voltage to settle before the BLE radio draws its startup current peak.
// Override via build flag: -D BLE_INIT_DELAY_MS=5000
#ifndef BLE_INIT_DELAY_MS
  #define BLE_INIT_DELAY_MS 3000
#endif

// Timeout in ms after BLE init to wait for all paired channels to fetch their initial
// state before switching to low-power scan mode (30% duty cycle).
// Increase if Nuki is far away or slow to respond. Override: -D BLE_INITIAL_STATE_TIMEOUT_MS=120000
#ifndef BLE_INITIAL_STATE_TIMEOUT_MS
  #define BLE_INITIAL_STATE_TIMEOUT_MS 60000
#endif

// BLE scan parameters during boot (phase 1: fast, until initial state is fetched).
// interval = time between scan window starts [units of 0.625ms], 23 = 14.375ms → 100% duty with window=23
// window   = how long the radio listens per interval [units of 0.625ms]
// 23/23 = 100% duty cycle — radio permanently on for fastest possible first connection.
// Override: -D BLE_SCAN_INTERVAL_BOOT=23  -D BLE_SCAN_WINDOW_BOOT=23
#ifndef BLE_SCAN_INTERVAL_BOOT
  #define BLE_SCAN_INTERVAL_BOOT 23
#endif
#ifndef BLE_SCAN_WINDOW_BOOT
  #define BLE_SCAN_WINDOW_BOOT 23
#endif

// BLE scan parameters during normal operation (phase 2: low-power, after initial state fetched).
// 160/48 = 100ms interval / 30ms window → 30% duty cycle.
// Nuki advertises every ~200ms — a 30ms window every 100ms reliably catches each burst.
// Saves ~70% BLE radio power vs 100% duty cycle.
// Override: -D BLE_SCAN_INTERVAL_LP=160  -D BLE_SCAN_WINDOW_LP=48
#ifndef BLE_SCAN_INTERVAL_LP
  #define BLE_SCAN_INTERVAL_LP 160
#endif
#ifndef BLE_SCAN_WINDOW_LP
  #define BLE_SCAN_WINDOW_LP 48
#endif

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
    unsigned long _bleInitDeadline = 0;          // deferred BLE startup: millis() target after boot stabilization
    unsigned long _initialStateFetchDeadline = 0; // deadline for switching to low-power BLE scan (set after BLE init)
    void initializeBleScanner();
    
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