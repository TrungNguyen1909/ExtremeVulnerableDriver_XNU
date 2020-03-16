//
//  ExtremeVulnerableDriverUserClient.hpp
//  ExtremeVulnerableDriver
//
//  Created by Nguyễn Hoàng Trung on 3/2/19.
//  Copyright © 2019 Trung Nguyen. All rights reserved.
//
#include <IOKit/IOUserClient.h>
#include "ExtremeVulnerableDriver.hpp"

class ExtremeVulnerableDriverUserClient : public IOUserClient
{
    OSDeclareDefaultStructors(ExtremeVulnerableDriverUserClient)
    task_t owningTask;
private:
    static IOReturn        sCareless_read (OSObject* target, void* reference, IOExternalMethodArguments* arguments);
    static IOReturn        sCareless_write (OSObject* target, void* reference, IOExternalMethodArguments* arguments);
    static IOReturn        sCreateShmem (OSObject* target, void* reference, IOExternalMethodArguments* arguments);
    static IOReturn        sDeleteShmem (OSObject* target, void* reference, IOExternalMethodArguments* arguments);
    static IOReturn        sProcessData (OSObject* target, void* reference, IOExternalMethodArguments* arguments);
    IOReturn careless_read(user_addr_t udaddr,size_t len);
    IOReturn careless_write(user_addr_t udaddr,size_t len);
    IOReturn createShmem(task_t inTask, vm_size_t size, ExtremeVulnerableShmemData* outShmemData);
    IOReturn deleteShmem(uint32_t shmemID);
    IOReturn processData(struct ExtremeVulnerableSubmitData* data);
    static const IOExternalMethodDispatch sMethods[5];
public:
    
    virtual bool        initWithTask (task_t owningTask, void* securityToken, UInt32 type, OSDictionary* properties) override;
    virtual IOReturn    clientClose (void) override;
    virtual IOReturn    clientDied (void) override;
    
    virtual bool        start (IOService* provider) override;
    virtual void        stop (IOService* provider) override;
    virtual void        free (void) override;
    
    virtual IOReturn    externalMethod (uint32_t selector, IOExternalMethodArguments* arguments,
                                        IOExternalMethodDispatch* dispatch = 0, OSObject* target = 0, void* reference = 0) override;
};
