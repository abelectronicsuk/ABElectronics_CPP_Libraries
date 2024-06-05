/*
================================================
AB Electronics UK ADC-DAC Pi
See CHANGELOG.md for the version number.
================================================
*/

#ifndef ADCDACPI_ABE_ADCDACPI_H_
#define ADCDACPI_ABE_ADCDACPI_H_
#endif /* ADCDACPI_ABE_ADCDACPI_H_ */

namespace ABElectronics_CPP_Libraries
{
class ADCDACPi
{

// public methods

public:

ADCDACPi();

/**
* Open the ADC SPI bus channel.
* This needs to be called before using the DAC.
*/
int open_adc();

/**
* Close the ADC SPI bus channel.
*/
void close_adc();

/**
* Open the DAC SPI bus channel.
* This needs to be called before using the DAC.
*/
int open_dac();

/**
* Close the DAC SPI bus channel.
*/
void close_dac();

/**
* Read the voltage from the ADC.
* @param channel - 1 or 2
* @param mode - 0 = Single Ended or 1 = Differential
* When in differential mode, setting the channel to 1 will make IN1 = IN+ and IN2 = IN-
* When in differential mode, setting the channel to 2 will make IN1 = IN- and IN2 = IN+
* @returns between 0V and the reference voltage
*/
double read_adc_voltage(uint8_t channel, uint8_t mode);

/**
* Read the raw value from the ADC.
* @param channel -  1 to 8
* @param mode -  0 = Single Ended or 1 = Differential
* When in differential mode, setting the channel to 1 will make IN1 = IN+ and IN2 = IN-
* When in differential mode, setting the channel to 2 will make IN1 = IN- and IN2 = IN+
* @returns 12-bit value between 0 and 4096
*/
uint16_t read_adc_raw(uint8_t channel, uint8_t mode);

/**
* Set the reference voltage for the ADC.
* @param ref - Set this value to be the same as the voltage measured on the 3.3V GPIO pin
*/
void set_adc_refvoltage(double ref);

/**
* Set the DAC voltage.
* @param voltage - between 0 and 2.048 when the gain is set to 1,  0 and 3.3 when the gain is set to 2
* @param channel - 1 or 2
*/
void set_dac_voltage(double voltage, uint8_t channel);

/**
* Set the raw value from the selected channel on the DAC.
* @param raw - between 0 and 4095
* @param channel - 1 or 2
*/
void set_dac_raw(uint16_t raw, uint8_t channel);

/**
* Set the DAC gain.
* @param gain - 1 or 2 - The output voltage will be between 0 and 2.048V when the gain is set to 1,  0 and 3.3V when the gain is set to 2	
*/
void set_dac_gain(uint8_t gain);

private:
// private variables
uint8_t spi_mode; // SPI_MODE_0
uint32_t adcspeed; // SPI ADC bus speed.
uint32_t dacspeed; // SPI DAC bus speed.

uint8_t adctx[3]; // transmit buffer for the ADC
uint8_t adcrx[3]; // receive buffer for the ADC
uint8_t dactx[2]; // transmit buffer for the DAC
int adc; // adc object
int dac; // dac object

double adcrefvoltage; // reference voltage for the ADC chip
uint8_t dacgain; // gain setting for the DAC chip
double dacvoltage; // maximum voltage for the DAC output

};
}
