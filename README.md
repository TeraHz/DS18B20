DS18B20
=======

A C++ library to read Dallas 1-Wire temperature sensors (eg DS18B20) accessible via the Linux file system.

You will need to already have the device tree and/or kernal modules sorted; there are plenty of instructions out there in Google-Land.

Should work with Raspberry Pi, Beaglebone, CubieBoard etc, so long as you can do the "cat w1_slave" thing to read the temperature.