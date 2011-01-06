AVR-JIG
=======

This is a simple clone of the PSGrade service jig emulator by zAxis and Graf.

Haven't really tested this on anything but my Arduino Mega, but it should work for pretty much anything that my port of psgroove will work on. Building and configuring is exactly the same as my psgroove port, so I won't put another copy here. Refer to the [readme]https://github.com/timwu/psgroove/blob/master/README.md

Check google for what to do with this.


----------------------------------------------------------


Added by c0d3m4st4:


To compile for the ATMega16A based dongles use this command line:

make MCU=atmega16a BOARD=ATmega16aBasedDongle F_CPU=12000000

AVR-JIG has been tested succesfully in Neojailbreak and the PSJB look alike clone.