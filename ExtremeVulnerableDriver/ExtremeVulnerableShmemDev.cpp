//
//  ExtremeVulnerableShmemDev.cpp
//  ExtremeVulnerableDriver
//
//  Created by Trung Nguyễn on 15/3/20.
//  Copyright © 2020 Trung Nguyen. All rights reserved.
//

#include <IOKit/IOLib.h>
#include <IOKit/IOBufferMemoryDescriptor.h>
#include "ExtremeVulnerableShmemDev.hpp"
#include <libkern/c++/OSContainers.h>

OSDefineMetaClassAndStructors(ExtremeVulnerableShmemDev, OSObject)
#define super OSObject

ExtremeVulnerableShmemDev* ExtremeVulnerableShmemDev::withTask(task_t inTask, vm_size_t capacity){
    ExtremeVulnerableShmemDev *me = new ExtremeVulnerableShmemDev;
    if (me && !me->initWithTask(inTask, capacity)){
        me->release();
        me = nullptr;
    }
    return me;
}
bool ExtremeVulnerableShmemDev::initWithTask(task_t inTask, vm_size_t capacity){
    super::init();
    if(!inTask || capacity >= 0x10000001){
        return false;
    }
    IOLog("ExtremeVulnerableShmemDev::initWithTask\n");
    IOBufferMemoryDescriptor* shmem = IOBufferMemoryDescriptor::inTaskWithOptions(inTask, kIOMemoryPageable| kIODirectionInOut | kIOMemoryKernelUserShared , capacity);
    if(!shmem){
        return false;
    }
    this->kernelData = 0;
    this->desc = shmem;
    return kIOReturnSuccess;
}

mach_vm_address_t ExtremeVulnerableShmemDev::getClientData(){
    return (mach_vm_address_t)this->desc->getBytesNoCopy();
}

mach_vm_address_t ExtremeVulnerableShmemDev::getKernelData(){
    if(!this->kernelData){
        this->kernelData = this->desc->map()->getAddress();
    }
    return this->kernelData;
}

mach_vm_size_t ExtremeVulnerableShmemDev::getCapacity(){
    return this->desc->getCapacity();
}

void ExtremeVulnerableShmemDev::free(){
    super::free();
    this->desc->release();
    return;
}
