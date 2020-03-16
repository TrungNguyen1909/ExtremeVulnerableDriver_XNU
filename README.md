# ExtremeVulnerableDriver

This is a XNU (IOKit) kernel extension inspired by the `hacksysteam/HackSysExtremeVulnerableDriver` written by me (TrungNguyen1909)

**ExtremeVulnerableDriver** is intentionally vulnerable XNU driver developed for security enthusiasts to learn and polish their exploitation skills at Kernel level.

## Types of vulnerabilities

- Stack buffer overflow (based on matesCTF's KSMASH Linux kernel Exploit challenge)

- Heap buffer overflow (stereo-typed version of IOAccelerationFamilyV2. replica of CVE-2020-3837 bug)

- The one I accidentially made and haven't noticed yet.

## Task

The task is simple: Elevate to root. TFP0 if possible.

## Solutions

Solutions for vulnerabilties are put inside [exploits](./exploits) folder. Please include the vulnerability's name you exploited, the macOS build version and first 6 characters of the sha1 of the driver's commit that you worked on in the file name.

This is because offsets may be subjected to changes between macOS or driver version.

## Contributions

Are welcome (including driver code and exploits)

### License

This work is licensed under a [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.html).

### Disclaimer

This product is damn vulnerable. **Never install it on a production machine**, as it will be compromised. It is recommended to use a virtual machine.

We do not take responsibility for the way in which any one uses this application (ExtremeVulnerableDriver). We have made the purposes of the application clear and it should not be used maliciously. We have given warnings and taken measures to prevent users from installing ExtremeVulnerableDriver on to production machine. If your machine is compromised via an installation of ExtremeVulnerableDriver, it is not our responsibility, it is the responsibility of the person/s who uploaded and installed it.

---
Happy pwning~
