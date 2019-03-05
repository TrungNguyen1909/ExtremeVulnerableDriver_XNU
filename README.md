# ExtremeVulnerableDriver

This is an XNU version for the HackSysExtremeVulnerableDriver

Currently, there is only an buffer overflow demo.

The task is simple: Elevate to root. Period

The solution for this problem was written for 

```
Darwin Kernel Version 18.2.0: root:xnu-4903.231.4~2/RELEASE_X86_64 x86_64
```

But everything will be the same on other XNU version, just update the offset.

I don't think I will release any other demo because as long as we don't touch the Mach subsystem, It should be the _same_ with `invictus-0x90/vulnerable_linux_driver`

## Exploit Reference

[saelo's IPwnKit Solution](https://gist.github.com/saelo/0a85f22c8a02f3a314661edd715900d3)

[Brandon Azad CVE-2016-1828 writeup](https://bazad.github.io/2016/05/mac-os-x-use-after-free/#building-the-rop-stack)
