#include "ExtremeVulnerableDriver.hpp"
#include <IOKit/IOLib.h>

// Define the superclass
#define super IOService

OSDefineMetaClassAndStructors(ExtremeVulnerableDriver, IOService)

bool ExtremeVulnerableDriver::init (OSDictionary* dict)
{
    bool res = super::init(dict);
    IOLog("ExtremeVulnerableDriver::init\n");
    return res;
}

void ExtremeVulnerableDriver::free (void)
{
    IOLog("ExtremeVulnerableDriver::free\n");
    super::free();
}

IOService* ExtremeVulnerableDriver::probe (IOService* provider, SInt32* score)
{
    IOService *res = super::probe(provider, score);
    IOLog("ExtremeVulnerableDriver::probe\n");
    return res;
}

bool ExtremeVulnerableDriver::start (IOService *provider)
{
    bool res = super::start(provider);
    IOLog("ExtremeVulnerableDriver::start\n");
    setProperty("IOUserClientClass", "ExtremeVulnerableDriverUserClient");
    registerService();
    return res;
}

void ExtremeVulnerableDriver::stop (IOService *provider)
{
    IOLog("ExtremeVulnerableDriver::stop\n");
    super::stop(provider);
}
