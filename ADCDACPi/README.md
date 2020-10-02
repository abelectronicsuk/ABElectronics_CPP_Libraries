AB Electronics UK ADCDAC Pi C++ Library
=====

C++ Library to use with ADCDAC Pi Raspberry Pi expansion board from https://www.abelectronics.co.uk

The example demo files can be found in /ABElectronics_CPP_Libraries/ADCDACPi/demos.

### Downloading and Installing the library

To download to your Raspberry Pi type in terminal: 

```
git clone https://github.com/abelectronicsuk/ABElectronics_CPP_Libraries.git
```

Classes:
----------  
```
ADCDACPi()
```

Methods:
----------

```
open_adc()
```
Open the ADC SPI bus channel.  This needs to be called before using the ADC.  
___
```
close_adc()
```
Close the ADC SPI bus channel.  
___
```
open_dac()
```
Open the DAC SPI bus channel.  This needs to be called before using the DAC.  
___
```
close_dac()
```
Close the DAC SPI bus channel.  
___
```
read_adc_voltage(uint8_t channel, uint8_t mode) 
```
Read the voltage from the selected channel on the ADC  
**Parameter:** channel - 1 or 2  
**Parameter:** mode - 0 = single ended, 1 = differential  
**Returns:** (double) between 0V and the reference voltage
___
```
read_adc_raw(uint8_t channel, uint8_t mode) 
```
Read the raw value from the selected channel on the ADC  
**Parameter:** channel - 1 or 2  
**Parameter:** mode - 0 = Single Ended or 1 = Differential  
When in differential mode setting channel to 1 will make IN1 = IN+ and IN2 = IN-  
When in differential mode setting channel to 2 will make IN1 = IN- and IN2 = IN+  
**Returns:** (uint16_t) 12 bit value between 0 and 4096  
___
```
set_adc_refvoltage(double ref)
```
Set the reference voltage for the analogue to digital converter.  
The ADC uses the raspberry pi 3.3V power as a voltage reference so using this method to set the reference to match the exact output voltage from the 3.3V regulator will increase the accuracy of the ADC readings.  
**Parameter:** ref - reference voltage  
**Returns:** null  
___
```
set_dac_voltage(double voltage, uint8_t channel)
```
Set the voltage for the selected channel on the DAC.  The DAC has two gain values, 1 or 2, which can be set when the ADCDAC object is created.  A gain of 1 will give a voltage between 0 and 2.047 volts.  A gain of 2 will give a voltage between 0 and 3.3 volts.  
**Parameter:**  channel - 1 or 2  
**Parameter:**  voltage - target DAC voltage  
**Returns:** null 
___
```
set_dac_raw(uint16_t raw, uint8_t channel)
```
Set the raw value for the selected channel on the DAC  
**Parameter:**  raw - between 0 and 4095  
**Parameter:**  channel - 1 or 2  
**Returns:** null  
___
```
set_dac_gain(uint8_t gain)
```
Set the DAC gain  
**Parameter:** gain - 1 or 2 - The output voltage will be between 0 and 2.048V when gain is set to 1,  0 and 3.3V when gain is set to 2  	  
**Returns:** null  