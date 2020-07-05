AB Electronics UK ADC Pi C++ Library
=====

C++ Library to use with ADC Pi Raspberry Pi expansion board from https://www.abelectronics.co.uk

The example CPP files can be found in /ABElectronics_CPP_Libraries/ADCPi/demos  

### Downloading and Installing the library

To download to your Raspberry Pi type in terminal: 

```
git clone https://github.com/abelectronicsuk/ABElectronics_CPP_Libraries.git
```

Classes:
----------
```
ADCPi(uint8_t address1, uint8_t address2, uint8_t rate)
```
**Parameter:** address1 - I2C address of ADC chip 1. 0x68 to 0x6F  
**Parameter:** address2 - I2C address of ADC chip 2. 0x68 to 0x6F  
**Parameter:** rate - Bit rate for ADC sampling.  12, 14, 16 or 18 

Methods:
----------
```
read_voltage(uint8_t channel) 
```
Read the voltage from the selected channel  
**Parameter:** channel - 1 to 8  
**Returns:** (double) number between 0 and 5.06
___
```
read_raw(uint8_t channel) 
```
Read the raw value from the selected channel  
**Parameter:** channel - 1 to 8  
**Returns:** (uint32_t) raw number
___
```
set_pga(uint8_t gain)
```
Set the gain of the PGA on the chip  
**Parameter:** gain -  1, 2, 4, 8  
**Returns:** null
___
```
set_bit_rate(uint8_t rate)
```
Set the sample bit rate of the adc  
**Parameter:** rate -  12, 14, 16, 18  
12 = 12 bit (240SPS max)  
14 = 14 bit (60SPS max)  
16 = 16 bit (15SPS max)  
18 = 18 bit (3.75SPS max)  
**Returns:** null  

___
```
set_conversion_mode(uint8_t mode)
```
Set the conversion mode for the adc  
**Parameter:** mode -  0 = One-shot conversion, 1 = Continuous conversion  
**Returns:** null