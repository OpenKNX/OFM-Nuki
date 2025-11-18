#include "NukiChannel.h"

NukiChannel::NukiChannel(uint8_t channelIndex, const char* type) : Channel()
{
    _channelIndex = channelIndex;
    _type = type;   
    _deviceName = "OpenKNX " + std::to_string(channelIndex + 1);
}

const std::string NukiChannel::name()
{
    return _type;
}

void NukiChannel::notify(Nuki::EventType eventType)
{
    logDebugP("Event received: %d", (int)eventType);
    _eventType = eventType;
    _notified = true;
}

void NukiChannel::initialize(BleScanner::Scanner& scanner)
{

}

void NukiChannel::setup()
{
}

void NukiChannel::loop()
{
    if (_notified)
    {
        _notified = false;
        handleEvent(_eventType);
    }
}

void NukiChannel::processInputKo(GroupObject &ko)
{
}

bool NukiChannel::processCommand(const std::string cmd, bool diagnoseKo)
{
    if (cmd == "")
    {
        showInformations();
        return true;
    }
    if (cmd == "pair")
    {
        pairDevice();
        return true;
    }
    return false;
}
