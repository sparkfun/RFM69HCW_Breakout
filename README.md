RFM69HCW Breakout Board
=================

Picture

Product Versions
----------------
[*RFM69HCW Breakout 915MHz (WRL-12775)*](https://www.sparkfun.com/products/12775)

[*RFM69HCW Breakout 433MHz (WRL-12823)*](https://www.sparkfun.com/products/12823)

This is a breakout board for HopeRF's RFM69HCW wireless transceiver module. These modules operate in the [ISM band](http://en.wikipedia.org/wiki/ISM_band), which is reserved for short-range, low-power communications. Note that the 915MHz version is legal in [ITU region](http://en.wikipedia.org/wiki/ITU_region) 2 (Americas, Greenland, Pacific Islands), and the 433MHz version is legal in [ITU region](http://en.wikipedia.org/wiki/ITU_region) 1 (Europe, Africa, Middle East, Russia). Other regions have mixed allocations. Hobbyist use is not likely to be an issue, but if you're going to be deploying a lot of these check your local regulations.

Documentation
-------------------
* [*RFM69HCW datasheet*](https://github.com/sparkfun/RFM69HCW_Breakout/blob/master/documentation/RFM69HCW-V1.1.pdf)

* [*HopeRF RFM69HCW product page*](http://www.hoperf.com/rf/fsk_module/RFM69HCW.htm)

Repository Contents
-------------------
* **/software/Arduino/libraries** - Contains the [RFM69 library](https://github.com/LowPowerLab/RFM69) written by Felix Rusu of [LowPowerLab.com](lowpowerlab.com).

* **/software/Arduino/RFM69HCW_examples** - Example Arduino sketches showing how to use the RFM69HCW breakout board. Read the comments in the sketch for wiring and power instructions. Note that the examples included with the above library were written for the Low Power Lab [Moteino](http://lowpowerlab.com/moteino/) hardware and require modification to run on other Arduinos. These RFM69HCW_examples will run on most Arduinos without modification.

* **/hardware** - Eagle design files (.brd, .sch)

* **/documentation** - Datasheets, etc.

Version History
---------------
* **v1.0** Initial release 3/21/14 MDG

Attribution
-----------
Felix Rusu of [LowPowerLab.com](lowpowerlab.com) has written a great [RFM69 library](https://github.com/LowPowerLab/RFM69) for his Moteino project; we gratefully acknowledge his work. A working version is included here for convenience, see his [GitHub repository](https://github.com/LowPowerLab/RFM69) for the latest version.

License Information
-------------------
The hardware design is released under the [Creative Commons Attribution-ShareAlike 4.0 International](http://creativecommons.org/licenses/by-sa/4.0/) license.

Felix Rusu's RFM69 library is released under the [Creative Commons Attribution-ShareAlike 3.0](http://creativecommons.org/licenses/by-sa/3.0/) license. 

SparkFun's example code is based on Felix Rusu's work, and is thus released under the same [Creative Commons Attribution-ShareAlike 3.0](http://creativecommons.org/licenses/by-sa/3.0/) license.
