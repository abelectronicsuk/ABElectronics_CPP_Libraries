/*
 ================================================
 ABElectronics UK IO Pi 32-Channel Port Expander
 Version 1.1 Created 23/01/2015 - Updated 27/05/2015
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


IoPi::IoPi(char address)
{
		config = 0x22;
		i2caddress = address;
	 	write_byte_data(IOCON, config);
		portaval = read_byte_data(GPIOA);
		portbval = read_byte_data(GPIOB);
		write_byte_data(IODIRA, 0xFF);
		write_byte_data(IODIRB, 0xFF);
		set_port_pullups(0, 0x00);
		set_port_pullups(1, 0x00);
		invert_port(0, 0x00);
		invert_port(1, 0x00);
}

void IoPi::set_pin_direction(char pin, char direction)
{
	/**
	* set IO direction for an individual pin
	* @param pins - 1 to 16
	* @param direction - 1 = input, 0 = output
	*/
	pin = pin - 1;
	if (pin >= 0 && pin < 8)
	{
		port_a_dir = updatebyte(port_a_dir, pin, direction);
		write_byte_data(IODIRA, port_a_dir);
	}
	else if (pin >= 8 && pin < 16)
	{
		port_b_dir = updatebyte(port_b_dir, pin - 8, direction);
		write_byte_data(IODIRB, port_b_dir);
	}
	else{
		throw std::out_of_range("set_pin_direction pin out of range: 1 to 16");
	}
}

void IoPi::set_port_direction(char port, char direction)
{	
	/**
	* set direction for an IO port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param direction - 1 = input, 0 = output
	*/
	if (port == 0)
	{
		write_byte_data(IODIRA, direction);
		port_a_dir = direction;
	}
	else if (port == 1)
	{
		write_byte_data(IODIRB, direction);
		port_b_dir = direction;
	}
	else{
		throw std::out_of_range("set_port_direction port out of range: 0 or 1");
	}
}

void IoPi::set_pin_pullup(char pin, char value)
{
	/**
	* set the internal 100K pull-up resistors for an individual pin
	* @param pin - 1 to 16
	* @param value - 1 = enabled, 0 = disabled
	*/
	pin = pin - 1;
	if (pin >= 0 && pin < 8)
	{
		porta_pullup = updatebyte(porta_pullup, pin, value);
		write_byte_data(GPPUA, porta_pullup);
	}
	else if (pin >= 8 && pin < 16)
	{
		portb_pullup = updatebyte(portb_pullup, pin - 8, value);
		write_byte_data(GPPUB, portb_pullup);
	}
	else{
		throw std::out_of_range("set_pin_pullup pin out of range: 1 to 16");
	}
	
}

void IoPi::set_port_pullups(char port, char value)
{	
	/**
	* set the internal 100K pull-up resistors for the selected IO port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - number between 0 and 255 or 0x00 and 0xFF
	*/
	if (port == 0)
	{
		porta_pullup = value;
		write_byte_data(GPPUA, value);
	}
	else if (port == 1)
	{
		portb_pullup = value;
		write_byte_data(GPPUB, value);
	}
	else{
		throw std::out_of_range("set_port_pullups port out of range: 0 or 1");
	}
}

void IoPi::write_pin(char pin, char value)
{
	/**
	* write to an individual pin 1 - 16
	* @param pin - 1 to 16
	* @param value - 0 = logic level low, 1 = logic level high
	*/
	pin = pin - 1;
	if (pin >= 0 && pin < 8)
	{
		portaval = updatebyte(portaval, pin, value);
		write_byte_data(GPIOA, portaval);
	}
	else if (pin >= 8 && pin < 16)
	{
		portbval = updatebyte(portbval, pin - 8, value);
		write_byte_data(GPIOB, portbval);
	}
	else{
		throw std::out_of_range("write_pin pin out of range: 1 to 16");
	}
}

void IoPi::write_port(char port, char value)
{	
	/**
	* write to all pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - number between 0 and 255 or 0x00 and 0xFF
	*/
	if (port == 0)
	{
	write_byte_data(GPIOA, value);
	portaval = value;
	}
	else if (port == 1)
	{
	write_byte_data(GPIOB, value);
	portbval = value;
	}
	else{
		throw std::out_of_range("write_port port out of range: 0 or 1");
	}
}

int IoPi::read_pin(char pin)
{
	/**
	* read the value of an individual pin
	* @param pin - 1 to 16
	* @returns - 0 = logic level low, 1 = logic level high
	*/
	pin = pin - 1;
	if (pin >= 0 && pin < 8)
	{
		portaval = read_byte_data(GPIOA);
		return (checkbit(portaval, pin));
	}
	else if (pin >= 8 && pin < 16)
	{
		pin = pin - 8;
		portbval = read_byte_data(GPIOB);
		return (checkbit(portbval, pin));
	}
	else{
		throw std::out_of_range("read_pin pin out of range: 1 to 16");
	}
}

char IoPi::read_port(char port)
{	
	/**
	* read all pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @returns - number between 0 and 255 or 0x00 and 0xFF
	*/
	if (port == 0)
	{
		portaval = read_byte_data(GPIOA);
		return (portaval);
	}
	else if (port == 1)
	{
		portbval = read_byte_data(GPIOB);
		return (portbval);
	}
	else{
		throw std::out_of_range("read_port port out of range: 0 or 1");
	}
}

void IoPi::invert_port(char port, char polarity)
{	
	/**
	* invert the polarity of the pins on a selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param polarity - 0 = same logic state of the input pin, 1 = inverted logic	state of the input pin
	*/
	if (port == 0)
	{
		write_byte_data(IPOLA, polarity);
		porta_polarity = polarity;
	}
	else if (port == 1)
	{
		write_byte_data(IPOLB, polarity);
		portb_polarity = polarity;
	}
	else{
		throw std::out_of_range("invert_port port out of range: 0 or 1");
	}
}

void IoPi::invert_pin(char pin, char polarity)
{
	/**
	* invert the polarity of the selected pin
	* @param pin - 1 to 16
	* @param polarity - 0 = same logic state of the input pin, 1 = inverted logic	state of the input pin
	*/
	pin = pin - 1;
	if (pin >= 0 && pin < 8)
	{

		porta_polarity = updatebyte(porta_polarity, pin, polarity);
		write_byte_data(IPOLA, porta_polarity);
	}
	else if (pin >= 8 && pin < 16)
	{
		portb_polarity = updatebyte(portb_polarity, pin - 8, polarity);
		write_byte_data(IPOLB, portb_polarity);
	}
	else{
		throw std::out_of_range("invert_pin pin out of range: 1 to 16");
	}
}

void IoPi::mirror_interrupts(char value)
{
	/**
	* Set the interrupt pins to be mirrored or for separate ports
	* @param value - 1 = The char pins are internally connected, 0 = The char pins are not connected. INTA is associated with PortA and INTB is associated with PortB
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
	else{
		throw std::out_of_range("mirror_interrupts value out of range: 0 or 1");
	}
}

void IoPi::set_interrupt_polarity(char value)
{
	/**
	* This sets the polarity of the char output pins.
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
	else{
		throw std::out_of_range("set_interrupt_polarity value out of range: 0 or 1");
	}
}

void IoPi::set_interrupt_type(char port, char value)
{
	/**
	* Sets the type of interrupt for each pin on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - 1 = interrupt is fired when the pin matches the default value, 0 = the interrupt is fired on state change
	*/
	if (port == 0)
	{
		write_byte_data(INTCONA, value);
	}
	else if (port == 1)
	{
		write_byte_data(INTCONB, value);
	}
	else{
		throw std::out_of_range("set_interrupt_type port out of range: 0 or 1");
	}
}

void IoPi::set_interrupt_defaults(char port, char value)
{
	/**
	* These bits set the compare value for pins configured for interrupt-on-change on the selected port.
	* If the associated pin level is the opposite from the register bit, an interrupt occurs.
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - default state for the port
	*/
	if (port == 0)
	{
		write_byte_data(DEFVALA, value);
	}
	else if (port == 1)
	{
		write_byte_data(DEFVALB, value);
	}
	else{
		throw std::out_of_range("set_interrupt_defaults port out of range: 0 or 1");
	}
}

void IoPi::set_interrupt_on_port(char port, char value)
{
	/**
	* Enable interrupts for the pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - number between 0 and 255 or 0x00 and 0xFF
	*/
	if (port == 0)
	{
		write_byte_data(GPINTENA, value);
		intA = value;
	}
	else if (port == 1)
	{
		write_byte_data(GPINTENB, value);
		intB = value;
	}
	else{
		throw std::out_of_range("set_interrupt_on_port port out of range: 0 or 1");
	}
}

void IoPi::set_interrupt_on_pin(char pin, char value)
{
	/**
	* Enable interrupts for the selected pin
	* @param pin - 1 to 16
	* @param value - 0 = interrupt disabled, 1 = interrupt enabled
	*/
	pin = pin - 1;
	if (pin >= 0 && pin < 8)
	{
		intA = updatebyte(intA, pin, value);
		write_byte_data(GPINTENA, intA);
	}
	else if (pin >= 8 && pin < 16)
	{
		intB = updatebyte(intB, pin - 8, value);
		write_byte_data(GPINTENB, intB);
	}
	else{
		throw std::out_of_range("set_interrupt_on_pin pin out of range: 1 to 16");
	}
}

char IoPi::read_interrupt_status(char port)
{
	/**
	* read the interrupt status for the pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	*/
	if (port == 0)
	{
		return (read_byte_data(INTFA));
	}
	else if (port == 1)
	{
		return (read_byte_data(INTFB));
	}
	else{
		throw std::out_of_range("read_interrupt_status port out of range: 0 or 1");
	}
}

char IoPi::read_interrupt_capture(char port)
{
	/**
	* read the value from the selected port at the time of the last interrupt trigger
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	*/
	if (port == 0)
	{
		return (read_byte_data(INTCAPA));
	}
	else if (port == 1)
	{
		return (read_byte_data(INTCAPB));
	}
	else{
		throw std::out_of_range("read_interrupt_capture port out of range: 0 or 1");
	}
}

void IoPi::reset_interrupts()
{
	/**
	* set the interrupts A and B to 0
	*/
	read_interrupt_capture(0);
	read_interrupt_capture(1);
}



int IoPi::read_byte_data(char reg)
{
	/**
	* private method for reading a byte from the I2C port
	*/
	if ((i2cbus = open(fileName, O_RDWR)) < 0)
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

void IoPi::write_byte_data(char reg, char value)
{
	/**
	* private method for writing a byte to the I2C port
	*/
	if ((i2cbus = open(fileName, O_RDWR)) < 0)
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

char IoPi::updatebyte(char byte, char bit, char value)
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

char IoPi::checkbit(char byte, char bit)
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
