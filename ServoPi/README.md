AB Electronics UK Servo Pi C++ Library
=====

C++ Library to use with Servo Pi Raspberry Pi expansion board from https://www.abelectronics.co.uk

The example C++ files can be found in /ABElectronics_CPP_Libraries/ServoPi/demos  

### Downloading and Installing the library

To download to your Raspberry Pi type in the terminal: 

```
git clone https://github.com/abelectronicsuk/ABElectronics_CPP_Libraries.git
```

Classes:
----------

```
PWM(uint8_t address, uint8_t use_oe_pin)
```
The PWM class provides control over the pulse-width modulation outputs on the PCA9685 controller.  Methods include setting the frequency and duty cycle for each channel.  

**Note:** The PWM class was previously called ServoPi.

**Parameter:** address - I2C address. Defaults to 0x40  
**Optional Parameter:** use_oe_pin - Enable the Output Enable pin on the GPIO port. 1 = enable, 0 = disable. Defaults to false.  


Methods:
----------

```
set_pwm_freq(double freq, uint8_t calibration=0) 
```
Set the PWM frequency  
**Parameter:** freq - required frequency  
**Optional Parameter:** calibration - optional integer value to offset oscillator errors. Defaults to 0  
**Returns:** null  

---  

```
set_pwm(uint8_t channel, uint16_t on, uint16_t off) 
```
Set the output for single channels  
**Parameter:** channel - 1 to 16  
**Parameter:** on - time period 0 to 4095  
**Parameter:** off - time period 0 to 4095.  
Total on-time and off-time can not exceed 4095  
**Returns:** null  

---  

```
set_pwm_on_time(uint8_t channel, uint16_t on_time)
```
Set the output on time for a single channel  
**Parameter:** channel - 1 to 16  
**Parameter:** on_time - time period 0 to 4095  
**Returns:** null  

---  

```
set_pwm_off_time(uint8_t channel, uint16_t off_time)
```
Set the output off time for a single channel  
**Parameter:** channel - 1 to 16  
**Parameter:** off_time - time period 0 to 4095  
**Returns:** null  

---  

```
get_pwm_on_time(uint8_t channel)
```
Get the output on time for a single channel  
**Parameter:** channel - 1 to 16  
**Returns:** (uint16_t) on time  

---  

```
get_pwm_off_time(uint8_t channel)
```
Get the output off time for a single channel  
**Parameter:** channel - 1 to 16  
**Returns:** (uint16_t) off time   

---  

```
set_all_pwm(uint16_t on, uint16_t off) 
```
Set the output on all channels  
**Parameter:** on - time period  
**Parameter:** off - time period 0 to 4095.  
Total on-time and off-time can not exceed 4095  
**Returns:** null  

---  

```
output_disable()
```
Disable the output via the OE pin  
**Parameter:** null  
**Returns:** null  

---  

```
output_enable()
```
Enable the output via the OE pin  
**Parameter:** null  
**Returns:** null  

---  

```
set_allcall_address(uint8_t allcalladdress)
```
Set the I2C address for the All Call function  
**Parameter:** address  
**Returns:** null  

---  

```
enable_allcall_address()
```
Enable the I2C address for the All Call function  
**Returns:** null  

---  

```
disable_allcall_address()
```
Disable the I2C address for the All Call function  
**Returns:** null  

---  

```
sleep()
```
Puts the PCA9685 PWM controller into a sleep state.  
**Returns:** null  

---  

```
wake()
```
Wakes the PCA9685 PWM controller from its sleep state.  
**Returns:** null  

---  

```
is_sleeping()
```
Returns if the PCA9685 PWM controller is in its sleep state.  
**Parameter:** null  
**Returns:** (bool) true = Is sleeping, false = Is awake.  

---  

```
invert_output(state)
```
Inverts the outputs on all PWM channels.  
**Parameter:** True = inverted, False = non-inverted  
**Returns:** null  

---  

```
invert_output(bool state)
```
Invert the PWM output on all channels  
**Parameter:** state = true = inverted, false = non-inverted  
**Returns:** null  

---  

```
set_address(uint8_t address)
```
Set the I2C address  
**Parameter:** address = i2c address  
**Returns:** null  

---  

```
get_address()
```
Get the I2C address  
**Returns:** (uint8_t) i2c address  

---  

```
enable_oe_pin()
```
Enable the Output Enable Pin on the GPIO header  
**Returns:** null  
  
# Class: Servo #

The Servo class provides functions for controlling the position of servo motors commonly used on radio control models and small robots.  The Servo class initialises with a default frequency of 50Hz and low and high limits of 1ms and 2ms.

Initialise with the I2C address for the Servo Pi.  

```
Servo(uint8_t address, double low_limit, double high_limit, bool reset, bool use_oe_pin)
```
**Parameter:** address - i2c address for the ServoPi board, defaults to 0x40  
**Optional Parameter:** low_limit - Pulse length in milliseconds for the lower servo limit. (default = 1.0ms)  
**Optional Parameter:** high_limit - Pulse length in milliseconds for the upper servo limit. (default = 2.0ms)  
**Optional Parameter:** reset - true: reset the servo controller and turn off all channels.  false: initialise with existing servo positions and frequency. (default = true)  
**Optional Parameter:** use_oe_pin - true = Enable the Output Enable pin on the GPIO port. false = Output Enable pin not used. Defaults to true.

Methods:
----------

```
move(channel, position, steps=250) 
```
Set the servo position  
**Parameter:**  channel - 1 to 16  
**Parameter:**  position - value between 0 and the maximum number of steps.  
**Optional Parameter:** steps - The number of steps between the low and high servo limits.  This is preset at 250 but can be any number between 0 and 4095.  On a typical RC servo a step value of 250 is recommended.  
**Returns:** null  

---  

```
get_position(channel, steps=250) 
```
Get the servo position  
**Parameter:** channel - 1 to 16  
**Optional Parameter:** steps - The number of steps between the low and high servo limits.  This is preset at 250 but can be any number between 0 and 4095.  On a typical RC servo, a step value of 250 is recommended.  
**Returns:** (uint16_t) position - value between 0 and the maximum number of steps. Due to rounding errors when calculating the position, the returned value may not be the same as the set value. 

---  

```
set_low_limit(low_limit, channel)
```
Set the pulse length for the lower servo limits.  Typically around 1 ms.  
Warning: Setting the pulse limit below 1 ms may damage your servo.  
**Parameter:** low_limit - Pulse length in milliseconds for the lower servo limit.  
**Optional Parameter:** channel - The channel for which the low limit will be set.  If this value is omitted or set to 0 the low limit will be set for all channels.  
**Returns:** null  

---  

```
set_high_limit(high_limit, channel)
```
Set the pulse length for the upper servo limits.  Typically around 2ms. 
Warning: Setting the pulse limit above 2ms may damage your servo.  
**Parameter:** high_limit - Pulse length in milliseconds for the upper servo limit.  
**Optional Parameter:** channel - The channel for which the upper limit will be set.  
If this value is omitted the upper limit will be set for all channels.  
**Returns:** null  

---  

```
set_frequency(freq, calibration) 
```
Set the PWM frequency  
**Parameter:** freq - required frequency for the servo.  
**Optional Parameter:** calibration - optional integer value to offset oscillator errors. Defaults to 0   
**Returns:** null  

---  

```
output_disable()
```
Disable the output via the OE pin  
**Parameter:** null  
**Returns:** null  

---  

```
output_enable()
```
Enable the output via the OE pin  
**Parameter:** null  
**Returns:** null  

---  

```
offset_enable()
```
Enable pulse offsets.  
This will set servo pulses to be staggered across the channels to reduce surges in the current draw.  
**Parameter:** null  
**Returns:** null  

---  

```
offset_disable()
```
Disable pulse offsets.  
This will set all servo pulses to start at the same time.  
**Parameter:** null  
**Returns:** null  

---  

```
sleep()
```
Put the device into a sleep state.  
**Parameter:** null  
**Returns:** null  

---  

```
wake()
```
Wake the device from its sleep state.  
**Parameter:** null  
**Returns:** null  

---  

```
is_sleeping()
```
Check the sleep status of the device.  
**Parameter:** null  
**Returns:** (bool) true = Is sleeping, false = Is awake.  

Usage
====

**PWM Class**

To use the Servo Pi PWM class in your code you must first import the class:
```
from ServoPi import PWM
```
Next, you must initialise the PWM object:
```
pwm = PWM(0x40)
```
Set the PWM frequency to 200 Hz and enable the output
```
pwm.set_pwm_freq(200)  
pwm.output_enable()  
```
Set the pulse width of channel 1 to 1024 or 25% duty cycle
```
pwm.set_pwm(1, 0, 1024) 
```
---
**Servo Class**

To use the Servo Pi Servo class in your code you must first import the class:
```
from ServoPi import Servo
```
Next, you must initialise the Servo object:
```
servo = Servo(0x40)
```
Set PWM frequency to 50 Hz
```
servo.set_frequency(50)  
```
Move the servo on channel 1 to position 125 out of 250 steps  
```
servo.move(1, 125, 250)
```

