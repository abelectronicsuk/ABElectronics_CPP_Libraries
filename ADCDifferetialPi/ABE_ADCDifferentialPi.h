/*
 ================================================
 ABElectronics UK ADC Differential Pi 8-Channel Analogue to Digital Converter
 Version 1.1 Updated 21/04/2020
 ================================================

Reads from the MCP3424 ADC on the ADC Differential Pi.

 Required package{
 apt-get install libi2c-dev
 */

namespace ABElectronics_CPP_Libraries
{
class ADCDifferentialPi
{

public:

/**
 * Initialises the ADCs
 * @param address1 - I2C address1 for the target device e.g. 0x68
 * @param address2 - I2C address2 for the target device e.g. 0x69
 * @param bitrate (optional) - 12, 14, 16 or 18
 */
ADCDifferentialPi(uint8_t address1, uint8_t address2, uint8_t rate=18);

/**
* Reads the raw value from the selected ADC channel
* @param channel - 1 to 8
* @returns - raw uint32_t value from ADC buffer
*/
uint32_t read_raw(uint8_t channel);

/**
* Returns the voltage from the selected ADC channel
* @param channel - 1 to 8
* @returns - double voltage value from ADC
*/
double read_voltage(uint8_t channel);

/**
* Programmable Gain Amplifier gain selection
* @param gain - Set to 1, 2, 4 or 8
*/
void set_pga(uint8_t gain);

/**
* Set the sample resolution
* @param rate - 12 = 12 bit(240SPS max), 14 = 14 bit(60SPS max), 16 = 16 bit(15SPS max), 18 = 18 bit(3.75SPS max)
*/
void set_bit_rate(uint8_t rate);

/**
* Set the conversion mode for ADC
* @param mode - 0 = One shot conversion mode, 1 = Continuous conversion mode
*/
void set_conversion_mode(uint8_t mode);

private:

/**
* private method for writing a byte to the I2C port
*/
void write_byte(uint8_t reg, uint8_t value);

/**
* private method for reading bytes from the I2C port
*/
void read_byte_array(uint8_t address, uint8_t reg, uint8_t length);

/**
* private method for setting the value of a single bit within a byte
*/
char update_byte(uint8_t byte, uint8_t bit, uint8_t value);

/**
* private method for setting the channel
*/
void set_channel(uint8_t channel);

int i2cbus;
uint8_t i2caddress1;
uint8_t i2caddress2;
uint8_t config1;
uint8_t currentchannel1;
uint8_t config2;
uint8_t currentchannel2;
uint8_t bitrate;
uint8_t conversionmode;
double pga;
double lsb;
uint8_t writebuffer[1];
uint8_t readbuffer[10];
uint8_t signbit;

};
}
