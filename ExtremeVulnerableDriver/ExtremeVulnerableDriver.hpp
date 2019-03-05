#include <IOKit/IOService.h>

class ExtremeVulnerableDriver : public IOService
{
    OSDeclareDefaultStructors(ExtremeVulnerableDriver)
    
public:
    virtual bool    init (OSDictionary* dictionary = NULL);
    virtual void    free (void);
    
    virtual IOService*    probe (IOService* provider, SInt32* score);
    virtual bool    start (IOService* provider);
    virtual void    stop (IOService* provider);
    
};
