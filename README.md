# Goldbach Conjecture Validator

Goldbach Conjecture Validator, a tool to test the  Goldbach's Conjecture.This Validator can test Goldbach's Conjecture. Can running in frontend or background, and configure settings as needed.

[中文文档](readme_zh.md)

## Build

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
~$ ./GoldBachCtl start
```

### Defaults to background mode

### Limit cpu usage under 20%

```bash
~$ cpulimit --limit 20 -- ./GoldBachCtl start
```

## Command

Using command operate Goldbach Conjecture Validator, use the following commands with argument

**Start:**
```bash
./GoldBachCtl start
```
This command will initiates the process in background.

**Stop:**
```bash
./GoldBachCtl stop
```
This command stops the process.

**Suspend:**
```bash
./GoldBachCtl suspend
```
Temporarily pause the background process.

**Resume:**
```bash
./GoldBachCtl resume
```
Resume the background process after it has been suspended.

**Check Status:**
```bash
./GoldBachCtl status
```
Display the status of the background process.

**Configure Settings:**
```bash
./GoldBachCtl config
```
Change the configuration settings for the Validator.

**Limit CPU Usage:**
```bash
cpulimit --limit 20 -- ./GoldBachCtl start
```
This command will limits the CPU usage of the Validator to 20% while starting the background process. 

## Info
For more detailed information about each command and options, use the `--help` command to access the built-in manual.
