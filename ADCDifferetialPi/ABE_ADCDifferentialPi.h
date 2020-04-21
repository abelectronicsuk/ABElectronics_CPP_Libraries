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
ADCDifferentialPi(unsigned char address1, unsigned char address2, unsigned char rate=18);

/**
* Reads the raw value from the selected ADC channel
* @param channel - 1 to 8
* @returns - raw long value from ADC buffer
*/
int read_raw(unsigned char channel);

/**
* Returns the voltage from the selected ADC channel
* @param channel - 1 to 8
* @returns - double voltage value from ADC
*/
double read_voltage(unsigned char channel);

/**
* Programmable Gain Amplifier gain selection
* @param gain - Set to 1, 2, 4 or 8
*/
void set_pga(unsigned char gain);

/**
* Set the sample resolution
* @param rate - 12 = 12 bit(240SPS max), 14 = 14 bit(60SPS max), 16 = 16 bit(15SPS max), 18 = 18 bit(3.75SPS max)
*/
void set_bit_rate(unsigned char rate);

/**
* Set the conversion mode for ADC
* @param mode - 0 = One shot conversion mode, 1 = Continuous conversion mode
*/
void set_conversion_mode(unsigned char mode);

private:

/**
* private method for writing a byte to the I2C port
*/
void write_byte(unsigned char reg, unsigned char value);

/**
* private method for reading bytes from the I2C port
*/
void read_byte_array(unsigned char address, unsigned char reg, unsigned char length);

/**
* private method for setting the value of a single bit within a byte
*/
char update_byte(unsigned char byte, unsigned char bit, unsigned char value);

/**
* private method for setting the channel
*/
void set_channel(unsigned char channel);

int i2cbus;
unsigned char i2caddress1;
unsigned char i2caddress2;
unsigned char config1;
unsigned char currentchannel1;
unsigned char config2;
unsigned char currentchannel2;
unsigned char bitrate;
unsigned char conversionmode;
double pga;
double lsb;
unsigned char writebuffer[1];
unsigned char readbuffer[10];
unsigned char signbit;

};
}
