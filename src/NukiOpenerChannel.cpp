#include "NukiOpenerChannel.h"

NukiOpenerChannel::NukiOpenerChannel(uint8_t _channelIndex) : NukiChannel(_channelIndex, "Opener"),
  _opener(_name, 2035000 + _channelIndex)
{
}

void NukiOpenerChannel::setup()
{
    NukiChannel::setup();
}

void NukiOpenerChannel::initialize(BleScanner::Scanner& scanner)
{
    NukiChannel::initialize(scanner);
    //_opener.registerLogger(&nukiLogger);
    _opener.registerBleScanner(&scanner);
    _opener.initialize();
}

void NukiOpenerChannel::loop()
{
    NukiChannel::loop();
}

bool NukiOpenerChannel::pairDevice()
{
    if (_opener.pairNuki() == Nuki::PairingResult::Success)
    {
        logInfoP("Nuki Opener paired");
        return true;
    }
    else
    {
        logErrorP("Nuki Opener pairing failed");
        return false;
    }
}

void NukiOpenerChannel::showInformations()
{
    if (_opener.isPairedWithLock())
    {
        logInfoP("Nuki Opener is paired");
    }
    else
    {
        logInfoP("Nuki Opener is not paired");
    }
}
