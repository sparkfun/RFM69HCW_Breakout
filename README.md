RFM69HCW Breakout Board
=================

-> [![alt text](https://cdn.sparkfun.com/assets/parts/9/6/6/5/12823-00.jpg)](https://cdn.sparkfun.com/assets/parts/9/6/6/5/12823-00.jpg) <-

Product Versions
----------------
* [**RFM69HCW Breakout 915MHz (WRL-12775)**](https://www.sparkfun.com/products/12775)
* [**RFM69HCW Breakout 433MHz (WRL-12823)**](https://www.sparkfun.com/products/12823)

This is a breakout board for HopeRF's RFM69HCW wireless transceiver module. These modules operate in the [ISM band](http://en.wikipedia.org/wiki/ISM_band), which is reserved for short-range, low-power communications. Note that the 915MHz version is legal in [ITU region](http://en.wikipedia.org/wiki/ITU_region) 2 (Americas, Greenland, Pacific Islands), and the 433MHz version is legal in [ITU region](http://en.wikipedia.org/wiki/ITU_region) 1 (Europe, Africa, Middle East, Russia). Other regions have mixed allocations. Hobbyist use is not likely to be an issue, but if you're going to be deploying a lot of these check your local regulations.

Documentation
-------------------
* [**RFM69HCW datasheet**](https://github.com/sparkfun/RFM69HCW_Breakout/blob/master/documentation/RFM69HCW-V1.1.pdf)
* [**HopeRF RFM69HCW product page**](http://www.hoperf.com/rf/fsk_module/RFM69HCW.htm)

Repository Contents
-------------------
* [**/Libraries/Arduino**](https://github.com/sparkfun/RFM69HCW_Breakout/tree/master/Libraries/Arduino) - Contains the [RFM69 library](https://github.com/LowPowerLab/RFM69) written by Felix Rusu of [LowPowerLab.com](lowpowerlab.com). See [https://github.com/LowPowerLab/RFM69](https://github.com/LowPowerLab/RFM69) for the most up-to-date version.

* [**/Libraries/Arduino/RFM69/examples**](https://github.com/sparkfun/RFM69HCW_Breakout/tree/master/Libraries/Arduino/RFM69/examples) - Example Arduino sketch showing how to use the RFM69HCW breakout board. See the hook-up guide at [https://learn.sparkfun.com/tutorials/rfm69hcw-hookup-guide](https://learn.sparkfun.com/tutorials/rfm69hcw-hookup-guide) for wiring and usage details.

* [**/hardware**](https://github.com/sparkfun/RFM69HCW_Breakout/tree/master/hardware) - Eagle design files (.brd, .sch, .pdf)

* [**/documentation**](https://github.com/sparkfun/RFM69HCW_Breakout/tree/master/documentation) - Datasheets, etc.

Attribution
-----------
We gratefully acknowledge Felix Rusu of [LowPowerLab.com](lowpowerlab.com) for his terrific [RFM69 library](https://github.com/LowPowerLab/RFM69) and his very cool [Moteino](http://lowpowerlab.com/blog/category/moteino/) hardware. A version of his library is included here for the convenience of SparkFun customers. Please see his [GitHub repository](https://github.com/LowPowerLab/RFM69) for the latest version.

License Information
-------------------
The hardware design is released under the [Creative Commons Attribution-ShareAlike 4.0 International](http://creativecommons.org/licenses/by-sa/4.0/) license.

Felix Rusu's RFM69 library is released under the [Creative Commons Attribution-ShareAlike 3.0](http://creativecommons.org/licenses/by-sa/3.0/) license. 

SparkFun's example code is based on Felix Rusu's work, and is thus released under the same [Creative Commons Attribution-ShareAlike 3.0](http://creativecommons.org/licenses/by-sa/3.0/) license.
