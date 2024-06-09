# Goldbach Conjecture Verifier

Goldbach Conjecture Verifier, a tool to test the  Goldbach's Conjecture.

This verifier can test Goldbach's Conjecture. Can running in frontend or background, and configure settings as needed.

## build

```bash
wget https://github.com/no-passwd/GoldBachCtl/archive/refs/heads/main.zip
unzip main.zip
cd GoldBachCtl-main
gcc GoldBachCtl.c -o GoldBachCtl
```

## Usage

### Simple using(Default background)
```bash
~$ ./GoldBachCtl start
~$ ./GoldBachCtl status
```

### Using config(Enable debug)
```bash
~$ ./GoldBachCtl config
Please Enter Memory upper limit, the default is: 18446744073709551418: 10000
Turn on debug mode (foreground running mode)?, default 0, Enter 1 to Enable: 1
./GoldBachCtl start
```

### Defaults to background mode

### Limit cpu usage under 20%

```bash
cpulimit --limit 20 -- ./GoldBachCtl start
```

### Simple using

## Command

To operate the Goldbach Conjecture Verifier, use the following commands with the appropriate argument :

**Start Verification:**
```bash
./GoldBachCtl start
```
This command initiates the verification process.

**Stop Verification:**
```bash
./GoldBachCtl stop
```
This command stops the verification process.

**Suspend Verification:**
```bash
./GoldBachCtl suspend
```
Temporarily pause the background verification process.

**Resume Verification:**
```bash
./GoldBachCtl resume
```
Resume the background verification process after it has been suspended.

**Check Status:**
```bash
./GoldBachCtl status
```
Display the status of the background verification process.

**Configure Settings:**
```bash
./GoldBachCtl config
```
Change the configuration settings for the verifier.

**Limit CPU Usage:**
```bash
cpulimit --limit 20 -- ./GoldBachCtl start
```
This command limits the CPU usage of the verifier to 20% while starting the verification process. It is useful for ensuring that the verifier does not consume too many system resources.

## Info
For more detailed information about each command and options, use the `--help` command to access the built-in manual.
