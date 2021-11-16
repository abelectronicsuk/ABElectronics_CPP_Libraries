AB Electronics UK Expander Pi C++ Library
=====

C++ Library to use with Expander Pi board from https://www.abelectronics.co.uk

The Expander Pi class contains methods for controlling the real-time clock, analogue to digital converter, digital to analogue converter and the digital I/O pins.  Examples are included to show the class can be used.

The example demo files can be found in /ABElectronics_CPP_Libraries/ExpanderPi/demos  

### Downloading and Installing the library

To download to your Raspberry Pi type in terminal: 

```
git clone https://github.com/abelectronicsuk/ABElectronics_CPP_Libraries.git
```

# Class: ExpanderPi

```
ExpanderPi(bool init)
```
Initialise the Expander Pi Object  
**Parameter:**  
init *(bool optional)*: initialise the IO chip. Defaults to true.  

When the IO is initialised the pins will be set as inputs and non-inverted. Pull-ups resistors are disabled.

___

## ADC Methods:

The ADC methods controls the functions on the 12 bit 8 channel Analogue to Digital converter.  The Expander Pi comes with an on board 4.096 voltage reference. To use an external voltage reference remover the solder bridge from jumper J1 and connect the external voltage reference to the Vref pin.  

```
int adc_open();
```
Open the ADC SPI bus channel  
This needs to be called before using the ADC  
**Returns:** null  
___
```
void adc_close();
```
Close the ADC SPI bus channel  
**Returns:** null  
___  

```
adc_read_voltage(int channel, int mode) 
```   
Read the voltage from the selected channel on the ADC   
**Parameters:**  
channel *(int)*: options are: 1 to 8.  
mode *(int)*: 0 = Single Ended or 1 = Differential  
**Returns:** voltage *(double)* between 0V and the reference voltage  

In single ended mode the channel number corresponds to the number on the Expander Pi.  In differential mode channel the number selects the channels as follows:

| Channel  | Mode         | ADC input pins on Expander Pi   |
|-------|--------------|----------------------|
| 1     | single-ended | 1                    |
| 2     | single-ended | 2                    |
| 3     | single-ended | 3                    |
| 4     | single-ended | 4                    |
| 5     | single-ended | 5                    |
| 6     | single-ended | 6                    |
| 7     | single-ended | 7                    |
| 8     | single-ended | 8                    |
| 1     | differential | CH1 = IN+  CH2 = IN- |
| 2     | differential | CH1 = IN-  CH2 = IN+ |
| 3     | differential | CH3 = IN+  CH4 = IN- |
| 4     | differential | CH3 = IN-  CH4 = IN+ |
| 5     | differential | CH5 = IN+  CH6 = IN- |
| 6     | differential | CH5 = IN-  CH6 = IN+ |
| 7     | differential | CH7 = IN+  CH8 = IN- |
| 8     | differential | CH7 = IN-  CH8 = IN+ |

___
```
adc_read_raw(int channel, int mode)
```   
Read the raw value from the selected channel on the ADC  
**Parameters:**  
channel *(int)*: options are: 1 to 8.  
mode *(int)*: 0 = Single Ended or 1 = Differential  
**Returns:** *(int)* 12 bit value (0 to 4096)  

In single ended mode the channel number corresponds to the number on the Expander Pi.  In differential mode channel the number selects the channels as follows:

| Channel  | Mode         | ADC input pins on Expander Pi   |
|-------|--------------|----------------------|
| 1     | single-ended | 1                    |
| 2     | single-ended | 2                    |
| 3     | single-ended | 3                    |
| 4     | single-ended | 4                    |
| 5     | single-ended | 5                    |
| 6     | single-ended | 6                    |
| 7     | single-ended | 7                    |
| 8     | single-ended | 8                    |
| 1     | differential | CH1 = IN+  CH2 = IN- |
| 2     | differential | CH1 = IN-  CH2 = IN+ |
| 3     | differential | CH3 = IN+  CH4 = IN- |
| 4     | differential | CH3 = IN-  CH4 = IN+ |
| 5     | differential | CH5 = IN+  CH6 = IN- |
| 6     | differential | CH5 = IN-  CH6 = IN+ |
| 7     | differential | CH7 = IN+  CH8 = IN- |
| 8     | differential | CH7 = IN-  CH8 = IN+ |

___
```
adc_set_refvoltage(double ref) 
```   
Set the reference voltage for the analogue to digital converter.  

By default the ADC uses an on-board 4.096V voltage reference.  If you choose to use an external voltage reference you will need to use this method to set the ADC reference voltage to match the supplied reference voltage.

The reference voltage must be less than or equal to the voltage on the Raspberry Pi 5V rail.  

**Parameters:**  
ref *(double)*: reference voltage  
**Returns:** null  

___
## DAC Methods:

The DAC methods control the 2 channel 12 bit digital to analogue converter.  The DAC uses an internal voltage reference and can output a voltage between 0 and 2.048V with gain set to 1 or 0 and 4.095V when gain is set to 2.  

```
dac_open()
```
Open the DAC SPI bus channel  
This needs to be called before using the DAC  
**Returns:** null  
___
```
dac_close()
```
Close the DAC SPI bus channel  
**Returns:** null  
___
```
dac_set_voltage(double voltage, int channel, int gain)
```
Set the voltage for the selected channel on the DAC  
**Parameters:**  
voltage *(double)*: Can be between 0 and 2.047 volts when gain is set to 1 or 0 and 4.095 volts when gain is set to 2  
channel *(int)*: 1 or 2  
gain *(int)*: 1 or 2. The output voltage will be between 0 and 2.048V when gain is set to 1,  0 and 4.096V when gain is set to 2  
**Returns:** null  
___
```
dac_set_raw(uint16_t raw, int channel, int gain)
```

Set the raw value from the selected channel on the DAC  
**Parameters:**  
raw *(int)*: value between 0 and 4095  
channel *(int)*: 1 or 2  
gain *(int)*: 1 or 2. The output voltage will be between 0 and 2.048V when gain is set to 1,  0 and 4.096V when gain is set to 2  
**Returns:** null 

___
## IO Methods

The IO methods control the MCP23017 16 digital I/O channels on the Expander Pi.  The MCP23017 chip is split into two 8-bit ports.  Port 0 controls pins 1 to 8 while Port 1 controls pins 9 to 16. 
When writing to or reading from a port the least significant bit represents the lowest numbered pin on the selected port.

___
```
io_set_pin_direction(uint8_t pin, uint8_t direction):
```
Sets the IO direction for an individual pin  
**Parameters:**  
pin *(uint8_t)*: 1 to 16   
direction *(uint8_t)*: 1 = input, 0 = output  
**Returns:** null
___
```
io_get_pin_direction(uint8_t pin)
```  
Get the IO direction for an individual pin  
**Parameters:**  
pin *(uint8_t)*: pin to read, 1 to 16   
**Returns:** *(uint8_t)* 1 = input, 0 = output  
___
```
io_set_port_direction(uint8_t port, uint8_t direction): 
```
Sets the IO direction for the specified IO port  
**Parameters:**  
port *(uint8_t)*: 0 = pins 1 to 8, 1 = pins 9 to 16   
direction *(uint8_t)*: number between 0 and 255 or 0x00 and 0xFF.  Each bit in the 8-bit number represents a pin on the port.  1 = input, 0 = output  
**Returns:** null
___
```
io_get_port_direction(uint8_t port): 
```
Get the direction from an IO port  
**Parameters:**  
port *(uint8_t)*: 0 = pins 1 to 8, 1 = pins 9 to 16   
**Returns:** *(uint8_t)* number between 0 and 255 (0xFF)  
___
```
io_set_bus_direction(uint16_t direction): 
```
Sets the IO direction for all pins on the bus  
**Parameters:**  
direction *(uint16_t)*: 16-bit number 0 to 65535 (0xFFFF).  For each bit 1 = input, 0 = output  
**Returns:** null
___
```
io_get_bus_direction()
```
Get the direction for an IO bus  
**Returns:** *(uint16_t)* 16-bit number 0 to 65535 (0xFFFF). For each bit 1 = input, 0 = output  
___
```
io_set_pin_pullup(uint8_t pin, uint8_t value)
```
Set the internal 100K pull-up resistors for an individual pin  
**Parameters:**  
pin *(uint8_t)*: pin to update, 1 to 16 
value *(uint8_t)*: 1 = enabled, 0 = disabled  
**Returns:** null
___
```
io_get_pin_pullup(uint8_t pin)
```  
Get the internal 100K pull-up resistors for an individual pin  
**Parameters:**  
pin *(uint8_t)*: pin to read, 1 to 16  
**Returns:** *(uint8_t)* 1 = enabled, 0 = disabled  
___
```
io_set_port_pullups(uint8_t port, uint8_t value)
```
Set the internal 100K pull-up resistors for the selected IO port  
**Parameters:**  
port *(uint8_t)*: 0 = pins 1 to 8, 1 = pins 9 to 16  
value *(uint8_t)*: number between 0 and 255 or 0x00 and 0xFF.  Each bit in the 8-bit number represents a pin on the port.  1 = Enabled, 0 = Disabled  
**Returns:** null  
___
```
io_get_port_pullups(uint8_t port): 
```
Get the internal pull-up status for the selected IO port  
**Parameters:**  
port *(uint8_t)*: 0 = pins 1 to 8, 1 = pins 9 to 16   
**Returns:** *(uint8_t)* number between 0 and 255 (0xFF)  
___
```
io_set_bus_pullups(uint16_t value)
```
Set internal 100K pull-up resistors for an IO bus  
**Parameters:**  
value *(uint16_t)*: 16-bit number 0 to 65535 (0xFFFF). For each bit 1 = enabled, 0 = disabled  
**Returns:** null
___
```
io_get_bus_pullups()
```
Get the internal 100K pull-up resistors for an IO bus  
**Returns:** *(uint16_t)* 16-bit number 0 to 65535 (0xFFFF). For each bit 1 = enabled, 0 = disabled  
___
```
io_write_pin(uint8_t pin, uint8_t value)
```
Write to an individual pin 1 - 16  
**Parameters:**  
pin *(uint8_t)*: 1 to 16  
value *(uint8_t)*: 1 = logic high, 0 = logic low  
**Returns:** null  
___
```
io_write_port(uint8_t port, uint8_t value)
```
Write to all pins on the selected port  
**Parameters:**  
port *(uint8_t)*: 0 = pins 1 to 8, 1 = pins 9 to 16  
value *(uint8_t)*:  number between 0 and 255 or 0x00 and 0xFF.  Each bit in the 8-bit number represents a pin on the port.  1 = logic high, 0 = logic low    
**Returns:** null  
___
```
io_write_bus(uint16_t value)
```
Write to all pins on the selected bus  
**Parameters:**  
value *(uint16_t)*: 16-bit number 0 to 65535 (0xFFFF). For each bit 1 = logic high, 0 = logic low  
**Returns:** null  
___
```
io_read_pin(uint8_t pin)
```
Read the value of an individual pin 1 - 16   
**Parameters:**  
pin *(uint8_t)*: 1 to 16  
**Returns:** *(uint8_t)* 0 = logic low, 1 = logic high  
___
```
io_read_port(uint8_t port)
```
Read all pins on the selected port  
**Parameters:**  
port *(uint8_t)*: 0 = pins 1 to 8, 1 = pins 9 to 16  
**Returns:** *(uint8_t)* number between 0 and 255 or 0x00 and 0xFF.  Each bit in the 8-bit number represents a pin on the port.  0 = logic low, 1 = logic high
___
```
io_read_bus()
```
Read all pins on the bus  
**Returns:** *(uint16_t)* 16-bit number 0 to 65535 (0xFFFF) Each bit in the 16-bit number represents a pin on the port.  0 = logic low, 1 = logic high  
___
```
io_invert_pin(uint8_t pin, uint8_t polarity)
```
Invert the polarity of the selected pin  
**Parameters:**  
pin *(uint8_t)*: 1 to 16  
polarity *(uint8_t)*: 0 = same logic state of the input pin, 1 = inverted logic state of the input pin  
**Returns:** null
___
```
io_get_pin_polarity(uint8_t pin)
```  
Get the polarity of the selected pin  
**Parameters:**  
pin *(uint8_t)*: pin to read, 1 to 16   
**Returns:** (uint8_t) 0 = same logic state of the input pin, 1 = inverted logic state of the input pin  
___
```
io_invert_port(uint8_t port, uint8_t polarity)
```
Invert the polarity of the pins on a selected port  
**Parameters:**  
port *(uint8_t)*: 0 = pins 1 to 8, 1 = pins 9 to 16  
polarity *(uint8_t)*: number between 0 and 255 or 0x00 and 0xFF.  Each bit in the 8-bit number represents a pin on the port.  0 = same logic state of the input pin, 1 = inverted logic state of the input pin  
**Returns:** null
___
```
io_get_port_polarity(uint8_t port): 
```
Get the polarity for the selected IO port  
**Parameters:**  
port *(uint8_t)*: 0 = pins 1 to 8, 1 = pins 9 to 16   
**Returns:** (uint8_t) number between 0 and 255 (0xFF) 
___
```
io_invert_bus(uint16_t polarity)
```
Invert the polarity of the pins on the bus  
**Parameters:**  
polarity *(uint16_t)*: 16-bit number 0 to 65535 (0xFFFF).  For each bit 0 = same logic state of the input pin, 1 = inverted logic state of the input pin  
**Returns:** null  
___
```
io_get_bus_polarity()
```
Get the polarity of the pins on the bus  
**Returns:** *(uint16_t)* 16-bit number 0 to 65535 (0xFFFF). For each bit 0 = same logic state of the input pin, 1 = inverted logic state of the input pin  
___
```
io_mirror_interrupts(uint8_t value)
```
Sets whether the interrupt pins INT A and INT B are independently connected to each port or internally connected together  
**Parameters:**  
value *(uint8_t)*: 1 = The INT pins are internally connected, 0 = The INT pins are not connected. INT A is associated with PortA and INT B is associated with PortB    
**Returns:** null
___
```
io_set_interrupt_polarity(uint8_t value)
```
Sets the polarity of the INT output pins  
**Parameters:**  
value *(uint8_t)*: 0 = Active Low, 1 = Active High  
**Returns:** null  
___
```
io_get_interrupt_polarity()
```
Get the polarity of the INT output pins  
**Returns:** *(uint8_t)* 1 = Active-high.  0 = Active-low.  
___
```
io_set_interrupt_type(uint8_t port, uint8_t value)
```
Sets the type of interrupt for each pin on the selected port  
**Parameters:**  
port *(uint8_t)*: 0 = pins 1 to 8, 1 = pins 9 to 16  
value *(uint8_t)*: number between 0 and 255 or 0x00 and 0xFF.  Each bit in the 8-bit number represents a pin on the port.  1 = interrupt is fired when the pin matches the default value, 0 = the interrupt is fired on state change  
**Returns:** null  
___
```
io_get_interrupt_type(uint8_t port): 
```
Get the type of interrupt for each pin on the selected port  
**Parameters:**  
port *(uint8_t)*: 0 = pins 1 to 8, 1 = pins 9 to 16   
**Returns:** *(uint8_t)* number between 0 and 255 (0xFF)  
For each bit 1 = interrupt is fired when the pin matches the default value, 0 = interrupt fires on state change  
___
```
io_set_interrupt_defaults(uint8_t port, uint8_t value)
```
These bits set the compare value for pins configured for interrupt-on-change on the selected port.  
If the associated pin level is the opposite from the register bit, an interrupt occurs.    
**Parameters:**  
port *(uint8_t)*: 0 = pins 1 to 8, 1 = pins 9 to 16, 
value *(uint8_t)*: compare value between 0 and 255 or 0x00 and 0xFF.  Each bit in the 8-bit number represents a pin on the port.  
**Returns:** null  
___
```
io_get_interrupt_defaults(uint8_t port): 
```
Get the interrupt default value for each pin on the selected port  
**Parameters:**  
port *(uint8_t)*: 0 = pins 1 to 8, 1 = pins 9 to 16   
**Returns:** *(uint8_t)* number between 0 and 255 (0xFF)  
___
```
io_set_interrupt_on_pin(uint8_t pin, uint8_t value)
```
Enable interrupts for the selected pin  
**Parameters:**  
pin *(uint8_t)*: 1 to 16  
value *(uint8_t)*: 0 = interrupt disabled, 1 = interrupt enabled  
**Returns:** null
___
```
io_get_interrupt_on_pin(uint8_t pin)
```  
Gets whether the interrupt is enabled for the selected pin  
**Parameters:**  
pin *(uint8_t)*: pin to read, 1 to 16   
**Returns:** *(uint8_t)* 1 = enabled, 0 = disabled
___
```
io_set_interrupt_on_port(uint8_t port, uint8_t value)
```
Enable interrupts for the pins on the selected port  
**Parameters:**  
port *(uint8_t)*: 0 = pins 1 to 8, 1 = pins 9 to 16  
value *(uint8_t)*: number between 0 and 255 or 0x00 and 0xFF.  Each bit in the 8-bit number represents a pin on the port.  
**Returns:** null
___
```
io_get_interrupt_on_port(uint8_t port): 
```
Gets whether the interrupts are enabled for the selected port  
**Parameters:**  
port *(uint8_t)*: 0 = pins 1 to 8, 1 = pins 9 to 16   
**Returns:** (uint8_t) number between 0 and 255 (0xFF).  For each bit 1 = enabled, 0 = disabled  
___
```
io_set_interrupt_on_bus(uint16_t value)
```
Enable interrupts for the pins on the bus  
**Parameters:**  
value *(uint16_t)*: 16-bit number 0 to 65535 (0xFFFF).  For each bit 1 = enabled, 0 = disabled  
**Returns:** null
___
```
io_get_interrupt_on_bus()
```
Gets whether the interrupts are enabled for the bus  
**Returns:** *(uint16_t)* 16-bit number 0 to 65535 (0xFFFF). For each bit 1 = enabled, 0 = disabled  
___
```
io_read_interrupt_status(uint8_t port)
```
Read the interrupt status for the pins on the selected port  
**Parameters:**  
port *(uint8_t)*: 0 = pins 1 to 8, 1 = pins 9 to 16  
**Returns:**  *(uint8_t)* number between 0 and 255 or 0x00 and 0xFF.  Each bit in the 8-bit number represents a pin on the port.  1 = Enabled, 0 = Disabled
___
```
io_read_interrupt_capture(uint8_t port)
```
Read the value from the selected port at the time of the last interrupt trigger  
**Parameters:**  
port *(uint8_t)*: 0 = pins 1 to 8, 1 = pins 9 to 16  
**Returns:**  *(uint8_t)* number between 0 and 255 or 0x00 and 0xFF.  Each bit in the 8-bit number represents a pin on the port.  1 = Enabled, 0 = Disabled
___
```
io_reset_interrupts()
```
Set the interrupts A and B to 0  
**Parameters:** null  
**Returns:** null

___
## RTC methods

The RTC methods control the DS1307 real-time clock on the Expander Pi.  You can set and read the date and time from the clock as well as controlling the pulse output on the RTC pin.


```
rtc_set_date(struct tm date) 
```
Set the date and time on the RTC   
**Parameters:**  
date *(struct tm)*: date and time  
**Returns:** null
___
```
rtc_read_date() 
```
Returns the date from the RTC  
**Returns:** *(tm struct)* date
___
```
rtc_enable_output() 
```
Enable the square-wave output on the SQW pin.  
**Returns:** null
___
```
rtc_disable_output()
```
Disable the square-wave output on the SQW pin.   
**Returns:** null
___
```
rtc_set_frequency(uint8_t frequency)
```
Set the frequency for the square-wave output on the SQW pin.   
**Parameters:**  
frequency *(uint8_t)*: options are: 1 = 1Hz, 2 = 4.096KHz, 3 = 8.192KHz, 4 = 32.768KHz   
**Returns:** null
___
```
rtc_write_memory(uint8_t address, uint8_t *valuearray, uint8_t length)
```
Write to the memory on the ds1307. The ds1307 contains 56-Byte, battery-backed RAM with Unlimited Writes  
**Parameters:**  
address *(uint8_t)*: 0x08 to 0x3F  
valuearray *(uint8_t\*)*: array containing data to be written to memory  
length *(uint8_t)*: up to 56 bytes.  array length can not exceed the available address space.  
**Returns:** null
___
```
rtc_read_memory(uint8_t address, uint8_t length)
```
Read from the memory on the ds1307  
**Parameters:**  
address *(uint8_t)*: 0x08 to 0x3F  
length *(uint8_t)*: up to 56 bytes.  length can not exceed the available address space.  
**Returns:** *(uint8_t\*)* array of bytes from the SRAM