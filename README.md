# radtel-rt-900-firmware
Radtel RT-900 Original Firmware (20250305)

## Made to compile with Linux
I added a bare minimum tweaked version of the Makefile so that the firmware
at least compiles under Linux and also had to change some file names as well
as add a file from the original sources.

If If you have an ARM cross toolchain installed you can build the firmware
using:
```console
make -f Makefile.linux
```

## Origin
This is basically the same firmware source code as it can be found on the
official Radtel site:
https://www.radtels.com/pages/software-download
called "Radtel RT-900 (None BT) Open Sources 250305" and points to this
download location:
https://radio-software.s3.us-east-1.amazonaws.com/Radtel_RT900+open+source+20250305+.zip

The license is unclear, parts are Apache-2.0, parts are (c) ARM Limited
(CMSIS), most parts have no copyright at all, so use at your own risk.
