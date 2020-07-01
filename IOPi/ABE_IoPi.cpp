/*
 ================================================
 ABElectronics UK IO Pi 32-Channel Port Expander
 Version 1.1.0 Updated 01/07/2020
 ================================================


 Each MCP23017 chip is split into two 8-bit ports.  port 0 controls
 pins 1 to 8 while port 1 controls pins 9 to 16.
 When writing to or reading from a port the least significant bit represents
 the lowest numbered pin on the selected port.


 Required package{
 apt-get install libi2c-dev
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdexcept>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "ABE_IoPi.h"

#define fileName "/dev/i2c-1" // change to /dev/i2c-0 if you are using a Raspberry Pi revision 0002 or 0003 model B

#define IODIRA 0x00 // IO direction A - 1= input 0 = output
#define IODIRB 0x01 // IO direction B - 1= input 0 = output
// Input polarity A - If a bit is set, the corresponding GPIO register bit
// will reflect the inverted value on the pin.
#define IPOLA 0x02
// Input polarity B - If a bit is set, the corresponding GPIO register bit
// will reflect the inverted value on the pin.
#define IPOLB 0x03
// The GPINTEN register controls the interrupt-onchange feature for each
// pin on port A.
#define GPINTENA 0x04
// The GPINTEN register controls the interrupt-onchange feature for each
// pin on port B.
#define GPINTENB 0x05
// Default value for port A - These bits set the compare value for pins
// configured for interrupt-on-change. If the associated pin level is the
// opposite from the register bit, an interrupt occurs.
#define DEFVALA 0x06
// Default value for port B - These bits set the compare value for pins
// configured for interrupt-on-change. If the associated pin level is the
// opposite from the register bit, an interrupt occurs.
#define DEFVALB 0x07
// Interrupt control register for port A.  If 1 interrupt is fired when the
// pin matches the default value, if 0 the interrupt is fired on state
// change
#define INTCONA 0x08
// Interrupt control register for port B.  If 1 interrupt is fired when the
// pin matches the default value, if 0 the interrupt is fired on state
// change
#define INTCONB 0x09
#define IOCON 0x0A // see datasheet for configuration register
#define GPPUA 0x0C // pull-up resistors for port A
#define GPPUB 0x0D // pull-up resistors for port B
// The INTF register reflects the interrupt condition on the port A pins of
// any pin that is enabled for interrupts. A set bit indicates that the
// associated pin caused the interrupt.
#define INTFA 0x0E
// The INTF register reflects the interrupt condition on the port B pins of
// any pin that is enabled for interrupts. A set bit indicates that the
// associated pin caused the interrupt.
#define INTFB 0x0F
// The INTCAP register captures the GPIO port A value at the time the
// interrupt occurred.
#define INTCAPA 0x10
// The INTCAP register captures the GPIO port B value at the time the
// interrupt occurred.
#define INTCAPB 0x11
#define GPIOA 0x12 // data port A
#define GPIOB 0x13 // data port B
#define OLATA 0x14 // output latches A
#define OLATB 0x15 // output latches B

using namespace ABElectronics_CPP_Libraries;

IoPi::IoPi(uint8_t address, bool initialise)
{
	/**
	* initialise the MCP32017 IO chip with default values: ports are inputs, pull-up resistors are disabled and ports are not inverted
	* @param address - I2C address for the target device
	* @param initialise - true = direction set as inputs, pull-ups disabled, ports not inverted.
                          false = device state unaltered. Defaults to true
	*/
	if (address<0x20 || address> 0x27)
	{
		throw std::out_of_range("IoPi address out of range: 0x20 to 0x27");
	}

	config = 0x02;
	i2caddress = address;
	write_byte_data(IOCON, config);

	if (initialise)
	{
		write_word_data(IODIRA, 0xFFFF);
		write_word_data(GPPUA, 0x0000);
		write_word_data(IPOLA, 0x0000);
	}
}

void IoPi::set_pin_direction(uint8_t pin, uint8_t direction)
{
	/**
	* set IO direction for an individual pin
	* @param pins - 1 to 16
	* @param direction - 1 = input, 0 = output
	*/
	set_pin(pin, direction, IODIRA, IODIRB);
}

uint8_t IoPi::get_pin_direction(uint8_t pin)
{
	/**
	* get IO direction for an individual pin
	* @param pins - 1 to 16
	*/
	return get_pin(pin, IODIRA, IODIRB);
}

void IoPi::set_port_direction(uint8_t port, uint8_t direction)
{
	/**
	* set direction for an IO port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param direction - 0 to 255 (0xFF).  For each bit 1 = input, 0 = output
	*/
	set_port(port, direction, IODIRA, IODIRB);
}

uint8_t IoPi::get_port_direction(uint8_t port)
{
	/**
	* get direction for an IO port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	*/
	return get_port(port, IODIRA, IODIRB);
}

void IoPi::set_bus_direction(uint16_t direction)
{
	/**
	* set direction for the IO bus
	* @param direction - 0 to 65535 (0xFFFF).  For each bit 1 = input, 0 = output
	*/
	write_word_data(IODIRA, direction);
}

uint16_t IoPi::get_bus_direction()
{
	/**
	* get direction for the IO bus
	*/
	return read_word_data(IODIRA);
}

void IoPi::set_pin_pullup(uint8_t pin, uint8_t value)
{
	/**
	* set the internal 100K pull-up resistors for an individual pin
	* @param pin - 1 to 16
	* @param value - 1 = enabled, 0 = disabled
	*/
	set_pin(pin, value, GPPUA, GPPUB);
}

uint8_t IoPi::get_pin_pullup(uint8_t pin)
{
	/**
	* get the internal 100K pull-up resistors for an individual pin
	* @param pin - 1 to 16
	*/

	return get_pin(pin, GPPUA, GPPUB);
}

void IoPi::set_port_pullups(uint8_t port, uint8_t value)
{
	/**
	* set the internal 100K pull-up resistors for the selected IO port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - 0 to 255 (0xFF). For each bit 1 = enabled, 0 = disabled
	*/
	set_port(port, value, GPPUA, GPPUB);
}

uint8_t IoPi::get_port_pullups(uint8_t port)
{
	/**
	* get the internal 100K pull-up resistors for the selected IO port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	*/
	return get_port(port, GPPUA, GPPUB);
}

void IoPi::set_bus_pullups(uint16_t value)
{
	/**
	* set internal 100K pull-up resistors for the IO bus
	* @param value - 0 to 65535 (0xFFFF).  For each bit 1 = enabled, 0 = disabled
	*/
	write_word_data(GPPUA, value);
}

uint16_t IoPi::get_bus_pullups()
{
	/**
	* get internal 100K pull-up resistors for the IO bus
	*/
	return read_word_data(GPPUA);
}

void IoPi::write_pin(uint8_t pin, uint8_t value)
{
	/**
	* write to an individual pin 1 - 16
	* @param pin - 1 to 16
	* @param value - 0 = logic low, 1 = logic high
	*/
	set_pin(pin, value, GPIOA, GPIOB);
}

void IoPi::write_port(uint8_t port, uint8_t value)
{
	/**
	* write to all pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - 0 to 255 (0xFF)
	*/
	set_port(port, value, GPIOA, GPIOB);
}

void IoPi::write_bus(uint16_t value)
{
	/**
	* write to all pins on the selected bus
	* @param value - 0 to 65535 (0xFFFF). For each bit 1 = logic high, 0 = logic low
	*/
	write_word_data(GPIOA, value);
}

uint8_t IoPi::read_pin(uint8_t pin)
{
	/**
	* read the value of an individual pin
	* @param pin - 1 to 16
	* @returns - 0 = logic low, 1 = logic high
	*/

	return get_pin(pin, GPIOA, GPIOB);
}

uint8_t IoPi::read_port(uint8_t port)
{
	/**
	* read all pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @returns - 0 to 255 (0xFF). For each bit 1 = logic high, 0 = logic low
	*/
	return get_port(port, GPIOA, GPIOB);
}

uint16_t IoPi::read_bus()
{
	/**
	* read all pins on the selected bus
	* @returns - 0 to 65535 (0xFFFF). For each bit 1 = logic high, 0 = logic low
	*/
	return read_word_data(GPIOA);
}

void IoPi::invert_pin(uint8_t pin, uint8_t polarity)
{
	/**
	* invert the polarity of the selected pin
	* @param pin - 1 to 16
	* @param polarity - 0 = non-inverted, 1 = inverted
	*/
	set_pin(pin, polarity, IPOLA, IPOLB);
}

uint8_t IoPi::get_pin_polarity(uint8_t pin)
{
	/**
  	* get the polarity of the selected pin
  	* @param pin - 1 to 16
  	*/
  	return get_pin(pin, IPOLA, IPOLB);
}

void IoPi::invert_port(uint8_t port, uint8_t polarity)
{
	/**
	* invert the polarity of the pins on a selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param polarity - 0 to 255 (0xFF). For each bit 0 = non-inverted, 1 = inverted
	*/
	set_port(port, polarity, IPOLA, IPOLB);
}

uint8_t IoPi::get_port_polarity(uint8_t port)
{
	/**
  	* get the polarity of the selected pin
  	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
  	*/
  	return get_port(port, IPOLA, IPOLB);
}

void IoPi::invert_bus(uint16_t polarity)
{
	/**
	* invert the polarity of the pins on a selected bus
	* @param polarity - 0 to 65535 (0xFFFF). For each bit 0 = non-inverted, 1 = inverted
	*/
	write_word_data(IPOLA, polarity);
}

 uint16_t IoPi::get_bus_polarity()
 {
	 /**
  	* get the polarity of the bus
  	*/
  	return read_word_data(IPOLA);
 }

void IoPi::mirror_interrupts(uint8_t value)
{
	/**
	* Set the interrupt pins to be mirrored or for separate ports
	* @param value - 1 = The interrupt pins are internally connected, 0 = The interrupt pins are not connected. INTA is associated with PortA and INTB is associated with PortB
	*/
	if (value == 0)
	{
		config = updatebyte(config, 6, 0);
		write_byte_data(IOCON, config);
	}
	else if (value == 1)
	{
		config = updatebyte(config, 6, 1);
		write_byte_data(IOCON, config);
	}
	else
	{
		throw std::out_of_range("mirror_interrupts value out of range: 0 or 1");
	}
}

void IoPi::set_interrupt_polarity(uint8_t value)
{
	/**
	* This sets the polarity of the interrupt output pins.
	* @param value - 1 = Active-high, 0 = Active-low.
	*/
	if (value == 0)
	{
		config = updatebyte(config, 1, 0);
		write_byte_data(IOCON, config);
	}
	else if (value == 1)
	{
		config = updatebyte(config, 1, 1);
		write_byte_data(IOCON, config);
	}
	else
	{
		throw std::out_of_range("set_interrupt_polarity value out of range: 0 or 1");
	}
}

uint8_t IoPi::get_interrupt_polarity()
{
	/**
  	* Get the polarity of the interrupt output pins.
  	*/
  	return checkbit(read_byte_data(IOCON), 1);
}

void IoPi::set_interrupt_type(uint8_t port, uint8_t value)
{
	/**
	* Sets the type of interrupt for each pin on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - 0 to 255 (0xFF). For each bit 1 = interrupt is fired when the pin matches the default value, 0 = the interrupt is fired on state change
	*/
	set_port(port, value, INTCONA, INTCONB);
}

uint8_t IoPi::get_interrupt_type(uint8_t port)
{
	/**
	* Get the type of interrupt for each pin on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	*/
	return get_port(port, INTCONA, INTCONB);
}

void IoPi::set_interrupt_defaults(uint8_t port, uint8_t value)
{
	/**
	* These bits set the compare value for pins configured for interrupt-on-change on the selected port.
	* If the associated pin level is the opposite from the register bit, an interrupt occurs.
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - default state for the port. 0 to 255 (0xFF).
	*/
	set_port(port, value, DEFVALA, DEFVALB);
}

uint8_t IoPi::get_interrupt_defaults(uint8_t port)
{
	/**
  	* Get the compare value for pins configured for interrupt-on-change on the selected port.
  	* If the associated pin level is the opposite from the register bit, an interrupt occurs.
  	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
  	*/
  	return get_port(port, DEFVALA, DEFVALB);
}

void IoPi::set_interrupt_on_pin(uint8_t pin, uint8_t value)
{
	/**
	* Enable interrupts for the selected pin
	* @param pin - 1 to 16
	* @param value - 0 = interrupt disabled, 1 = interrupt enabled
	*/
	set_pin(pin, value, GPINTENA, GPINTENB);
}

 uint8_t IoPi::get_interrupt_on_pin(uint8_t pin)
 {
	 /**
  	* Get the interrupt enable status for the selected pin
  	* @param pin - 1 to 16
  	*/
  	return get_pin(pin, GPINTENA, GPINTENB);
 }

void IoPi::set_interrupt_on_port(uint8_t port, uint8_t value)
{
	/**
	* Enable interrupts for the pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - 0 to 255 (0xFF). For each bit 0 = interrupt disabled, 1 = interrupt enabled
	*/
	set_port(port, value, GPINTENA, GPINTENB);
}

uint8_t IoPi::get_interrupt_on_port(uint8_t port)
{
	/**
  	* Get the interrupt enable status for the selected port
  	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
  	*/
  	return get_port(port, GPINTENA, GPINTENB);
}

void IoPi::set_interrupt_on_bus(uint16_t value)
{
	/**
	* Enable interrupts for the pins on the selected bus
	* @param value - 0 to 65535 (0xFFFF). For each bit 0 = interrupt disabled, 1 = interrupt enabled
	*/
	write_word_data(GPINTENA, value);
}

 uint16_t IoPi::get_interrupt_on_bus()
 {
	 /**
  	* Get the interrupt enable status for the selected bus
  	*/
  	return read_word_data(GPINTENA);
 }

uint8_t IoPi::read_interrupt_status(uint8_t port)
{
	/**
	* read the interrupt status for the pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @returns - 0 to 255 (0xFF). For each bit 1 = interrupt triggered, 0 = interrupt not triggered
	*/
	return get_port(port, INTFA, INTFB);
}

uint8_t IoPi::read_interrupt_capture(uint8_t port)
{
	/**
	* read the value from the selected port at the time of the last interrupt trigger
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @returns - 0 to 255 (0xFF). For each bit 1 = interrupt triggered, 0 = interrupt not triggered
	*/
	return get_port(port, INTCAPA, INTCAPB);
}

void IoPi::reset_interrupts()
{
	/**
	* Reset the interrupts A and B to 0
	*/
	read_interrupt_capture(0);
	read_interrupt_capture(1);
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

uint8_t IoPi::read_byte_data(uint8_t reg)
{
	/**
	* private method for reading a byte from the I2C port
	*/
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

	return (buf[0]);
}

uint16_t IoPi::read_word_data(uint8_t reg)
{
	/**
	* private method for reading a byte from the I2C port
	*/
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
}

void IoPi::write_byte_data(uint8_t reg, uint8_t value)
{
	/**
	* private method for writing a byte to the I2C port
	*/
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
}

void IoPi::write_word_data(uint8_t reg, uint16_t value)
{
	/**
	* private method for writing a byte to the I2C port
	*/
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
}

uint8_t IoPi::updatebyte(uint8_t byte, uint8_t bit, uint8_t value)
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

uint8_t IoPi::checkbit(uint8_t byte, uint8_t bit)
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

void IoPi::set_pin(uint8_t pin, uint8_t value, uint8_t a_register, uint8_t b_register)
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
	else if (pin >= 9 and pin <= 16)
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

uint8_t IoPi::get_pin(uint8_t pin, uint8_t a_register, uint8_t b_register)
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

void IoPi::set_port(uint8_t port, uint8_t value, uint8_t a_register, uint8_t b_register)
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

uint8_t IoPi::get_port(uint8_t port, uint8_t a_register, uint8_t b_register)
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

void IoPi::set_bus(uint16_t value, uint8_t a_register){
	/**
	* private method for writing a 16-bit value to two consecutive device registers
	*/
	write_word_data(a_register, value);
}
