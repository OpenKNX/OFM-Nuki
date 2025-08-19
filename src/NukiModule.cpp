#include "NukiModule.h"


const std::string NukiModule::name()
{
    return "Nuki";
}

void NukiModule::showInformations()
{
}

const std::string NukiModule::version()
{
#ifdef MODULE_NukiModule_Version
    return MODULE_NukiModule_Version;
#else
    // hides the module in the version output on the console, because the firmware version is sufficient.
    return "";
#endif
}

void NukiModule::showHelp()
{
}

bool NukiModule::processCommand(const std::string cmd, bool diagnoseKo)
{
    
    return false;
}
 

NukiModule openknxNukiModule;