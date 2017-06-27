/*
 ================================================
 ABElectronics UK ADC Pi 8-Channel Analogue to Digital Converter
 Version 1.0 Created 21/06/2017
 ================================================

Reads from the MCP3424 ADC on the ADC Pi and ADC Pi Plus.

 Required package{
 apt-get install libi2c-dev
 */

namespace ABElectronics_CPP_Libraries
{
class ADCPi
{

public:

/**
 * Initialises the ADCs
 * @param address1 - I2C address1 for the target device e.g. 0x68
 * @param address2 - I2C address2 for the target device e.g. 0x69
 * @param bitrate (optional) - 12, 14, 16 or 18
 */
ADCPi(char address1, char address2, char rate=18);

/**
* Reads the raw value from the selected ADC channel
* @param channel - 1 to 8
* @returns - raw long value from ADC buffer
*/
int read_raw(char channel);


/**
* Returns the voltage from the selected ADC channel
* @param channel - 1 to 8
* @returns - double voltage value from ADC
*/
double read_voltage(char channel);

/**
* Programmable Gain Amplifier gain selection
* @param gain - Set to 1, 2, 4 or 8
*/
void set_pga(char gain);

/**
* Set the sample resolution
* @param rate - 12 = 12 bit(240SPS max), 14 = 14 bit(60SPS max), 16 = 16 bit(15SPS max), 18 = 18 bit(3.75SPS max)
*/
void set_bit_rate(char rate);

/**
* Set the conversion mode for ADC
* @param mode - 0 = One shot conversion mode, 1 = Continuous conversion mode
*/
void set_conversion_mode(char mode);

private:

/**
* private method for writing a byte to the I2C port
*/
void write_byte(char reg, char value);

/**
* private method for reading bytes from the I2C port
*/
void read_byte_array(char address, char reg, char length);

/**
* private method for setting the value of a single bit within a byte
*/
char update_byte(char byte, char bit, char value);

/**
* private method for setting the channel
*/
void set_channel(char channel);

int i2cbus;
char i2caddress1;
char i2caddress2;
char config1;
char currentchannel1;
char config2;
char currentchannel2;
char bitrate;
char conversionmode;
double pga;
double lsb;
char writebuffer[1];
char readbuffer[10];
char signbit;

};
}
