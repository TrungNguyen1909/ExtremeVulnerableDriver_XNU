#include "ExtremeVulnerableDriver.hpp"
#include "ExtremeVulnerableDriverUserClient.hpp"
#include <IOKit/IOLib.h>
#include <IOKit/IOBufferMemoryDescriptor.h>

// Define the superclass
#define super IOService

OSDefineMetaClassAndStructors(ExtremeVulnerableDriver, IOService)

bool ExtremeVulnerableDriver::init (OSDictionary* dict)
{
    bool res = super::init(dict);
    IOLog("ExtremeVulnerableDriver::init\n");
    this->shmemCount = 0;
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

IOReturn ExtremeVulnerableDriver::createShmem(task_t inTask, vm_size_t size, ExtremeVulnerableShmemData *outShmemData){
    if(size >= 0x10000001){
        return kIOReturnBadArgument;
    }
    IOLog("ExtremeVulnerableDriver::createShmem\n");
    if(this->shmemCount>= MAX_SHMEMS){
        return kIOReturnNoSpace;
    }
    ExtremeVulnerableShmemDev* shmem = ExtremeVulnerableShmemDev::withTask(inTask,size);
    if(!shmem){
        return kIOReturnNoMemory;
    }
    this->shmemCount++;
    for(int i=0;i<MAX_SHMEMS;i++)
        if(this->shmems[i]==nullptr){
            this->shmems[i] = shmem;
            outShmemData->shmem_id = i;
            break;
        }
    outShmemData->data = shmem->getClientData();
    outShmemData->length = shmem->getCapacity();
    return kIOReturnSuccess;
}

IOReturn ExtremeVulnerableDriver::deleteShmem(uint32_t shmemID){
    if(shmemID >= this->shmemCount || !this->shmems[shmemID]){
        return kIOReturnBadArgument;
    }
    this->shmemCount--;
    this->shmems[shmemID]->release();
    this->shmems[shmemID] = nullptr;
    return kIOReturnSuccess;
}

IOReturn ExtremeVulnerableDriver::processData(struct ExtremeVulnerableSubmitData* data){
    uint32_t shmemID = data->shmem_id;
    if(shmemID >= this->shmemCount || !this->shmems[shmemID]){
        return kIOReturnBadArgument;
    }
    ExtremeVulnerableShmemDev* shmem1 = this->shmems[shmemID];
    ExtremeVulnerableKernelCommand* cmd = (ExtremeVulnerableKernelCommand*)shmem1->getKernelData();
    mach_vm_size_t length = min(shmem1->getCapacity(),data->length);
    return this->processCommands(cmd, cmd+length);
}

IOReturn ExtremeVulnerableDriver::processCommand(struct ExtremeVulnerableKernelCommand *cmd, struct ExtremeVulnerableKernelCommand *end){
    if((mach_vm_address_t)end - (mach_vm_address_t)cmd < sizeof(struct ExtremeVulnerableKernelCommand)){
        return kIOReturnBadArgument;
    }
    switch (cmd->type) {
        case 1:
            IOLog("Hello from ExtremeVulnerableDriver::processCommand\n");
            break;
        case 2:
            ExtremeVulnerableKernelCommandWithResult* cmdWithResult = (ExtremeVulnerableKernelCommandWithResult*)cmd;
            cmdWithResult->result = mach_absolute_time();
            break;
    }
    return kIOReturnSuccess;
}

IOReturn ExtremeVulnerableDriver::processCommands(struct ExtremeVulnerableKernelCommand *cmd, struct ExtremeVulnerableKernelCommand *end){
    if(cmd < end){
        struct ExtremeVulnerableKernelCommand *curCmd = cmd;
        while(1){
            if((mach_vm_address_t)curCmd+sizeof(struct ExtremeVulnerableKernelCommand) > (mach_vm_address_t)end){
                return kIOReturnSuccess;
            }
            if(curCmd->size < sizeof(struct ExtremeVulnerableKernelCommand) || (mach_vm_address_t)curCmd+curCmd->size > (mach_vm_address_t)end){
                return kIOReturnSuccess;
            }
            this->processCommand(curCmd, curCmd+curCmd->size);
            curCmd = curCmd+curCmd->size;
            if((mach_vm_address_t)curCmd>=(mach_vm_address_t)end){
                return kIOReturnSuccess;
            }
        }
    } else return kIOReturnBadArgument;
    
}
