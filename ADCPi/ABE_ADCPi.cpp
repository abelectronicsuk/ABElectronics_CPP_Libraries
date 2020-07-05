/*
 ================================================
 ABElectronics UK ADC Pi 8-Channel Analogue to Digital Converter
 Version 1.1 Updated 21/04/2020
 ================================================

Reads from the MCP3424 ADC on the ADC Pi and ADC Pi Plus.

 Required package{
 apt-get install libi2c-dev
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdexcept>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "ABE_ADCPi.h"

#define fileName "/dev/i2c-1" // change to /dev/i2c-0 if you are using a revision 0002 or 0003 model B

using namespace ABElectronics_CPP_Libraries;

// stops file handle leakage on exceptions
class ScopedFileHandle{
public:
    ScopedFileHandle(int fd) :_fd(fd){}
    ~ScopedFileHandle(){ if(_fd >= 0) close(_fd); }
    operator int() const { return _fd; }
private:
    int _fd;
};

ADCPi::ADCPi(uint8_t address1, uint8_t address2, uint8_t rate)
{
	if (address1 < 0x68 || address1 > 0x6F)
	{
		throw std::out_of_range("ADCPi address1 out of range: 0x68 to 0x6F");
	}

	if (address2 < 0x68 || address2 > 0x6F)
	{
		throw std::out_of_range("ADCPi address2 out of range: 0x68 to 0x6F");
	}

	signbit = 0;
	i2caddress1 = address1;
	i2caddress2 = address2;
	config1 = (uint8_t)0x9C;		 // PGAx1, 18 bit, continuous conversion, channel 1
	currentchannel1 = (uint8_t)1; // channel variable for adc 1
	config2 = (uint8_t)0x9C;		 // PGAx1, 18 bit, continuous-shot conversion, channel 1
	currentchannel2 = (uint8_t)1; // channel variable for adc2
	bitrate = (uint8_t)18;		 // current bitrate
	conversionmode = (uint8_t)1;  // Conversion Mode
	pga = 0.5;			 // current pga setting
	lsb = 0.000007812;   // default lsb value for 18 bit

	set_bit_rate(rate);
}
// public methods


uint32_t ADCPi::read_raw(uint8_t channel)
{
	/**
	* Reads the raw value from the selected ADC channel
	* @param channel - 1 to 8
	* @returns - raw long value from ADC buffer
	*/

	// variables for storing the raw bytes from the ADC
	char h = 0;
	char l = 0;
	char m = 0;
	char s = 0;
	char config = 0;
	char address = 0;
	long t = 0;
	signbit = 0;

	// get the config and i2c address for the selected channel
	set_channel(channel);

	if (channel > 0 && channel < 5)
	{
		config = config1;
		address = i2caddress1;
	}
	else if (channel < 9)
	{
		config = config2;
		address = i2caddress2;
	}else
	{
		throw std::out_of_range("read_raw() channel out of range: 1 to 8");
	}

	// if the conversion mode is set to one-shot update the ready bit to 1
	if (conversionmode == 0)
	{
		config = config | (1 << 7);
		write_byte(address, config);
		config = config & ~(1 << 7);
	}

	// keep reading the ADC data until the conversion result is ready
	uint32_t timeout = 10000; // number of reads before a timeout occurs
	uint32_t x = 0;
	
	do
	{
		if (bitrate == 18)
		{
			read_byte_array(address, config, 4);
			h = readbuffer[0];
			m = readbuffer[1];
			l = readbuffer[2];
			s = readbuffer[3];
		}
		else
		{
			read_byte_array(address, config, 3);
			h = readbuffer[0];
			m = readbuffer[1];
			s = readbuffer[2];
		}

		// check bit 7 of s to see if the conversion result is ready
		if ((s & (1 << 7)) == 0)
		{
			break;
		}

		if (x > timeout)
		{
			// timeout occurred
			throw std::runtime_error("read_raw() timeout occurred");
		}

		x++;
	} while (1);

	// extract the returned bytes and combine in the correct order
	switch (bitrate)
	{
	case 18:
		t = ((h & 0x03) << 16) | (m << 8) | l;
		if ((t >> 17) & 1)
		{
			signbit = 1;
			t &= ~(1 << 17);
		}
		break;
	case 16:
		t = (h << 8) | m;
		if ((t >> 15) & 1)
		{
			signbit = 1;
			t &= ~(1 << 15);
		}
		break;
	case 14:
		t = ((h & 63) << 8) | m;
		if ((t >> 13) & 1)
		{
			signbit = 1;
			t &= ~(1 << 13);
		}
		break;
	case 12:
		t = ((h & 15) << 8) | m;
		if ((t >> 11) & 1)
		{
			signbit = 1;
			t &= ~(1 << 11);
		}
		break;
	default:
		throw std::runtime_error("read_raw() bitrate out of range");
		break;
	}

	return (t);
}


double ADCPi::read_voltage(uint8_t channel)
{
	/**
	* Returns the voltage from the selected ADC channel
	* @param channel - 1 to 8
	* @returns - double voltage value from ADC
	*/
	uint32_t raw = read_raw(channel); // get the raw value

	if (signbit == 1) // if the signbit is 1 the value is negative and most likely noise so it can be ignored.
	{
		return (0);
	}
	else
	{
		double voltage = ((double)raw * (lsb / pga)) * 2.471; // calculate the voltage and return it
		return (voltage);
	}
}

void ADCPi::set_pga(uint8_t gain)
{
	/**
	* Programmable Gain Amplifier gain selection
	* @param gain - Set to 1, 2, 4 or 8
	*/
	switch (gain)
	{
	case 1:
		config1 = update_byte(config1, (uint8_t)0xFC, (uint8_t)0x00);
		config2 = update_byte(config2, (uint8_t)0xFC, (uint8_t)0x00);
		pga = 0.5;
		break;
	case 2:
		config1 = update_byte(config1, (uint8_t)0xFC, (uint8_t)0x01);
		config2 = update_byte(config2, (uint8_t)0xFC, (uint8_t)0x01);
		pga = 1;
		break;
	case 4:
		config1 = update_byte(config1, (uint8_t)0xFC, (uint8_t)0x02);
		config2 = update_byte(config2, (uint8_t)0xFC, (uint8_t)0x02);
		pga = 2;
		break;
	case 8:
		config1 = update_byte(config1, (uint8_t)0xFC, (uint8_t)0x03);
		config2 = update_byte(config2, (uint8_t)0xFC, (uint8_t)0x03);
		pga = 4;
		break;
	default:
		throw std::out_of_range("set_pga() gain out of range: 1, 2, 4, 8");
		break;
	}

	write_byte(i2caddress1, config1);
	write_byte(i2caddress2, config2);
}

void ADCPi::set_bit_rate(uint8_t rate)
{
	/**
	* Set the sample resolution
	* @param rate - 12 = 12 bit(240SPS max), 14 = 14 bit(60SPS max), 16 = 16 bit(15SPS max), 18 = 18 bit(3.75SPS max)
	*/
	switch (rate)
	{
	case 12:
		config1 = update_byte(config1, (uint8_t)0xF3, (uint8_t)0x00);
		config2 = update_byte(config2, (uint8_t)0xF3, (uint8_t)0x00);
		bitrate = 12;
		lsb = 0.0005;
		break;
	case 14:
		config1 = update_byte(config1, (uint8_t)0xF3, (uint8_t)0x04);
		config2 = update_byte(config2, (uint8_t)0xF3, (uint8_t)0x04);
		bitrate = 14;
		lsb = 0.000125;
		break;
	case 16:
		config1 = update_byte(config1, (uint8_t)0xF3, (uint8_t)0x08);
		config2 = update_byte(config2, (uint8_t)0xF3, (uint8_t)0x08);
		bitrate = 16;
		lsb = 0.00003125;
		break;
	case 18:
		config1 = update_byte(config1, (uint8_t)0xF3, (uint8_t)0x0C);
		config2 = update_byte(config2, (uint8_t)0xF3, (uint8_t)0x0C);
		bitrate = 18;
		lsb = 0.0000078125;
		break;
	default:
		throw std::out_of_range("set_bit_rate() rate out of range: 12, 14, 16, 18");
		break;
	}

	write_byte(i2caddress1, config1);
	write_byte(i2caddress2, config2);
}

void ADCPi::set_conversion_mode(uint8_t mode)
{
	/**
	* Set the conversion mode for ADC
	* @param mode - 0 = One shot conversion mode, 1 = Continuous conversion mode
	*/

	if (mode == 0)
	{
		config1 = update_byte(config1, (uint8_t)0xEF, (uint8_t)0x00);
		config2 = update_byte(config2, (uint8_t)0xEF, (uint8_t)0x00);
		conversionmode = 0;
	}
	else if (mode == 1)
	{
		config1 = update_byte(config1, (uint8_t)0xEF, (uint8_t)0x10);
		config2 = update_byte(config2, (uint8_t)0xEF, (uint8_t)0x10);
		conversionmode = 1;
	}
	else
	{
		throw std::out_of_range("set_conversion_mode() mode out of range: 0 or 1");
	}
}

// private methods

void ADCPi::write_byte(uint8_t address, uint8_t value)
{
	/**
	* private method for writing a byte to the I2C port
	*/

	// open the i2c bus
	ScopedFileHandle i2cbus(open(fileName, O_RDWR));
    if (i2cbus < 0)
	{
		throw std::runtime_error("Failed to open i2c port for write");
	}

	if (ioctl(i2cbus, I2C_SLAVE, address) < 0)
	{
		throw std::runtime_error("Failed to write to i2c port for write");
	}

	writebuffer[0] = value;

	if ((write(i2cbus, writebuffer, 1)) != 1)
	{
		throw std::runtime_error("Failed to write to i2c device for write");
	}

	close(i2cbus);
}

void ADCPi::read_byte_array(uint8_t address, uint8_t reg, uint8_t length)
{
	/**
	* private method for reading bytes from the I2C port
	*/
	ScopedFileHandle i2cbus(open(fileName, O_RDWR));
	if (i2cbus < 0)
	{
		throw std::runtime_error("Failed to open i2c port for read");
	}

	if (ioctl(i2cbus, I2C_SLAVE, address) < 0)
	{
		throw std::runtime_error("Failed to write to i2c port for read");
	}

	writebuffer[0] = reg;

	if ((write(i2cbus, writebuffer, 1)) != 1)
	{
		throw std::runtime_error("Failed to write to i2c device for read");
	}

	read(i2cbus, readbuffer, length);

	close(i2cbus);
}

char ADCPi::update_byte(uint8_t byte, uint8_t mask, uint8_t value)
{
	/**
	* private method for setting the value of a single bit within a byte
	*/
	byte &= mask;
    byte |= value;
    return byte;
}

void ADCPi::set_channel(uint8_t channel)
{
	/**
	* private method for setting the channel
	*/
	if (channel >= 1 && channel <= 4)
	{
		if (channel != currentchannel1)
		{
			currentchannel1 = channel;
			switch (channel)
			{
			case 1:
				config1 = update_byte(config1, (uint8_t)0x9F, (uint8_t)0x00);
				break;
			case 2:
				config1 = update_byte(config1, (uint8_t)0x9F, (uint8_t)0x20);
				break;
			case 3:
				config1 = update_byte(config1, (uint8_t)0x9F, (uint8_t)0x40);
				break;
			case 4:
				config1 = update_byte(config1, (uint8_t)0x9F, (uint8_t)0x60);
				break;
			}
		}
	}
	else if (channel >= 5 && channel <= 8)
	{
		if (channel != currentchannel2)
		{
			currentchannel2 = channel;
			switch (channel)
			{
			case 5:
				config2 = update_byte(config2, (uint8_t)0x9F, (uint8_t)0x00);
				break;
			case 6:
				config2 = update_byte(config2, (uint8_t)0x9F, (uint8_t)0x20);
				break;
			case 7:
				config2 = update_byte(config2, (uint8_t)0x9F, (uint8_t)0x40);
				break;
			case 8:
				config2 = update_byte(config2, (uint8_t)0x9F, (uint8_t)0x60);
				break;
			}
		}
	}
	else{
		throw std::out_of_range("set_channel() channel out of range: 1 to 8");
	}
}
