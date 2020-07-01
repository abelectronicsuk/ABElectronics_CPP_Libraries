AB Electronics UK IO Pi C++ Library
=====

C++ Library to use with IO Pi Raspberry Pi expansion board from https://www.abelectronics.co.uk

The example demo files can be found in /ABElectronics_CPP_Libraries/IOPi/demos  

### Downloading and Installing the library

To download to your Raspberry Pi type in terminal: 

```
git clone https://github.com/abelectronicsuk/ABElectronics_CPP_Libraries.git
```

Classes:
----------  
```
IOPi(address, initialise)
```
**Parameters:**  
address: i2c address for the target device. 0x20 to 0x27  
initialise (optional): true = direction set as inputs, pull-ups disabled, ports not inverted. false = device state unaltered. defaults to true  


Methods:
----------
___
```
set_pin_direction(uint8_t pin, uint8_t direction):
```
Sets the IO direction for an individual pin  
**Parameters:**  
pin: 1 to 16   
direction: 1 = input, 0 = output  
**Returns:** null
___
```
get_pin_direction(uint8_t pin)
```  
Get the IO direction for an individual pin  
**Parameters:**  
pin: pin to read, 1 to 16   
**Returns:** (uint8_t) 1 = input, 0 = output  
___
```
set_port_direction(uint8_t port, uint8_t direction): 
```
Sets the IO direction for the specified IO port  
**Parameters:**  
port: 0 = pins 1 to 8, 1 = pins 9 to 16   
direction: number between 0 and 255 or 0x00 and 0xFF.  Each bit in the 8-bit number represents a pin on the port.  1 = input, 0 = output  
**Returns:** null
___
```
get_port_direction(uint8_t port): 
```
Get the direction from an IO port  
**Parameters:**  
port: 0 = pins 1 to 8, 1 = pins 9 to 16   
**Returns:** (uint8_t) number between 0 and 255 (0xFF)  
___
```
set_bus_direction(uint16_t direction): 
```
Sets the IO direction for all pins on the bus  
**Parameters:**  
direction: 16-bit number 0 to 65535 (0xFFFF).  For each bit 1 = input, 0 = output  
**Returns:** null
___
```
get_bus_direction()
```
Get the direction for an IO bus  
**Returns:** (uint16_t) 16-bit number 0 to 65535 (0xFFFF). For each bit 1 = input, 0 = output  
___
```
set_pin_pullup(uint8_t pin, uint8_t value)
```
Set the internal 100K pull-up resistors for an individual pin  
**Parameters:**  
pin: pin to update, 1 to 16 
value: 1 = enabled, 0 = disabled  
**Returns:** null
___
```
get_pin_pullup(uint8_t pin)
```  
Get the internal 100K pull-up resistors for an individual pin  
**Parameters:**  
pin: pin to read, 1 to 16  
**Returns:** (uint8_t) 1 = enabled, 0 = disabled  
___
```
set_port_pullups(uint8_t port, uint8_t value)
```
Set the internal 100K pull-up resistors for the selected IO port  
**Parameters:**  
port: 0 = pins 1 to 8, 1 = pins 9 to 16  
value: number between 0 and 255 or 0x00 and 0xFF.  Each bit in the 8-bit number represents a pin on the port.  1 = Enabled, 0 = Disabled  
**Returns:** null  
___
```
get_port_pullups(uint8_t port): 
```
Get the internal pull-up status for the selected IO port  
**Parameters:**  
port: 0 = pins 1 to 8, 1 = pins 9 to 16   
**Returns:** (uint8_t) number between 0 and 255 (0xFF)  
___
```
set_bus_pullups(uint16_t value)
```
Set internal 100K pull-up resistors for an IO bus  
**Parameters:**  
value: 16-bit number 0 to 65535 (0xFFFF). For each bit 1 = enabled, 0 = disabled  
**Returns:** null
___
```
get_bus_pullups()
```
Get the internal 100K pull-up resistors for an IO bus  
**Returns:** (uint16_t) 16-bit number 0 to 65535 (0xFFFF). For each bit 1 = enabled, 0 = disabled  
___
```
write_pin(uint8_t pin, uint8_t value)
```
Write to an individual pin 1 - 16  
**Parameters:**  
pin: 1 to 16  
value: 1 = logic high, 0 = logic low  
**Returns:** null  
___
```
write_port(uint8_t port, uint8_t value)
```
Write to all pins on the selected port  
**Parameters:**  
port: 0 = pins 1 to 8, 1 = pins 9 to 16  
value:  number between 0 and 255 or 0x00 and 0xFF.  Each bit in the 8-bit number represents a pin on the port.  1 = logic high, 0 = logic low    
**Returns:** null  
___
```
write_bus(uint16_t value)
```
Write to all pins on the selected bus  
**Parameters:**  
value: 16-bit number 0 to 65535 (0xFFFF). For each bit 1 = logic high, 0 = logic low  
**Returns:** null  
___
```
read_pin(uint8_t pin)
```
Read the value of an individual pin 1 - 16   
**Parameters:**  
pin: 1 to 16  
**Returns:** (uint8_t) 0 = logic low, 1 = logic high  
___
```
read_port(uint8_t port)
```
Read all pins on the selected port  
**Parameters:**  
port: 0 = pins 1 to 8, 1 = pins 9 to 16  
**Returns:** (uint8_t) number between 0 and 255 or 0x00 and 0xFF.  Each bit in the 8-bit number represents a pin on the port.  0 = logic low, 1 = logic high
___
```
read_bus()
```
Read all pins on the bus  
**Returns:** (uint16_t) 16-bit number 0 to 65535 (0xFFFF) Each bit in the 16-bit number represents a pin on the port.  0 = logic low, 1 = logic high  
___
```
invert_pin(uint8_t pin, uint8_t polarity)
```
Invert the polarity of the selected pin  
**Parameters:**  
pin: 1 to 16  
polarity: 0 = same logic state of the input pin, 1 = inverted logic state of the input pin  
**Returns:** null
___
```
get_pin_polarity(uint8_t pin)
```  
Get the polarity of the selected pin  
**Parameters:**  
pin: pin to read, 1 to 16   
**Returns:** (uint8_t) 0 = same logic state of the input pin, 1 = inverted logic state of the input pin  
___
```
invert_port(uint8_t port, uint8_t polarity)
```
Invert the polarity of the pins on a selected port  
**Parameters:**  
port: 0 = pins 1 to 8, 1 = pins 9 to 16  
polarity: number between 0 and 255 or 0x00 and 0xFF.  Each bit in the 8-bit number represents a pin on the port.  0 = same logic state of the input pin, 1 = inverted logic state of the input pin  
**Returns:** null
___
```
get_port_polarity(uint8_t port): 
```
Get the polarity for the selected IO port  
**Parameters:**  
port: 0 = pins 1 to 8, 1 = pins 9 to 16   
**Returns:** (uint8_t) number between 0 and 255 (0xFF) 
___
```
invert_bus(uint16_t polarity)
```
Invert the polarity of the pins on the bus  
**Parameters:**  
polarity: 16-bit number 0 to 65535 (0xFFFF).  For each bit 0 = same logic state of the input pin, 1 = inverted logic state of the input pin  
**Returns:** null  
___
```
get_bus_polarity()
```
Get the polarity of the pins on the bus  
**Returns:** (uint16_t) 16-bit number 0 to 65535 (0xFFFF). For each bit 0 = same logic state of the input pin, 1 = inverted logic state of the input pin  
___
```
mirror_interrupts(uint8_t value)
```
Sets whether the interrupt pins INT A and INT B are independently connected to each port or internally connected together  
**Parameters:**  
value: 1 = The INT pins are internally connected, 0 = The INT pins are not connected. INT A is associated with PortA and INT B is associated with PortB    
**Returns:** null
___
```
set_interrupt_polarity(uint8_t value)
```
Sets the polarity of the INT output pins  
**Parameters:**  
value: 0 = Active Low, 1 = Active High  
**Returns:** null  
___
```
get_interrupt_polarity()
```
Get the polarity of the INT output pins  
**Returns:** (uint8_t) 1 = Active-high.  0 = Active-low.  
___
```
set_interrupt_type(uint8_t port, uint8_t value)
```
Sets the type of interrupt for each pin on the selected port  
**Parameters:**  
port: 0 = pins 1 to 8, 1 = pins 9 to 16  
value: number between 0 and 255 or 0x00 and 0xFF.  Each bit in the 8-bit number represents a pin on the port.  1 = interrupt is fired when the pin matches the default value, 0 = the interrupt is fired on state change  
**Returns:** null  
___
```
get_interrupt_type(uint8_t port): 
```
Get the type of interrupt for each pin on the selected port  
**Parameters:**  
port: 0 = pins 1 to 8, 1 = pins 9 to 16   
**Returns:** (uint8_t) number between 0 and 255 (0xFF)  
For each bit 1 = interrupt is fired when the pin matches the default value, 0 = interrupt fires on state change  
___
```
set_interrupt_defaults(uint8_t port, uint8_t value)
```
These bits set the compare value for pins configured for interrupt-on-change on the selected port.  
If the associated pin level is the opposite from the register bit, an interrupt occurs.    
**Parameters:**  
port: 0 = pins 1 to 8, 1 = pins 9 to 16, 
value: compare value between 0 and 255 or 0x00 and 0xFF.  Each bit in the 8-bit number represents a pin on the port.  
**Returns:** null  
___
```
get_interrupt_defaults(uint8_t port): 
```
Get the interrupt default value for each pin on the selected port  
**Parameters:**  
port: 0 = pins 1 to 8, 1 = pins 9 to 16   
**Returns:** (uint8_t) number between 0 and 255 (0xFF)  
___
```
set_interrupt_on_pin(uint8_t pin, uint8_t value)
```
Enable interrupts for the selected pin  
**Parameters:**  
pin: 1 to 16  
value: 0 = interrupt disabled, 1 = interrupt enabled  
**Returns:** null
___
```
get_interrupt_on_pin(uint8_t pin)
```  
Gets whether the interrupt is enabled for the selected pin  
**Parameters:**  
pin: pin to read, 1 to 16   
**Returns:** (uint8_t) 1 = enabled, 0 = disabled
___
```
set_interrupt_on_port(uint8_t port, uint8_t value)
```
Enable interrupts for the pins on the selected port  
**Parameters:**  
port: 0 = pins 1 to 8, 1 = pins 9 to 16  
value: number between 0 and 255 or 0x00 and 0xFF.  Each bit in the 8-bit number represents a pin on the port.  
**Returns:** null
___
```
get_interrupt_on_port(uint8_t port): 
```
Gets whether the interrupts are enabled for the selected port  
**Parameters:**  
port: 0 = pins 1 to 8, 1 = pins 9 to 16   
**Returns:** (uint8_t) number between 0 and 255 (0xFF).  For each bit 1 = enabled, 0 = disabled  
___
```
set_interrupt_on_bus(uint16_t value)
```
Enable interrupts for the pins on the bus  
**Parameters:**  
value: 16-bit number 0 to 65535 (0xFFFF).  For each bit 1 = enabled, 0 = disabled  
**Returns:** null
___
```
get_interrupt_on_bus()
```
Gets whether the interrupts are enabled for the bus  
**Returns:** (uint16_t) 16-bit number 0 to 65535 (0xFFFF). For each bit 1 = enabled, 0 = disabled  
___
```
read_interrupt_status(uint8_t port)
```
Read the interrupt status for the pins on the selected port  
**Parameters:**  
port: 0 = pins 1 to 8, 1 = pins 9 to 16  
**Returns:**  (uint8_t) number between 0 and 255 or 0x00 and 0xFF.  Each bit in the 8-bit number represents a pin on the port.  1 = Enabled, 0 = Disabled
___
```
read_interrupt_capture(uint8_t port)
```
Read the value from the selected port at the time of the last interrupt trigger  
**Parameters:**  
port: 0 = pins 1 to 8, 1 = pins 9 to 16  
**Returns:**  (uint8_t) number between 0 and 255 or 0x00 and 0xFF.  Each bit in the 8-bit number represents a pin on the port.  1 = Enabled, 0 = Disabled
___
```
reset_interrupts()
```
Set the interrupts A and B to 0  
**Parameters:** null  
**Returns:** null