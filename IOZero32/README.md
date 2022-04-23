AB Electronics UK IO Zero 32 C++ Library
=====

C++ Library to use with IO Zero 32 Raspberry Pi expansion board from https://www.abelectronics.co.uk

The example demo files can be found in /ABElectronics_CPP_Libraries/IOZero32/demos  

### Downloading and Installing the library

To download to your Raspberry Pi type in terminal: 

```
git clone https://github.com/abelectronicsuk/ABElectronics_CPP_Libraries.git
```

Classes:
----------  
```
IOZero32(address)
```
**Parameters:**  
address: i2c address for the target device. 0x20 to 0x27  


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
set_pin_polarity(uint8_t pin, uint8_t polarity)
```
Set the polarity of the selected pin  
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
set_port_polarity(uint8_t port, uint8_t polarity)
```
Set the polarity of the pins on a selected port  
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
set_bus_polarity(uint16_t polarity)
```
Set the polarity of the pins on the bus  
**Parameters:**  
polarity: 16-bit number 0 to 65535 (0xFFFF).  For each bit 0 = same logic state of the input pin, 1 = inverted logic state of the input pin  
**Returns:** null  
___
```
get_bus_polarity()
```
Get the polarity of the pins on the bus  
**Returns:** (uint16_t) 16-bit number 0 to 65535 (0xFFFF). For each bit 0 = same logic state of the input pin, 1 = inverted logic state of the input pin  
