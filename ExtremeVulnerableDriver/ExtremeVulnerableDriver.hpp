#include <IOKit/IOService.h>
#include "ExtremeVulnerableShmemDev.hpp"
#pragma once
#define MAX_SHMEMS 0x10

struct ExtremeVulnerableKernelCommand{
    uint32_t type;
    uint32_t size;
    uint64_t result;
};
struct ExtremeVulnerableSubmitData {
    uint32_t shmem_id;
    uint32_t length;
};

class ExtremeVulnerableDriver : public IOService
{
    OSDeclareDefaultStructors(ExtremeVulnerableDriver)
    ExtremeVulnerableShmemDev* shmems[MAX_SHMEMS];
    uint32_t shmemCount = 0;
    virtual IOReturn processCommand(struct ExtremeVulnerableKernelCommand* cmd, struct ExtremeVulnerableKernelCommand* end);
    virtual IOReturn processCommands(struct ExtremeVulnerableKernelCommand* cmd, struct ExtremeVulnerableKernelCommand* end);
public:
    virtual bool    init (OSDictionary* dictionary = NULL) override;
    virtual void    free (void) override;
    
    virtual IOService*    probe (IOService* provider, SInt32* score) override;
    virtual bool    start (IOService* provider) override;
    virtual void    stop (IOService* provider) override;
    virtual IOReturn createShmem(task_t inTask, vm_size_t size, ExtremeVulnerableShmemData* outShmemData);
    virtual IOReturn deleteShmem(uint32_t shmemID);
    virtual IOReturn processData(struct ExtremeVulnerableSubmitData* data);
};
