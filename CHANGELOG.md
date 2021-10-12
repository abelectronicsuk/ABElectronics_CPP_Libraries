#### 2021-10-12 Andrew Dorey

* 1.1.5 Added unit tests to the I2C Switch library.

#### 2021-10-02 Andrew Dorey

* 1.1.4 IO Pi, RTC Pi and Servo Pi Updates
Added unit tests to IO Pi and RTC classes.
Changed IO Pi class to use enum for MCP23017 register addresses instead of defines.
Changed Servo Pi class to use enum for PCA9685 register addresses instead of defines.
Updated unit tests to use TestFile class in UnitTest folder.
RTCPi class, added length parameter to write_memory function.

#### 2021-06-18 Andrew Dorey

* 1.1.3  Servo Pi Updates
Renamed ServoPi class to PWM.
Added new methods to the PWM class for controlling the functionality of the PCA9685 PWM controller IC.
Added Servo class for controlling servos.
Added new demos and unit tests.

#### 2020-10-02 Andrew Dorey

* 1.1.2  Updates to the ADC DAC Pi class.

Added test programs for the ADC and DAC functions.


#### 2020-07-05 Andrew Dorey

* 1.1.1  Updates to the ADC DAC Pi, ADC Pi, ADC Differential Pi, I2C Switch and RTC Pi classes.

Changed datatypes in all classes, unsigned char is now uint8_t, unsigned short is now uint16_t, unsigned long is now uint32_t.
Added README files for each class with class and method documentation.
Moved the demo files into demo sub-folders.

#### 2020-07-01 Andrew Dorey

* 1.1.0  Updates to the IO Pi class.  
Added new methods for accessing whole IO bus directly, set_bus_direction(), set_bus_pullups(), write_bus(), read_bus(), invert_bus(), set_interrupt_on_bus(). 
Added get methods for each set method. 
Added unit tests for each IO Pi method
Moved demos into demos folder
Added optional parameter to IoPi to initialise the device.  
Changed all pin level methods to read the existing value from the MCP23017 before updating to allow for changes by other applications.
Changed datatypes in all classes, unsigned char is now uint8_t, unsigned short is now uint16_t.
Refactored code to reduce repetition.


#### 2020-04-22 Andrew Dorey
* 1.0.9 Fixed memory leaks in the RTC SRAM functions for the Expander Pi and RTC Pi.  Fixed out of bound errors in several demo files.

#### 2020-04-21 Andrew Dorey
* 1.0.8 Fixed various bugs in all C++ classes and updated all variables using char types to be unsigned char.

#### 2020-02-27 Andrew Dorey
* 1.0.7 Update README.md

#### 2019-11-28 Andrew Dorey
* 1.0.6 Added new I2C Switch library

#### 2019-03-05 Andrew Dorey
* 1.0.5 Fixed several bugs and optimised the code to improve performance.

#### 2019-03-03 Gnurdle
* 1.0.4 Scope wrap file handles to keep for leaking on exceptions

#### 2018--07-16 Andrew Dorey
* 1.0.3 Bug fixes in the write and read memory RTC functions in the RTC Pi and Expander Pi classes.

#### 2018-04-24 Andrew Dorey
* 1.0.2 Updated link for ADC Pi

#### 2017-10-03 Andrew Dorey
* 1.0.1 A new example file showing how to use the interrupt functions on the IO Pi.

#### 2017-06-27 Brian Dorey
* 1.0.0 Upload of initial code
