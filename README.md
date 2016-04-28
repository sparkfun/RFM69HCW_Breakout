RFM69HCW Breakout Board
=================
The RFM69HCW is an inexpensive and versatile radio module that operates in the unlicensed ISM (Industry, Science, and Medicine) radio band. It's perfect for building inexpensive short-range wireless networks of sensors and actuators for home automation, citizen science, and more.

[![alt text](https://cdn.sparkfun.com/assets/parts/9/6/6/5/12823-00.jpg)](https://cdn.sparkfun.com/assets/parts/9/6/6/5/12823-00.jpg)

Specs
----------------

* Transmit power: -18dBm (0.016mW) to +20dBm (100mW) in 1dBm steps
* Receive sensitivity: down to -120dBm at 1.2kbps
* Modulation types: FSK GFSK MSK GMSK OOK
* Bit rates (FSK): 1.2kbps to 300kbps
* Voltage range: 1.8V to 3.6V
* Current consumption: 0.1uA sleep, 1.25mA standby, 16mA receive, 
* 130mA transmit (max)
* Encryption: AES 128-bit (optional)
* Packet buffer (FIFO): 66 bytes
* Dimensions: 0.8" x 1.1"

Product Versions
----------------

The RFM69HCW modules transmit in the [ISM band](http://en.wikipedia.org/wiki/ISM_band), which is reserved for short-range, low-power communications. SparkFun sells the RFM69HCW Breakout Board in two frequencies:

* [**RFM69HCW Breakout 915MHz (WRL-12775)**](https://www.sparkfun.com/products/12775)
* [**RFM69HCW Breakout 433MHz (WRL-12823)**](https://www.sparkfun.com/products/12823)

Broadly speaking, the 915MHz version is legal in [ITU region](http://en.wikipedia.org/wiki/ITU_region) 2 (North and South America, Australia, Greenland, Pacific Islands, Israel), and the 433MHz version is legal in [ITU region](http://en.wikipedia.org/wiki/ITU_region) 1 (Europe, Africa, Middle East, Russia). Other areas have mixed allocations; hobbyist use is not likely to be an issue, but if you're going to be deploying a lot of these or using them in a commercial product, check your local regulations.

Documentation
-------------------

* [**Hookup Guide**](https://learn.sparkfun.com/tutorials/rfm69hcw-hookup-guide)
* [**RFM69HCW Breakout Board Schematic**](https://github.com/sparkfun/RFM69HCW_Breakout/blob/master/documentation/RFM69HCW_BOB.pdf)
* [**RFM69HCW datasheet**](https://github.com/sparkfun/RFM69HCW_Breakout/blob/master/documentation/RFM69HCW-V1.1.pdf)
* [**HopeRF RFM69HCW product page (external link)**](http://www.hoperf.com/rf/fsk_module/RFM69HCW.htm)

Repository Contents
-------------------
* [**/Libraries/Arduino**](https://github.com/sparkfun/RFM69HCW_Breakout/tree/master/Libraries/Arduino) - Contains the [RFM69 library](https://github.com/LowPowerLab/RFM69) written by Felix Rusu of [LowPowerLab.com](lowpowerlab.com). See [https://github.com/LowPowerLab/RFM69](https://github.com/LowPowerLab/RFM69) for the most up-to-date version.

* [**/Libraries/Arduino/RFM69/examples**](https://github.com/sparkfun/RFM69HCW_Breakout/tree/master/Libraries/Arduino/RFM69/examples) - Example Arduino sketch showing how to use the SparkFun RFM69HCW breakout board. See the hook-up guide at [https://learn.sparkfun.com/tutorials/rfm69hcw-hookup-guide](https://learn.sparkfun.com/tutorials/rfm69hcw-hookup-guide) for wiring and usage details.

* [**/hardware**](https://github.com/sparkfun/RFM69HCW_Breakout/tree/master/hardware) - Eagle design files (.brd, .sch)

* [**/documentation**](https://github.com/sparkfun/RFM69HCW_Breakout/tree/master/documentation) - Datasheets, schematic, etc.

Attribution
-----------
We gratefully acknowledge Felix Rusu of [LowPowerLab.com](lowpowerlab.com) for his terrific [RFM69 library](https://github.com/LowPowerLab/RFM69), which runs on his very cool [Moteino](http://lowpowerlab.com/moteino/) hardware. A version of his library is included here for the convenience of SparkFun customers. Please see his [GitHub repository](https://github.com/LowPowerLab/RFM69) for the latest version.

License Information
-------------------
The hardware design is released under the [Creative Commons Attribution-ShareAlike 4.0 International](http://creativecommons.org/licenses/by-sa/4.0/) license.

Felix Rusu's RFM69 library is released under the [Creative Commons Attribution-ShareAlike 3.0](http://creativecommons.org/licenses/by-sa/3.0/) license. 

SparkFun's example code is based on Felix Rusu's work, and is thus released under the same [Creative Commons Attribution-ShareAlike 3.0](http://creativecommons.org/licenses/by-sa/3.0/) license.
