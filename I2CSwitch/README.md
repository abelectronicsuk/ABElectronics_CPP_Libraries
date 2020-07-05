AB Electronics UK I2C Switch C++ Library
=====

C++ Library to use with [I2C Switch](https://www.abelectronics.co.uk/p/84/i2c-switch "I2C Switch") Raspberry Pi expansion board from https://www.abelectronics.co.uk

The example C++ files can be found in /ABElectronics_CPP_Libraries/I2CSwitch/demos  

### Downloading and Installing the library

To download to your Raspberry Pi type in terminal: 

```
git clone https://github.com/abelectronicsuk/ABElectronics_CPP_Libraries.git
```

Class:
----------

```
I2CSwitch(uint8_t address)
```
The I2CSwitch class provides control over the I2C Switch outputs on the PCA9546A controller.  Methods include setting and getting the I2C channel and resetting the switch.  

**Parameters:** address - Initialise with the I2C address for the I2C Switch. Supported I2C addresses are 0x70 to 0x77.  The default address is 0x70.  
**Returns:** null 


Methods:
----------

```
switch_channel(uint8_t channel) 
```
Switch on the selected channel and switch off all other channels.  
**Parameters:** channel - 1 to 4.  
**Returns:** null  
___
```
set_channel_state(uint8_t channel, uint8_t state) 
```
Set the state for the selected channel.  All other channels remain in their previous state.  
**Parameter:** channel - 1 to 4  
**Parameter:** state - 1 or 0. 1 = channel on, 0 = channel off.  
**Returns:** null  
___
```
get_channel_state(uint8_t channel) 
```
Get the state for the selected channel.  
**Parameters:** channel - 1 to 4  
**Returns:** (uint8_t) 1 or 0. 1 = channel on, 0 = channel off.  
___
```
reset() 
```
Reset the PCA9546A I2C switch.  Resetting allows the PCA9546A to recover from a situation in which one of the downstream I2C buses is stuck in a low state.  All channels will be set to an off state.  
**Returns:** null  