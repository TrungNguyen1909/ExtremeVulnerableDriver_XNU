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
    
private:
    static IOReturn        sCareless_read (OSObject* target, void* reference, IOExternalMethodArguments* arguments);
    static IOReturn        sCareless_write (OSObject* target, void* reference, IOExternalMethodArguments* arguments);
    IOReturn careless_read(user_addr_t udaddr,size_t len);
    IOReturn careless_write(user_addr_t udaddr,size_t len);
    static const IOExternalMethodDispatch sMethods[2];
public:
    
    virtual bool        initWithTask (task_t owningTask, void* securityToken, UInt32 type, OSDictionary* properties);
    virtual IOReturn    clientClose (void);
    virtual IOReturn    clientDied (void);
    
    virtual bool        start (IOService* provider);
    virtual void        stop (IOService* provider);
    virtual void        free (void);
    
    virtual IOReturn    externalMethod (uint32_t selector, IOExternalMethodArguments* arguments,
                                        IOExternalMethodDispatch* dispatch = 0, OSObject* target = 0, void* reference = 0);
};
