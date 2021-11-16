/*
================================================
ABElectronics UK Expander Pi
================================================


Required package{
apt-get install libi2c-dev
*/

//#define TESTMODE /* used for unit testing, comment out when using with the Expander Pi board */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <errno.h>
#include <fcntl.h>
#include <cstring>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <linux/i2c-dev.h>
#include <time.h>
#include <unistd.h>

#include "ABE_ExpanderPi.h"

#ifdef TESTMODE
	#include "../UnitTest/testlibs.h"
    TestLibs unittest;
#endif

/* I2C Bus Definitions */

#define fileName "/dev/i2c-1" /* change to /dev/i2c-0 if you are using a revision 0002 or 0003 model B */

/* SPI Bus Definitions */
#define adcdevice "/dev/spidev0.0"
#define dacdevice "/dev/spidev0.1"

/* MCP23017 register addresses */
enum MCP23017
{
	IOADDRESS = 0x20,/* Address of the device on the I2C bus */
    IODIRA = 0x00,   /* IO direction A - 1= input 0 = output */
    IODIRB = 0x01,   /* IO direction B - 1= input 0 = output */
    IPOLA = 0x02,    /* Input polarity A */
    IPOLB = 0x03,    /* Input polarity B */
    GPINTENA = 0x04, /* Controls the interrupt-onchange on port A */
    GPINTENB = 0x05, /* Controls the interrupt-onchange on port B */
    DEFVALA = 0x06,  /* Default value for port A */
    DEFVALB = 0x07,  /* Default value for port B */
    INTCONA = 0x08,  /* Interrupt control register for port A */
    INTCONB = 0x09,  /* Interrupt control register for port B */
    IOCON = 0x0A,    /* see datasheet for configuration register */
    GPPUA = 0x0C,    /* pull-up resistors for port A */
    GPPUB = 0x0D,    /* pull-up resistors for port B */
    INTFA = 0x0E,    /* Interrupt condition on port A for any enabled pin */
    INTFB = 0x0F,    /* Interrupt condition on port B for any enabled pin */
    INTCAPA = 0x10,  /* Captures the GPIO port A value at the time the interrupt occurred */
    INTCAPB = 0x11,  /* Captures the GPIO port B value at the time the interrupt occurred */
    GPIOA = 0x12,    /* Data port A */
    GPIOB = 0x13,    /* Data port B */
    OLATA = 0x14,    /* Output latches for port A */
    OLATB = 0x15     /* Output latches for port B */
};

/* RTC Definitions */
enum DS1307
{
	RTCADDRESS = 0x68,/* Address for the RTC on the I2C bus */
	SECONDS = 0x00,   /* Register addresses for date components */
	MINUTES = 0x01,
	HOURS = 0x02,
	DAYOFWEEK = 0x03,
	DAY = 0x04,
	MONTH = 0x05,
	YEAR = 0x06,
	RTCCONTROL = 0x07 /* Control register address */
};

using namespace ABElectronics_CPP_Libraries;

/*===============================Public Methods===============================*/

ExpanderPi::ExpanderPi(bool init){ /* init = true */
	/**
	* Initialise the Expander Pi Object
	* @param init (optional) -  initialise the IO chip.
	* When the IO is initialised the pins will be set as inputs and non-inverted. Pull-ups resistors are disabled.
	*/

	/* SPI Bus Variables */
	mode = SPI_MODE_0; /* SPI_MODE_0 */
	speed = 200000; /* SPI bus speed */

	/* ADC Variables */

	adctx[0] = 0x01; /* transmit buffer for the ADC */
	adctx[1] = 0x80;
	adctx[2] = 0x00;
	adcrefvoltage = 4.096; /* reference voltage for the ADC chip. */

	/* RTC Variables */
	rtcCentury = 2000;

	/*initialise the DS1307 RTC chip with default values */
	write_byte_data(DS1307::RTCADDRESS, DS1307::RTCCONTROL, (unsigned char)0x03);

	/*initialise the MCP32017 IO chip with default values: ports are inputs, pull-up resistors are disabled and ports are not inverted */
	write_byte_data(MCP23017::IOADDRESS, IOCON, (unsigned char)0x02);

	if (init){
		write_byte_data(MCP23017::IOADDRESS, IODIRA, (unsigned char)0xFF);
		write_byte_data(MCP23017::IOADDRESS, IODIRB, (unsigned char)0xFF);
		io_set_port_pullups(0, 0x00);
		io_set_port_pullups(1, 0x00);
		io_invert_port(0, 0x00);
		io_invert_port(1, 0x00);
	}
}

/*===================ADC Methods Begin ===================*/

int ExpanderPi::adc_open() {
	/**
	* Open the ADC SPI bus channel
	* This needs to be called before using the DAC
	*/

	/* Open SPI device */
	if ((adc = open(adcdevice, O_RDWR)) < 0)
		return (0);

	if (ioctl(adc, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1)
		return (0);
	/* Set SPI mode */
	if (ioctl(adc, SPI_IOC_WR_MODE, &mode) == -1)
		return (0);

	return (1);
}

void ExpanderPi::adc_close() {
	/**
	* Close the ADC SPI bus channel
	*/
	close(adc);
}

double ExpanderPi::adc_read_voltage(int channel, int mode) {
	/**
	* Read the voltage from the ADC
	* @param channel - 1 or 2
	* @param mode - 0 = Single Ended or 1 = Differential
	* @returns between 0V and the reference voltage
	*/
	int rawval = adc_read_raw(channel, mode);
	return ((adcrefvoltage / 4096) * (double)rawval);
}

int ExpanderPi::adc_read_raw(int channel, int mode) {
	/**
	* Read the raw value from the ADC
	* @param channel -  1 to 8
	* @param mode -  0 = Single Ended or 1 = Differential
	* When in differential mode setting channel to 1 will make IN1 = IN+ and IN2 = IN-
	* When in differential mode setting channel to 2 will make IN1 = IN- and IN2 = IN+
	* @returns 12 bit value between 0 and 4096
	*/

	channel = channel - 1;
	if (mode == 0) {
		adctx[0] = 6 + (channel >> 2);
		adctx[1] = (channel & 3) << 6;
	}
	else if (mode == 1) {
		adctx[0] = 4 + (channel >> 2);
		adctx[1] = (channel & 3) << 6;
	}
	else {
		return (0);
	}

	struct spi_ioc_transfer spi;
	memset(&spi,0,sizeof(spi));

	spi.tx_buf = (unsigned long)adctx;
	spi.rx_buf = (unsigned long)adcrx;
	spi.len = 3;
	spi.speed_hz = 1800000; /* 1.8MHz Clock Speed */
	spi.delay_usecs = 0;
	spi.bits_per_word = 8;


	if (ioctl(adc, SPI_IOC_MESSAGE(1), &spi) == -1){
		return(0);
	}
	else{
		return (((adcrx[1] & 0x0F) << 8) + (adcrx[2]));
	}
}

void ExpanderPi::adc_set_refvoltage(double ref) {
	/**
	* Set the reference voltage for the adc
	* @param ref - Set this value to be the same as the voltage measured on the Vref pin on the Expander Pi
	* If using the on board voltage reference then the value will be 4.096
	*/
	adcrefvoltage = ref;
}

/*===================ADC Methods END ===================*/

/*===================DAC Methods Begin ===================*/

int ExpanderPi::dac_open() {
	/**
	* Open the DAC SPI bus channel
	* This needs to be called before using the DAC
	*/

	/* Open SPI device */
	if ((dac = open(dacdevice, O_RDWR)) < 0)
		return (0);

	if (ioctl(dac, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1)
		return (0);
	/* Set SPI mode */
	if (ioctl(dac, SPI_IOC_WR_MODE, &mode) == -1)
		return (0);

	return (1);
}

void ExpanderPi::dac_close() {
	/**
	* Close the DAC SPI bus channel
	*/
	close(dac);
}

void ExpanderPi::dac_set_raw(uint16_t raw, int channel, int gain) {
	/**
	* Set the raw value from the selected channel on the DAC
	* @param raw - between 0 and 4095
	* @param channel - 1 or 2
	* @param gain - 1 or 2  - The output voltage will be between 0 and 2.048V when gain is set to 1,  0 and 4.096V when gain is set to 2
	*/

	uint8_t dactx[2];

	dactx[1] = (raw & 0xff);

	if (gain == 1) {
		dactx[0] = (((raw >> 8) & 0xff) | (channel - 1) << 7 | 1 << 5 | 1 << 4);
    }
	else if (gain == 2) {
		dactx[0] = (((raw >> 8) & 0xff) | (channel - 1) << 7 | 1 << 4);
	}
	else {
		throw std::out_of_range("dac_set_raw gain out of range: 1 or 2");
	}

	struct spi_ioc_transfer tr;
    memset(&tr,0,sizeof(tr));

	tr.tx_buf = (unsigned long)&dactx;
	tr.rx_buf = (unsigned long)NULL;
	tr.len = 2;
	tr.speed_hz = 20000000; /* 20MHz clock speed */
	tr.delay_usecs = 0;
	tr.bits_per_word = 8;
	tr.cs_change = 0;

	/* Write data */
	if (ioctl(dac, SPI_IOC_MESSAGE(1), &tr) == -1){
		throw std::runtime_error("error setting dac raw value");
	}

	return;
}

void ExpanderPi::dac_set_voltage(double voltage, int channel, int gain) {
	/**
	* Set the DAC voltage
	* @param voltage - between 0 and 2.047 when gain is set to 1,  0 and 4.096 when gain is set to 2
	* @param channel - 1 or 2
	* @param gain - 1 or 2
	*/
	double dacvoltage = 2.048;

	if (gain == 2) {
		dacvoltage = 4.096;
	}

	if ((voltage >= 0.0) && (voltage < dacvoltage)) {
		uint16_t rawval = (voltage / 2.048) * 4096 / gain;
		dac_set_raw(rawval, channel, gain);
	}
	else {
		throw std::out_of_range("dac_set_voltage voltage out of range");
	}
}


/*===================DAC Methods END ===================*/

/*===================IO Methods Begin ===================*/

void ExpanderPi::io_set_pin_direction(uint8_t pin, uint8_t direction)
{
	/**
	* set IO direction for an individual pin
	* @param pins - 1 to 16
	* @param direction - 1 = input, 0 = output
	*/
	set_pin(pin, direction, MCP23017::IODIRA, MCP23017::IODIRB);
}

uint8_t ExpanderPi::io_get_pin_direction(uint8_t pin)
{
	/**
	* get IO direction for an individual pin
	* @param pins - 1 to 16
	*/
	return get_pin(pin, MCP23017::IODIRA, MCP23017::IODIRB);
}

void ExpanderPi::io_set_port_direction(uint8_t port, uint8_t direction)
{
	/**
	* set direction for an IO port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param direction - 0 to 255 (0xFF).  For each bit 1 = input, 0 = output
	*/
	set_port(port, direction, MCP23017::IODIRA, MCP23017::IODIRB);
}

uint8_t ExpanderPi::io_get_port_direction(uint8_t port)
{
	/**
	* get direction for an IO port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	*/
	return get_port(port, MCP23017::IODIRA, MCP23017::IODIRB);
}

void ExpanderPi::io_set_bus_direction(uint16_t direction)
{
	/**
	* set direction for the IO bus
	* @param direction - 0 to 65535 (0xFFFF).  For each bit 1 = input, 0 = output
	*/
	write_word_data(MCP23017::IOADDRESS, MCP23017::IODIRA, direction);
}

uint16_t ExpanderPi::io_get_bus_direction()
{
	/**
	* get direction for the IO bus
	*/
	return read_word_data(MCP23017::IOADDRESS, MCP23017::IODIRA);
}

void ExpanderPi::io_set_pin_pullup(uint8_t pin, uint8_t value)
{
	/**
	* set the internal 100K pull-up resistors for an individual pin
	* @param pin - 1 to 16
	* @param value - 1 = enabled, 0 = disabled
	*/
	set_pin(pin, value, MCP23017::GPPUA, MCP23017::GPPUB);
}

uint8_t ExpanderPi::io_get_pin_pullup(uint8_t pin)
{
	/**
	* get the internal 100K pull-up resistors for an individual pin
	* @param pin - 1 to 16
	*/

	return get_pin(pin, MCP23017::GPPUA, MCP23017::GPPUB);
}

void ExpanderPi::io_set_port_pullups(uint8_t port, uint8_t value)
{
	/**
	* set the internal 100K pull-up resistors for the selected IO port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - 0 to 255 (0xFF). For each bit 1 = enabled, 0 = disabled
	*/
	set_port(port, value, MCP23017::GPPUA, MCP23017::GPPUB);
}

uint8_t ExpanderPi::io_get_port_pullups(uint8_t port)
{
	/**
	* get the internal 100K pull-up resistors for the selected IO port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	*/
	return get_port(port, MCP23017::GPPUA, MCP23017::GPPUB);
}

void ExpanderPi::io_set_bus_pullups(uint16_t value)
{
	/**
	* set internal 100K pull-up resistors for the IO bus
	* @param value - 0 to 65535 (0xFFFF).  For each bit 1 = enabled, 0 = disabled
	*/
	write_word_data(MCP23017::IOADDRESS, MCP23017::GPPUA, value);
}

uint16_t ExpanderPi::io_get_bus_pullups()
{
	/**
	* get internal 100K pull-up resistors for the IO bus
	*/
	return read_word_data(MCP23017::IOADDRESS, MCP23017::GPPUA);
}

void ExpanderPi::io_write_pin(uint8_t pin, uint8_t value)
{
	/**
	* write to an individual pin 1 - 16
	* @param pin - 1 to 16
	* @param value - 0 = logic low, 1 = logic high
	*/
	set_pin(pin, value, MCP23017::GPIOA, MCP23017::GPIOB);
}

void ExpanderPi::io_write_port(uint8_t port, uint8_t value)
{
	/**
	* write to all pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - 0 to 255 (0xFF)
	*/
	set_port(port, value, MCP23017::GPIOA, MCP23017::GPIOB);
}

void ExpanderPi::io_write_bus(uint16_t value)
{
	/**
	* write to all pins on the selected bus
	* @param value - 0 to 65535 (0xFFFF). For each bit 1 = logic high, 0 = logic low
	*/
	write_word_data(MCP23017::IOADDRESS, MCP23017::GPIOA, value);
}

uint8_t ExpanderPi::io_read_pin(uint8_t pin)
{
	/**
	* read the value of an individual pin
	* @param pin - 1 to 16
	* @returns - 0 = logic low, 1 = logic high
	*/

	return get_pin(pin, MCP23017::GPIOA, MCP23017::GPIOB);
}

uint8_t ExpanderPi::io_read_port(uint8_t port)
{
	/**
	* read all pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @returns - 0 to 255 (0xFF). For each bit 1 = logic high, 0 = logic low
	*/
	return get_port(port, MCP23017::GPIOA, MCP23017::GPIOB);
}

uint16_t ExpanderPi::io_read_bus()
{
	/**
	* read all pins on the selected bus
	* @returns - 0 to 65535 (0xFFFF). For each bit 1 = logic high, 0 = logic low
	*/
	return read_word_data(MCP23017::IOADDRESS, MCP23017::GPIOA);
}

void ExpanderPi::io_invert_pin(uint8_t pin, uint8_t polarity)
{
	/**
	* invert the polarity of the selected pin
	* @param pin - 1 to 16
	* @param polarity - 0 = non-inverted, 1 = inverted
	*/
	set_pin(pin, polarity, MCP23017::IPOLA, MCP23017::IPOLB);
}

uint8_t ExpanderPi::io_get_pin_polarity(uint8_t pin)
{
	/**
  	* get the polarity of the selected pin
  	* @param pin - 1 to 16
  	*/
  	return get_pin(pin, MCP23017::IPOLA, MCP23017::IPOLB);
}

void ExpanderPi::io_invert_port(uint8_t port, uint8_t polarity)
{
	/**
	* invert the polarity of the pins on a selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param polarity - 0 to 255 (0xFF). For each bit 0 = non-inverted, 1 = inverted
	*/
	set_port(port, polarity, MCP23017::IPOLA, MCP23017::IPOLB);
}

uint8_t ExpanderPi::io_get_port_polarity(uint8_t port)
{
	/**
  	* get the polarity of the selected pin
  	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
  	*/
  	return get_port(port, MCP23017::IPOLA, MCP23017::IPOLB);
}

void ExpanderPi::io_invert_bus(uint16_t polarity)
{
	/**
	* invert the polarity of the pins on a selected bus
	* @param polarity - 0 to 65535 (0xFFFF). For each bit 0 = non-inverted, 1 = inverted
	*/
	write_word_data(MCP23017::IOADDRESS, MCP23017::IPOLA, polarity);
}

 uint16_t ExpanderPi::io_get_bus_polarity()
 {
	 /**
  	* get the polarity of the bus
  	*/
  	return read_word_data(MCP23017::IOADDRESS, MCP23017::IPOLA);
 }

void ExpanderPi::io_mirror_interrupts(uint8_t value)
{
	/**
	* Set the interrupt pins to be mirrored or for separate ports
	* @param value - 1 = The interrupt pins are internally connected, 0 = The interrupt pins are not connected. INTA is associated with PortA and INTB is associated with PortB
	*/
    uint8_t ioconfig =  read_byte_data(MCP23017::IOADDRESS, MCP23017::IOCON);

	if (value == 0)
	{        
		ioconfig = updatebyte(ioconfig, 6, 0);
		write_byte_data(MCP23017::IOADDRESS, MCP23017::IOCON, ioconfig);
	}
	else if (value == 1)
	{
		ioconfig = updatebyte(ioconfig, 6, 1);
		write_byte_data(MCP23017::IOADDRESS, MCP23017::IOCON, ioconfig);
	}
	else
	{
		throw std::out_of_range("mirror_interrupts value out of range: 0 or 1");
	}
}

void ExpanderPi::io_set_interrupt_polarity(uint8_t value)
{
	/**
	* This sets the polarity of the interrupt output pins.
	* @param value - 1 = Active-high, 0 = Active-low.
	*/
    uint8_t ioconfig =  read_byte_data(MCP23017::IOADDRESS, MCP23017::IOCON);
    
	if (value == 0)
	{
		ioconfig = updatebyte(ioconfig, 1, 0);
		write_byte_data(MCP23017::IOADDRESS, MCP23017::IOCON, ioconfig);
	}
	else if (value == 1)
	{
		ioconfig = updatebyte(ioconfig, 1, 1);
		write_byte_data(MCP23017::IOADDRESS, MCP23017::IOCON, ioconfig);
	}
	else
	{
		throw std::out_of_range("set_interrupt_polarity value out of range: 0 or 1");
	}
}

uint8_t ExpanderPi::io_get_interrupt_polarity()
{
	/**
  	* Get the polarity of the interrupt output pins.
  	*/
  	return checkbit(read_byte_data(MCP23017::IOADDRESS, MCP23017::IOCON), 1);
}

void ExpanderPi::io_set_interrupt_type(uint8_t port, uint8_t value)
{
	/**
	* Sets the type of interrupt for each pin on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - 0 to 255 (0xFF). For each bit 1 = interrupt is fired when the pin matches the default value, 0 = the interrupt is fired on state change
	*/
	set_port(port, value, MCP23017::INTCONA, MCP23017::INTCONB);
}

uint8_t ExpanderPi::io_get_interrupt_type(uint8_t port)
{
	/**
	* Get the type of interrupt for each pin on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	*/
	return get_port(port, MCP23017::INTCONA, MCP23017::INTCONB);
}

void ExpanderPi::io_set_interrupt_defaults(uint8_t port, uint8_t value)
{
	/**
	* These bits set the compare value for pins configured for interrupt-on-change on the selected port.
	* If the associated pin level is the opposite from the register bit, an interrupt occurs.
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - default state for the port. 0 to 255 (0xFF).
	*/
	set_port(port, value, MCP23017::DEFVALA, MCP23017::DEFVALB);
}

uint8_t ExpanderPi::io_get_interrupt_defaults(uint8_t port)
{
	/**
  	* Get the compare value for pins configured for interrupt-on-change on the selected port.
  	* If the associated pin level is the opposite from the register bit, an interrupt occurs.
  	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
  	*/
  	return get_port(port, MCP23017::DEFVALA, MCP23017::DEFVALB);
}

void ExpanderPi::io_set_interrupt_on_pin(uint8_t pin, uint8_t value)
{
	/**
	* Enable interrupts for the selected pin
	* @param pin - 1 to 16
	* @param value - 0 = interrupt disabled, 1 = interrupt enabled
	*/
	set_pin(pin, value, MCP23017::GPINTENA, MCP23017::GPINTENB);
}

 uint8_t ExpanderPi::io_get_interrupt_on_pin(uint8_t pin)
 {
	 /**
  	* Get the interrupt enable status for the selected pin
  	* @param pin - 1 to 16
  	*/
  	return get_pin(pin, MCP23017::GPINTENA, MCP23017::GPINTENB);
 }

void ExpanderPi::io_set_interrupt_on_port(uint8_t port, uint8_t value)
{
	/**
	* Enable interrupts for the pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - 0 to 255 (0xFF). For each bit 0 = interrupt disabled, 1 = interrupt enabled
	*/
	set_port(port, value, MCP23017::GPINTENA, MCP23017::GPINTENB);
}

uint8_t ExpanderPi::io_get_interrupt_on_port(uint8_t port)
{
	/**
  	* Get the interrupt enable status for the selected port
  	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
  	*/
  	return get_port(port, MCP23017::GPINTENA, MCP23017::GPINTENB);
}

void ExpanderPi::io_set_interrupt_on_bus(uint16_t value)
{
	/**
	* Enable interrupts for the pins on the selected bus
	* @param value - 0 to 65535 (0xFFFF). For each bit 0 = interrupt disabled, 1 = interrupt enabled
	*/
	write_word_data(MCP23017::IOADDRESS, MCP23017::GPINTENA, value);
}

 uint16_t ExpanderPi::io_get_interrupt_on_bus()
 {
	 /**
  	* Get the interrupt enable status for the selected bus
  	*/
  	return read_word_data(MCP23017::IOADDRESS, MCP23017::GPINTENA);
 }

uint8_t ExpanderPi::io_read_interrupt_status(uint8_t port)
{
	/**
	* read the interrupt status for the pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @returns - 0 to 255 (0xFF). For each bit 1 = interrupt triggered, 0 = interrupt not triggered
	*/
	return get_port(port, MCP23017::INTFA, MCP23017::INTFB);
}

uint8_t ExpanderPi::io_read_interrupt_capture(uint8_t port)
{
	/**
	* read the value from the selected port at the time of the last interrupt trigger
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @returns - 0 to 255 (0xFF). For each bit 1 = interrupt triggered, 0 = interrupt not triggered
	*/
	return get_port(port, MCP23017::INTCAPA, MCP23017::INTCAPB);
}

void ExpanderPi::io_reset_interrupts()
{
	/**
	* Reset the interrupts A and B to 0
	*/
	io_read_interrupt_capture(0);
	io_read_interrupt_capture(1);
}

/*===================IO Methods END ===================*/

/*===================RTC Methods Begin ===================*/


void ExpanderPi::rtc_set_date(struct tm date) {
	/**
	* Set the date on the RTC
	* @param date - struct tm formated date and time
	*/
	writebuffer[0] = DS1307::SECONDS;                /* register address for seconds */
	writebuffer[1] = dec_to_bcd(date.tm_sec);        /* seconds */
	writebuffer[2] = dec_to_bcd(date.tm_min);        /* minutes */
	writebuffer[3] = dec_to_bcd(date.tm_hour);       /* hours */
	writebuffer[4] = dec_to_bcd(date.tm_wday);       /* dayofweek */
	writebuffer[5] = dec_to_bcd(date.tm_mday);	     /* day */
	writebuffer[6] = dec_to_bcd(date.tm_mon) + 1;	 /* month */
	writebuffer[7] = dec_to_bcd(date.tm_year % 100); /* strip the century from the date */

	write_byte_array(DS1307::RTCADDRESS, writebuffer, 8);
}

struct tm ExpanderPi::rtc_read_date() {
	/**
	* Read the date from the RTC.
	* @returns - date as a tm struct
	*/

	read_byte_array(DS1307::RTCADDRESS, 0, 7);
	struct tm date;
	date.tm_sec = bcd_to_dec(readbuffer[0]);       /* seconds */
	date.tm_min = bcd_to_dec(readbuffer[1]);       /* minutes */
	date.tm_hour = bcd_to_dec(readbuffer[2]);      /* hours */
	date.tm_wday = bcd_to_dec(readbuffer[3]);      /* dayofweek */
	date.tm_mday = bcd_to_dec(readbuffer[4]);      /* day */
	date.tm_mon = bcd_to_dec(readbuffer[5]) - 1;   /* month */
	date.tm_year = bcd_to_dec(readbuffer[6]) + (rtcCentury - 1900); /* year */

	return date;
}

void ExpanderPi::rtc_enable_output() {
	/**
	* Enable the squarewave output pin
	*/
	uint8_t rtcconfig = read_byte_data(DS1307::RTCADDRESS, DS1307::RTCCONTROL);
	rtcconfig = updatebyte(rtcconfig, 7, 1);
	rtcconfig = updatebyte(rtcconfig, 4, 1);
	write_byte_data(DS1307::RTCADDRESS, DS1307::RTCCONTROL, rtcconfig);
}

void ExpanderPi::rtc_disable_output() {
	/**
	* Disable the squarewave output pin
	*/
	uint8_t rtcconfig = read_byte_data(DS1307::RTCADDRESS, DS1307::RTCCONTROL);
	rtcconfig = updatebyte(rtcconfig, 7, 0);
	rtcconfig = updatebyte(rtcconfig, 4, 0);
	write_byte_data(DS1307::RTCADDRESS, DS1307::RTCCONTROL, rtcconfig);
}

void ExpanderPi::rtc_set_frequency(unsigned char frequency) {
	/**
	* Set the squarewave output frequency
	* @param - 1 = 1Hz, 2 = 4.096KHz, 3 = 8.192KHz, 4 = 32.768KHz
	*/
    uint8_t rtcconfig = read_byte_data(DS1307::RTCADDRESS, DS1307::RTCCONTROL);

	switch (frequency) {
		case 1:
			rtcconfig = updatebyte(rtcconfig, 0, 0);
			rtcconfig = updatebyte(rtcconfig, 1, 0);
			write_byte_data(DS1307::RTCADDRESS, DS1307::RTCCONTROL, rtcconfig);
			break;
		case 2:
			rtcconfig = updatebyte(rtcconfig, 0, 1);
			rtcconfig = updatebyte(rtcconfig, 1, 0);
			write_byte_data(DS1307::RTCADDRESS, DS1307::RTCCONTROL, rtcconfig);
			break;
		case 3:
			rtcconfig = updatebyte(rtcconfig, 0, 0);
			rtcconfig = updatebyte(rtcconfig, 1, 1);
			write_byte_data(DS1307::RTCADDRESS, DS1307::RTCCONTROL, rtcconfig);
			break;
		case 4:
			rtcconfig = updatebyte(rtcconfig, 0, 1);
			rtcconfig = updatebyte(rtcconfig, 1, 1);
			write_byte_data(DS1307::RTCADDRESS, DS1307::RTCCONTROL, rtcconfig);
			break;
		default:
			throw std::out_of_range("Error: rtc_set_frequency() - value must be between 1 and 4");
	}
}

void ExpanderPi::rtc_write_memory(uint8_t address, uint8_t *valuearray, uint8_t length) {
	/**
	* write to the memory on the ds1307
	* the ds1307 contains 56 - Byte, battery - backed RAM with Unlimited Writes
	* @param address - 0x08 to 0x3F
	* @param valuearray - byte array containing data to be written to memory
	*/

	if (address >= 0x08 && address <= 0x3F) {
		if (address <= (0x3F - (length - 1))) {
			
			uint8_t *writearray = (uint8_t*)malloc(length + 1);

			if (errno == ENOMEM) { /* Fail!!!! */
				free(writearray);
				throw std::runtime_error("memory allocation error: not enough system memory to allocate array");
			}
			else {

				writearray[0] = address;

				int a;
				for (a = 0; a < length; a++) {
					writearray[a + 1] = valuearray[a];
				}
				
				write_byte_array(DS1307::RTCADDRESS, writearray, length);
				
				free(writearray);
			}

		}
		else {
			throw std::runtime_error("memory overflow error: address + length exceeds 0x3F");
		}
	}
	else{
		throw std::out_of_range("address out of range");
	}
}

uint8_t *ExpanderPi::rtc_read_memory(uint8_t address, uint8_t length) {
	/**
	* read from the memory on the ds1307
	* the ds1307 contains 56-Byte, battery-backed RAM with Unlimited Writes
	* @param address - 0x08 to 0x3F
	* @param length - up to 56 bytes.  length can not exceed the avaiable address space.
	* @returns - pointer to a byte array where the data will be saved
	*/

    if (length < 1 || length > 56){
        throw std::runtime_error("length outside of range 1 to 56");
    }

	if (address >= 0x08 && address <= 0x3F) {
		if (address <= (0x3F - (length - 1))) {

			uint8_t *writearray = (uint8_t*)malloc(length);

			if (errno == ENOMEM) { /* Fail!!!! */
				free(writearray);
				throw std::runtime_error("memory allocation error: not enough system memory to allocate array");
				return NULL;
			}
			else {
				read_byte_array(DS1307::RTCADDRESS, address, length); /* read the values from the SRAM into the read buffer */

				/* copy the read buffer into the writearray */
				int i = 0;
				for (i = 0; i < length; i++) {
					writearray[i] = readbuffer[i];
				}

				return writearray;
			}

		}
		else {
			throw std::runtime_error("memory overflow error: address + length exceeds 0x3F");
			return NULL;
		}
	}
	else {
		throw std::out_of_range("address out of range");
		return NULL;
	}		
}

/*===================RTC Methods End ===================*/


/*===================Private Methods===================*/

class ScopedFileHandle{
	/* stops file handle leakage on exceptions */
public:
    ScopedFileHandle(int fd) :_fd(fd){}
    ~ScopedFileHandle(){ if(_fd >= 0) close(_fd); }
    operator int() const { return _fd; }
private:
    int _fd;
};

uint8_t ExpanderPi::bcd_to_dec(uint8_t bcd) {
	/*
	private method for converting a bcd formatted number to decimal
	*/
	return (uint8_t)(((bcd >> 4) & 0x0F) * 10) + ((bcd & 0x0F));
}

uint8_t ExpanderPi::dec_to_bcd(uint8_t dec) {
	/*
	private method for converting a decimal formatted number to bcd
	*/
	return (uint8_t)((dec / 10) * 16) + (dec % 10);
}

uint8_t ExpanderPi::read_byte_data(uint8_t address, uint8_t reg)
{
	/**
	* private method for reading a byte from the I2C port
	*/
	#ifdef TESTMODE
		address++;  /* suppresses parameter set but not used warning */
		buf[0] = unittest.i2c_emulator_read_byte_data(reg);
	#else

	ScopedFileHandle i2cbus(open(fileName, O_RDWR));
	if (i2cbus < 0)
	{
		throw std::runtime_error("Failed to open i2c port for read");
	}

	if (ioctl(i2cbus, I2C_SLAVE, address) < 0)
	{
		throw std::runtime_error("Failed to write to i2c port for read");
	}

	buf[0] = reg;

	if ((write(i2cbus, buf, 1)) != 1)
	{
		throw std::runtime_error("Failed to write to i2c device for read");
	}

	if (read(i2cbus, buf, 1) != 1)
	{ /* Read back data into buf[] */
		throw std::runtime_error("Failed to read from slave");
	}

	close(i2cbus);

	#endif

	return (buf[0]);
}

uint16_t ExpanderPi::read_word_data(uint8_t address, uint8_t reg)
{
	/**
	* private method for reading a byte from the I2C port
	*/
	#ifdef TESTMODE
		address++;  /* suppresses parameter set but not used warning */
		return (unittest.i2c_emulator_read_word_data(reg));
	#else

	ScopedFileHandle i2cbus(open(fileName, O_RDWR));
	if (i2cbus < 0)
	{
		throw std::runtime_error("Failed to open i2c port for read");
	}

	if (ioctl(i2cbus, I2C_SLAVE, address) < 0)
	{
		throw std::runtime_error("Failed to write to i2c port for read");
	}

	buf[0] = reg;

	if ((write(i2cbus, buf, 1)) != 1)
	{
		throw std::runtime_error("Failed to write to i2c device for read");
	}

	if (read(i2cbus, buf, 2) != 2)
	{ /* Read back data into buf[] */
		throw std::runtime_error("Failed to read from slave");
	}

	close(i2cbus);

	uint16_t value = (buf[1] << 8) | buf[0];
	return (value);

	#endif
}

void ExpanderPi::read_byte_array(uint8_t address, uint8_t reg, uint8_t length) {
	/*
	private method for reading an array of bytes from the I2C port
	*/

    #ifdef TESTMODE
		TestLibs test;
		address++;  /* suppresses parameter set but not used warning */
        if (length > 1){
            for (uint8_t i = 0; i <= length; i++){
                readbuffer[i] = test.i2c_emulator_read_byte_data(reg + i);
            }
        }		
	#else

	ScopedFileHandle i2cbus(open(fileName, O_RDWR));
    if (i2cbus < 0)
	{
		throw std::runtime_error("read_byte_array: Failed to open i2c port for read");
	}

	if (ioctl(i2cbus, I2C_SLAVE, address) < 0)
	{
		throw std::runtime_error("read_byte_array: Failed to write to i2c port for read");
	}

	buf[0] = reg;

	if ((write(i2cbus, buf, 1)) != 1)
	{
		throw std::runtime_error("read_byte_array: Failed to write to i2c device for read");
	}

	read(i2cbus, readbuffer, length);

	close(i2cbus);

    #endif
}

void ExpanderPi::write_byte_data(uint8_t address, uint8_t reg, uint8_t value)
{
	/**
	* private method for writing a byte to the I2C port
	*/
	#ifdef TESTMODE
		address++;  /* suppresses parameter set but not used warning */
		unittest.i2c_emulator_write_byte_data(reg, value);
	#else

	ScopedFileHandle i2cbus(open(fileName, O_RDWR));
	if (i2cbus < 0)
	{
		throw std::runtime_error("Failed to open i2c port for write");
	}

	if (ioctl(i2cbus, I2C_SLAVE, address) < 0)
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

void ExpanderPi::write_word_data(uint8_t address, uint8_t reg, uint16_t value)
{
	/**
	* private method for writing a byte to the I2C port
	*/
	#ifdef TESTMODE
		address++;  /* suppresses parameter set but not used warning */
		unittest.i2c_emulator_write_word_data(reg, value);
	#else

	ScopedFileHandle i2cbus(open(fileName, O_RDWR));
	if (i2cbus < 0)
	{
		throw std::runtime_error("Failed to open i2c port for write");
	}

	if (ioctl(i2cbus, I2C_SLAVE, address) < 0)
	{
		throw std::runtime_error("Failed to write to i2c port for write");
	}


	buf[0] = reg;
	buf[1] = (uint8_t)(value&(0xff)); /* lower 8 bits */
	buf[2] = (uint8_t)(value>>8) & 0xff; /* upper 8 bits */

	if ((write(i2cbus, buf, 3)) != 3)
	{
		throw std::runtime_error("Failed to write to i2c device for write");
	}

	close(i2cbus);

	#endif
}

void ExpanderPi::write_byte_array(uint8_t address, uint8_t buffer[], uint8_t length) {
	/*
	private method for writing an array of bytes to the I2C port
	*/

    #ifdef TESTMODE
		TestLibs test;
		address++;  /* suppresses parameter set but not used warning */
        uint8_t regaddress = buffer[0];
        if (length > 1){
            for (uint8_t i = 1; i <= length; i++){
                test.i2c_emulator_write_byte_data(regaddress + (i-1), buffer[i]);
            }
        }		
	#else

	ScopedFileHandle i2cbus(open(fileName, O_RDWR));
    if (i2cbus < 0)
	{
		throw std::runtime_error("write_byte_array: Failed to open i2c port for write");
	}

	if (ioctl(i2cbus, I2C_SLAVE, address) < 0)
	{
		throw std::runtime_error("write_byte_array: Failed to write to i2c port for write");
	}

	if ((write(i2cbus, buffer, length)) != length) {
		throw std::runtime_error("write_byte_array: Failed to write to i2c device for write");
		exit(1);
	}

	close(i2cbus);

    #endif
}

uint8_t ExpanderPi::updatebyte(uint8_t byte, uint8_t bit, uint8_t value)
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

uint8_t ExpanderPi::checkbit(uint8_t byte, uint8_t bit)
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

void ExpanderPi::set_pin(uint8_t pin, uint8_t value, uint8_t a_register, uint8_t b_register)
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

	uint8_t newval = updatebyte(read_byte_data(MCP23017::IOADDRESS, reg), p, value);
	write_byte_data(MCP23017::IOADDRESS, reg, newval);
}

uint8_t ExpanderPi::get_pin(uint8_t pin, uint8_t a_register, uint8_t b_register)
{
	/**
	* private method for getting the value of a single bit within the device registers
	*/

		uint8_t value = 0;

        if (pin >= 1 && pin <= 8)
		{
            value = checkbit(read_byte_data(MCP23017::IOADDRESS, a_register), pin - 1);
		}
        else if (pin >= 9 && pin <= 16)
		{
            value = checkbit(read_byte_data(MCP23017::IOADDRESS, b_register), pin - 9);
		}
        else
		{
            throw std::out_of_range("pin out of range: 1 to 16");
		}

        return value;
}

void ExpanderPi::set_port(uint8_t port, uint8_t value, uint8_t a_register, uint8_t b_register)
{
	/**
	* private method for setting the value of a device register
	*/
	if (port == 0)
	{
    	write_byte_data(MCP23017::IOADDRESS, a_register, value);
	}
    else if (port == 1)
	{
    	write_byte_data(MCP23017::IOADDRESS, b_register, value);
	}
	else
	{
		throw std::out_of_range("port out of range: 0 or 1");
	}
}

uint8_t ExpanderPi::get_port(uint8_t port, uint8_t a_register, uint8_t b_register)
{
	/**
	* private method for getting the value of a device register
	*/
	if (port == 0)
	{
    	return read_byte_data(MCP23017::IOADDRESS, a_register);
	}
    else if (port == 1)
	{
    	return read_byte_data(MCP23017::IOADDRESS, b_register);
	}
	else
	{
		throw std::out_of_range("port out of range: 0 or 1");
	}
}

void ExpanderPi::set_bus(uint16_t value, uint8_t a_register){
	/**
	* private method for writing a 16-bit value to two consecutive device registers
	*/
	write_word_data(MCP23017::IOADDRESS, a_register, value);
}