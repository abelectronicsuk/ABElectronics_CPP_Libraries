/*
 ================================================
 AB Electronics UK IO Zero 32 : 32-Channel Port Expander
 See CHANGELOG.md for version number
 ================================================

 32-Channel Port Expander based on the PCA9535.
 The PCA9535 chip is split into two 8-bit ports.  Port 0 controls
 pins 1 to 8 while Port 1 controls pins 9 to 16.
 When writing to or reading from a bus or port the least significant bit
 represents the lowest numbered pin on the selected port.


 Required package{
 apt-get install libi2c-dev
 */

//#define TESTMODE // used for unit testing, comment out when using with the IO Pi board

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdexcept>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "ABE_IOZero32.h"

#ifdef TESTMODE
	#include "../UnitTest/testlibs.h"
    TestLibs unittest;
#endif

using namespace ABElectronics_CPP_Libraries;

IOZero32::IOZero32(uint8_t address)
{
	/**
	* IOZero32 object
	* @param address - I2C address for the target device
	*/
	if (address<0x20 || address> 0x27)
	{
		throw std::out_of_range("IOZero32 address out of range: 0x20 to 0x27");
	}

	i2caddress = address;
}

void IOZero32::set_pin_direction(uint8_t pin, uint8_t direction)
{
	/**
	* set IO direction for an individual pin
	* @param pins - 1 to 16
	* @param direction - 1 = input, 0 = output
	*/
	set_pin(pin, direction, PCA9535::CONFIGPORT0, PCA9535::CONFIGPORT1);
}

uint8_t IOZero32::get_pin_direction(uint8_t pin)
{
	/**
	* get IO direction for an individual pin
	* @param pins - 1 to 16
	*/
	return get_pin(pin, PCA9535::CONFIGPORT0, PCA9535::CONFIGPORT1);
}

void IOZero32::set_port_direction(uint8_t port, uint8_t direction)
{
	/**
	* set direction for an IO port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param direction - 0 to 255 (0xFF).  For each bit 1 = input, 0 = output
	*/
	set_port(port, direction, PCA9535::CONFIGPORT0, PCA9535::CONFIGPORT1);
}

uint8_t IOZero32::get_port_direction(uint8_t port)
{
	/**
	* get direction for an IO port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	*/
	return get_port(port, PCA9535::CONFIGPORT0, PCA9535::CONFIGPORT1);
}

void IOZero32::set_bus_direction(uint16_t direction)
{
	/**
	* set direction for the IO bus
	* @param direction - 0 to 65535 (0xFFFF).  For each bit 1 = input, 0 = output
	*/
	write_word_data(PCA9535::CONFIGPORT0, direction);
}

uint16_t IOZero32::get_bus_direction()
{
	/**
	* get direction for the IO bus
	*/
	return read_word_data(PCA9535::CONFIGPORT0);
}

void IOZero32::write_pin(uint8_t pin, uint8_t value)
{
	/**
	* write to an individual pin 1 - 16
	* @param pin - 1 to 16
	* @param value - 0 = logic low, 1 = logic high
	*/
	set_pin(pin, value, PCA9535::OUTPUTPORT0, PCA9535::OUTPUTPORT1);
}

void IOZero32::write_port(uint8_t port, uint8_t value)
{
	/**
	* write to all pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - 0 to 255 (0xFF)
	*/
	set_port(port, value, PCA9535::OUTPUTPORT0, PCA9535::OUTPUTPORT1);
}

void IOZero32::write_bus(uint16_t value)
{
	/**
	* write to all pins on the selected bus
	* @param value - 0 to 65535 (0xFFFF). For each bit 1 = logic high, 0 = logic low
	*/
	write_word_data(PCA9535::OUTPUTPORT0, value);
}

uint8_t IOZero32::read_pin(uint8_t pin)
{
	/**
	* read the value of an individual pin
	* @param pin - 1 to 16
	* @returns - 0 = logic low, 1 = logic high
	*/

	return get_pin(pin, PCA9535::INPUTPORT0, PCA9535::INPUTPORT1);
}

uint8_t IOZero32::read_port(uint8_t port)
{
	/**
	* read all pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @returns - 0 to 255 (0xFF). For each bit 1 = logic high, 0 = logic low
	*/
	return get_port(port, PCA9535::INPUTPORT0, PCA9535::INPUTPORT1);
}

uint16_t IOZero32::read_bus()
{
	/**
	* read all pins on the selected bus
	* @returns - 0 to 65535 (0xFFFF). For each bit 1 = logic high, 0 = logic low
	*/
	return read_word_data(PCA9535::INPUTPORT0);
}

void IOZero32::set_pin_polarity(uint8_t pin, uint8_t polarity)
{
	/**
	* set the polarity of the selected pin
	* @param pin - 1 to 16
	* @param polarity - 0 = non-inverted, 1 = inverted
	*/
	set_pin(pin, polarity, PCA9535::INVERTPORT0, PCA9535::INVERTPORT1);
}

uint8_t IOZero32::get_pin_polarity(uint8_t pin)
{
	/**
  	* get the polarity of the selected pin
  	* @param pin - 1 to 16
  	*/
  	return get_pin(pin, PCA9535::INVERTPORT0, PCA9535::INVERTPORT1);
}

void IOZero32::set_port_polarity(uint8_t port, uint8_t polarity)
{
	/**
	* set the polarity of the pins on a selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param polarity - 0 to 255 (0xFF). For each bit 0 = non-inverted, 1 = inverted
	*/
	set_port(port, polarity, PCA9535::INVERTPORT0, PCA9535::INVERTPORT1);
}

uint8_t IOZero32::get_port_polarity(uint8_t port)
{
	/**
  	* get the polarity of the selected pin
  	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
  	*/
  	return get_port(port, PCA9535::INVERTPORT0, PCA9535::INVERTPORT1);
}

void IOZero32::set_bus_polarity(uint16_t polarity)
{
	/**
	* set the polarity of the pins on a selected bus
	* @param polarity - 0 to 65535 (0xFFFF). For each bit 0 = non-inverted, 1 = inverted
	*/
	write_word_data(PCA9535::INVERTPORT0, polarity);
}

 uint16_t IOZero32::get_bus_polarity()
 {
	 /**
  	* get the polarity of the bus
  	*/
  	return read_word_data(PCA9535::INVERTPORT0);
 }

// stops file handle leakage on exceptions
class ScopedFileHandle
{
public:
	ScopedFileHandle(int fd) : _fd(fd) {}
	~ScopedFileHandle()
	{
		if (_fd >= 0)
			close(_fd);
	}
	operator int() const { return _fd; }

private:
	int _fd;
};

uint8_t IOZero32::read_byte_data(uint8_t reg)
{
	/**
	* private method for reading a byte from the I2C port
	*/
	#ifdef TESTMODE		
		buf[0] = unittest.i2c_emulator_read_byte_data(reg);
	#else

	ScopedFileHandle i2cbus(open(fileName, O_RDWR));
	if (i2cbus < 0)
	{
		throw std::runtime_error("Failed to open i2c port for read");
	}

	if (ioctl(i2cbus, I2C_SLAVE, i2caddress) < 0)
	{
		throw std::runtime_error("Failed to write to i2c port for read");
	}

	buf[0] = reg;

	if ((write(i2cbus, buf, 1)) != 1)
	{
		throw std::runtime_error("Failed to write to i2c device for read");
	}

	if (read(i2cbus, buf, 1) != 1)
	{ // Read back data into buf[]
		throw std::runtime_error("Failed to read from slave");
	}

	close(i2cbus);

	#endif

	return (buf[0]);
}

uint16_t IOZero32::read_word_data(uint8_t reg)
{
	/**
	* private method for reading a byte from the I2C port
	*/
	#ifdef TESTMODE		
		return (unittest.i2c_emulator_read_word_data(reg));
	#else

	ScopedFileHandle i2cbus(open(fileName, O_RDWR));
	if (i2cbus < 0)
	{
		throw std::runtime_error("Failed to open i2c port for read");
	}

	if (ioctl(i2cbus, I2C_SLAVE, i2caddress) < 0)
	{
		throw std::runtime_error("Failed to write to i2c port for read");
	}

	buf[0] = reg;

	if ((write(i2cbus, buf, 1)) != 1)
	{
		throw std::runtime_error("Failed to write to i2c device for read");
	}

	if (read(i2cbus, buf, 2) != 2)
	{ // Read back data into buf[]
		throw std::runtime_error("Failed to read from slave");
	}

	close(i2cbus);

	uint16_t value = (buf[1] << 8) | buf[0];
	return (value);

	#endif
}

void IOZero32::write_byte_data(uint8_t reg, uint8_t value)
{
	/**
	* private method for writing a byte to the I2C port
	*/
	#ifdef TESTMODE
		unittest.i2c_emulator_write_byte_data(reg, value);
	#else

	ScopedFileHandle i2cbus(open(fileName, O_RDWR));
	if (i2cbus < 0)
	{
		throw std::runtime_error("Failed to open i2c port for write");
	}

	if (ioctl(i2cbus, I2C_SLAVE, i2caddress) < 0)
	{
		throw std::runtime_error("Failed to write to i2c port for write");
	}

	buf[0] = reg;
	buf[1] = value;

	if ((write(i2cbus, buf, 2)) != 2)
	{
		throw std::runtime_error("Failed to write to i2c device for write");
	}

	close(i2cbus);

	#endif
}

void IOZero32::write_word_data(uint8_t reg, uint16_t value)
{
	/**
	* private method for writing a byte to the I2C port
	*/
	#ifdef TESTMODE
		unittest.i2c_emulator_write_word_data(reg, value);
	#else

	ScopedFileHandle i2cbus(open(fileName, O_RDWR));
	if (i2cbus < 0)
	{
		throw std::runtime_error("Failed to open i2c port for write");
	}

	if (ioctl(i2cbus, I2C_SLAVE, i2caddress) < 0)
	{
		throw std::runtime_error("Failed to write to i2c port for write");
	}


	buf[0] = reg;
	buf[1] = (uint8_t)(value&(0xff)); // lower 8 bits
	buf[2] = (uint8_t)(value>>8) & 0xff; // upper 8 bits

	if ((write(i2cbus, buf, 3)) != 3)
	{
		throw std::runtime_error("Failed to write to i2c device for write");
	}

	close(i2cbus);

	#endif
}

uint8_t IOZero32::updatebyte(uint8_t byte, uint8_t bit, uint8_t value)
{
	/**
	* private method for updating a bit within a byte
	*/
	if (value == 0)
	{
		return (byte &= ~(1 << bit));
	}
	else
	{
		return (byte |= 1 << bit);
	}
}

uint8_t IOZero32::checkbit(uint8_t byte, uint8_t bit)
{
	/**
	* private method for checking the status of a bit within a byte
	*/
	if (byte & (1 << bit))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

void IOZero32::set_pin(uint8_t pin, uint8_t value, uint8_t a_register, uint8_t b_register)
{
	/**
	* private method for setting the value of a single bit within the device registers
	*/
	uint8_t reg = 0;
	uint8_t p = 0;
	if (pin >= 1 && pin <= 8)
	{
		reg = a_register;
		p = pin - 1;
	}
	else if (pin >= 9 && pin <= 16)
	{
		reg = b_register;
		p = pin - 9;
	}
	else
	{
		throw std::out_of_range("pin out of range: 1 to 16");
	}

	if (value > 1)
	{
		throw std::out_of_range("value out of range: 0 or 1");
	}

	uint8_t newval = updatebyte(read_byte_data(reg), p, value);
	write_byte_data(reg, newval);
}

uint8_t IOZero32::get_pin(uint8_t pin, uint8_t a_register, uint8_t b_register)
{
	/**
	* private method for getting the value of a single bit within the device registers
	*/

		uint8_t value = 0;

        if (pin >= 1 && pin <= 8)
		{
            value = checkbit(read_byte_data(a_register), pin - 1);
		}
        else if (pin >= 9 && pin <= 16)
		{
            value = checkbit(read_byte_data(b_register), pin - 9);
		}
        else
		{
            throw std::out_of_range("pin out of range: 1 to 16");
		}

        return value;
}

void IOZero32::set_port(uint8_t port, uint8_t value, uint8_t a_register, uint8_t b_register)
{
	/**
	* private method for setting the value of a device register
	*/
	if (port == 0)
	{
    	write_byte_data(a_register, value);
	}
    else if (port == 1)
	{
    	write_byte_data(b_register, value);
	}
	else
	{
		throw std::out_of_range("port out of range: 0 or 1");
	}
}

uint8_t IOZero32::get_port(uint8_t port, uint8_t a_register, uint8_t b_register)
{
	/**
	* private method for getting the value of a device register
	*/
	if (port == 0)
	{
    	return read_byte_data(a_register);
	}
    else if (port == 1)
	{
    	return read_byte_data(b_register);
	}
	else
	{
		throw std::out_of_range("port out of range: 0 or 1");
	}
}

void IOZero32::set_bus(uint16_t value, uint8_t a_register){
	/**
	* private method for writing a 16-bit value to two consecutive device registers
	*/
	write_word_data(a_register, value);
}
