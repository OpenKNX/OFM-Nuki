#include "NukiChannel.h"

NukiChannel::NukiChannel(uint8_t channelIndex, const char* type) : Channel()
{
    _channelIndex = channelIndex;
    _name = std::to_string(channelIndex + 1) + "-" + type;   
}

const std::string NukiChannel::name()
{
    return _name;
}

void NukiChannel::initialize(BleScanner::Scanner& scanner)
{

}

void NukiChannel::setup()
{
}

void NukiChannel::loop()
{
}

void NukiChannel::processInputKo(GroupObject &ko)
{
}

bool NukiChannel::processCommand(const std::string cmd, bool diagnoseKo)
{
    if (cmd == "")
    {
        showInformations();
    }
    if (cmd == "pair")
    {
        pairDevice();
        return true;
    }
    return false;
}
