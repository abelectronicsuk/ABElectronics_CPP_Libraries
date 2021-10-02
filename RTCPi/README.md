AB Electronics UK RTC Pi C++ Library
=====

C++ Library to use with RTC Pi Raspberry Pi real-time clock board from https://www.abelectronics.co.uk

The example C++ files can be found in /ABElectronics_CPP_Libraries/RTCPi/demos  

### Downloading and Installing the library

To download to your Raspberry Pi type in terminal: 

```
git clone https://github.com/abelectronicsuk/ABElectronics_CPP_Libraries.git
```

Clases:
----------

```
RTCPi(date) 
```
RTC class for accessing the DS1307 real time clock.  


Methods:
----------

```
set_date(struct tm date) 
```
Set the date and time on the RTC   
**Parameter:** date - struct tm formated date and time  
**Returns:** null
___
```
read_date() 
```
Returns the date from the RTC  
**Returns:** (tm struct) date
___
```
enable_output() 
```
Enable the square-wave output on the SQW pin.  
**Returns:** null
___
```
disable_output()
```
Disable the square-wave output on the SQW pin.   
**Returns:** null
___
```
set_frequency(uint8_t frequency)
```
Set the frequency for the square-wave output on the SQW pin.   
**Parameter:** frequency - options are: 1 = 1Hz, 2 = 4.096KHz, 3 = 8.192KHz, 4 = 32.768KHz   
**Returns:** null
___
```
write_memory(uint8_t address, uint8_t *valuearray, uint8_t length)
```
Write to the memory on the ds1307. The ds1307 contains 56-Byte, battery-backed RAM with Unlimited Writes  
**Parameter:** address - 0x08 to 0x3F  
**Parameter:** valuearray - uint8_t array containing data to be written to memory  
**Parameter:** length - up to 56 bytes.  array length can not exceed the available address space.  
**Returns:** null
___
```
read_memory(uint8_t address, uint8_t length)
```
Read from the memory on the ds1307  
**Parameter:** address - 0x08 to 0x3F  
**Parameter:** length - up to 56 bytes.  length can not exceed the available address space.  
**Returns:** (uint8_t*) array of bytes from the SRAM