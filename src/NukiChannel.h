#pragma once
#include "OpenKNX.h"
#include "NukiConstants.h"
#include "NukiDataTypes.h"
#include "BleScanner.h"

// -------------------------------------------------------------------------
// Nuki timing / power tuning — all values configurable via build flags
// -------------------------------------------------------------------------

// SmartLock: how often to poll state when no BLE notifications are received.
// Each poll opens a BLE connection — longer interval = less power consumption.
// Override: -D NUKI_STATE_POLL_INTERVAL_MS=43200000
#ifndef NUKI_STATE_POLL_INTERVAL_MS
  #define NUKI_STATE_POLL_INTERVAL_MS (600000UL * 12) // 12 hours
#endif

// SmartLock: how long after the last notification before assuming Nuki will
// send notifications again and switching back to the long poll interval.
// Override: -D NUKI_NOTIFICATION_TIMEOUT_MS=120000
#ifndef NUKI_NOTIFICATION_TIMEOUT_MS
  #define NUKI_NOTIFICATION_TIMEOUT_MS 120000UL // 2 minutes
#endif

// SmartLock: how soon to re-poll state after receiving a notification.
// Nuki needs a brief settle time before its state reflects the new action.
// Override: -D NUKI_STATE_RETRY_AFTER_NOTIFICATION_MS=30000
#ifndef NUKI_STATE_RETRY_AFTER_NOTIFICATION_MS
  #define NUKI_STATE_RETRY_AFTER_NOTIFICATION_MS 30000UL // 30 seconds
#endif

// SmartLock: retry interval for re-initialization after a failed BLE init.
// Override: -D NUKI_REINIT_INTERVAL_MS=600000
#ifndef NUKI_REINIT_INTERVAL_MS
  #define NUKI_REINIT_INTERVAL_MS 600000UL // 10 minutes
#endif

// SmartLock: re-poll interval while Nuki is in a transitional state (Unlocking/Locking/Unlatching).
// Short enough to catch the final state quickly without hammering the lock.
// Override: -D NUKI_STATE_INTERMEDIATE_POLL_MS=5000
#ifndef NUKI_STATE_INTERMEDIATE_POLL_MS
  #define NUKI_STATE_INTERMEDIATE_POLL_MS 5000UL // 5 seconds
#endif

// Opener: how often to request a battery report.
// Override: -D NUKI_OPENER_BATTERY_CHECK_INTERVAL_MS=86400000
#ifndef NUKI_OPENER_BATTERY_CHECK_INTERVAL_MS
  #define NUKI_OPENER_BATTERY_CHECK_INTERVAL_MS (3600000UL * 24) // 24 hours
#endif
// -------------------------------------------------------------------------


class NukiChannel : public OpenKNX::Channel, protected Nuki::SmartlockEventHandler
{   
private:     
    bool _notified = false;
    Nuki::EventType _eventType;
    void notify(Nuki::EventType eventType) override;
    std::string _type;
protected:
    std::string _deviceName;
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
    virtual void handleEvent(Nuki::EventType eventType) = 0;
    // Returns true once the initial device state has been fetched after boot.
    // Unpaired channels return true immediately (nothing to wait for).
    // Used by NukiModule to switch BLE scan from 100% to 30% duty cycle.
    virtual bool isInitialStateFetched() const { return true; }
};
