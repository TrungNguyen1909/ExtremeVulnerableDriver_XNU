//
//  ExtremeVulnerableShmemDev.hpp
//  ExtremeVulnerableDriver
//
//  Created by Trung Nguyễn on 15/3/20.
//  Copyright © 2020 Trung Nguyen. All rights reserved.
//

#include <IOKit/IOLib.h>
#include <libkern/c++/OSContainers.h>
#include <IOKit/IOBufferMemoryDescriptor.h>

struct ExtremeVulnerableShmemData{
    uint32_t shmem_id;
    mach_vm_address_t data;
    vm_size_t length;
};

class ExtremeVulnerableShmemDev : public OSObject
{
    OSDeclareDefaultStructors(ExtremeVulnerableShmemDev)
    IOBufferMemoryDescriptor* desc = nullptr;
    mach_vm_address_t kernelData = 0;
protected:
    virtual void free() APPLE_KEXT_OVERRIDE;
public:
    virtual bool initWithTask(task_t inTask, vm_size_t capacity);
    virtual mach_vm_address_t getKernelData();
    virtual mach_vm_address_t getClientData();
    virtual mach_vm_size_t getCapacity();

    static ExtremeVulnerableShmemDev* withTask(task_t inTask, vm_size_t capacity);
};

