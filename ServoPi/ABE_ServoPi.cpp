/*
 ================================================
 ABElectronics UK Servo Pi 16-Channel PWM Servo Controller
 Version 1.1 Updated 21/04/2020
 ================================================


 Required packages: i2c-dev and wiringPi
 apt-get install libi2c-dev wiringpi
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <errno.h>
#include <fcntl.h>
#include <cstring>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/i2c-dev.h>
#include <math.h>
#include <unistd.h>
#include <wiringPi.h>

#include "ABE_ServoPi.h"

using namespace ABElectronics_CPP_Libraries;

#define fileName "/dev/i2c-1"
// change to /dev/i2c-0 if you are using a revision 0002 or 0003 model B

// Define registers values from datasheet
#define MODE1 0x00
#define MODE2 0x01
#define SUBADR1 0x02
#define SUBADR2 0x03
#define SUBADR3 0x04
#define ALLCALLADR 0x05
#define LED0_ON_L 0x06
#define LED0_ON_H 0x07
#define LED0_OFF_L 0x08
#define LED0_OFF_H 0x09
#define ALL_LED_ON_L 0xFA
#define ALL_LED_ON_H 0xFB
#define ALL_LED_OFF_L 0xFC
#define ALL_LED_OFF_H 0xFD
#define PRE_SCALE 0xFE

// values used for I2C and GPIO communication
#define OUT 1
#define IN 0
#define LOW 0
#define HIGH 1
#define VALUE_MAX 30
#define BUFFER_MAX 3
#define DIRECTION_MAX 35

// Output enable pin.  Change this if you connect the GPIO pin to something other than Wiring Pi pin 7
#define ENABLE_PIN 7

// public methods

ServoPi::ServoPi(unsigned char address, unsigned char use_oe_pin)
{
	/**
	* Initialise the Servo Pi - run before calling any other methods
	* @param address - I2C address
	* @param use_oe_pin - Enable the Output Enable pin on the GPIO port
	*/
	write_byte_data(address, MODE1, (unsigned char)0x00);

	// set the gpio pin as an output for the Output Enable Pin if use_oe_pin = 1

	if (use_oe_pin == 1)
	{
		// Check for wiring pi setup
		if (wiringPiSetup () == -1)
			throw std::runtime_error("Error setting up GPIO pin");

		pinMode (ENABLE_PIN, OUTPUT) ; 
	}
}

void ServoPi::set_pwm_freq(double freq, unsigned char address)
{
	/**
	* Set the PWM frequency
	* @param freq - required frequency
	* @param address - I2C address
	*/

	double scaleval = 25000000.0; // 25MHz
	scaleval /= 4096.0;			  // 12-bit
	scaleval /= freq;
	scaleval -= 1.0;
	unsigned char prescale = (unsigned char)floor(scaleval + 0.5);
	unsigned char oldmode = read_byte_data(address, (unsigned char)MODE1);
	unsigned char newmode = (oldmode & 0x7F) | 0x10;

	write_byte_data(address, (unsigned char)MODE1, newmode);
	write_byte_data(address, (unsigned char)PRE_SCALE, prescale);
	write_byte_data(address, (unsigned char)MODE1, oldmode);
	//usleep(5000); // sleep 5 milliseconds
	write_byte_data(address, (unsigned char)MODE1, oldmode | (unsigned char)0x80);
}

void ServoPi::set_pwm(unsigned char channel, int on, int off, unsigned char address)
{
	/**
	* Set the output on single channels
	* @param channel - 1 to 16
	* @param on - time period 0 to 4096
	* @param off - time period 0 to 4096
	* @param address - I2C address
	*/
	channel -= 1;
	write_byte_data(address, (unsigned char)(LED0_ON_L + 4 * channel), (unsigned char)(on & 0xFF));
	write_byte_data(address, (unsigned char)(LED0_ON_H + 4 * channel), (unsigned char)(on >> 8));
	write_byte_data(address, (unsigned char)(LED0_OFF_L + 4 * channel), (unsigned char)(off & 0xFF));
	write_byte_data(address, (unsigned char)(LED0_OFF_H + 4 * channel), (unsigned char)(off >> 8));
}

void ServoPi::set_all_pwm(int on, int off, unsigned char address)
{
	/**
	* Set the output on all channels
	* @param on - time period 0 to 4096
	* @param off - time period 0 to 4096
	* @param address - I2C address
	*/

	write_byte_data(address, (unsigned char)ALL_LED_ON_L, (unsigned char)(on & 0xFF));
	write_byte_data(address, (unsigned char)ALL_LED_ON_H, (unsigned char)(on >> 8));
	write_byte_data(address, (unsigned char)ALL_LED_OFF_L, (unsigned char)(off & 0xFF));
	write_byte_data(address, (unsigned char)ALL_LED_OFF_H, (unsigned char)(off >> 8));
}

void ServoPi::output_disable()
{
	/**
	* Disable the output via OE pin
	* @returns - 0 = OK, 1 = GPIO failed
	*/
	digitalWrite (ENABLE_PIN, 1);

}

void ServoPi::output_enable()
{
	/**
	* Enable the output via OE pin
	* @returns - 0 = OK, 1 = GPIO failed
	*/
	digitalWrite (ENABLE_PIN, 0);
}

void ServoPi::set_allcall_address(unsigned char allcalladdress, unsigned char address)
{
	/**
	* Set the I2C address for the All Call function
	* @param allcalladdress - I2C address
	*/
	unsigned char oldmode = read_byte_data(address, MODE1);
	unsigned char newmode = oldmode | (1 << 0);
	write_byte_data(address, (unsigned char)MODE1, newmode);
	write_byte_data(address, (unsigned char)ALLCALLADR, allcalladdress << 1);
}

void ServoPi::enable_allcall_address(unsigned char address)
{
	/**
	* Enable the I2C address for the All Call function
	* @param address - I2C address
	*/
	unsigned char oldmode = read_byte_data(address, MODE1);
	unsigned char newmode = oldmode | (1 << 0);
	write_byte_data(address, (unsigned char)MODE1, newmode);
}

void ServoPi::disable_allcall_address(unsigned char address)
{
	/**
	* Disable the I2C address for the All Call function
	* @param address - I2C address
	*/
	unsigned char oldmode = read_byte_data(address, MODE1);
	unsigned char newmode = oldmode & ~(1 << 0);
	write_byte_data(address, (unsigned char)MODE1, newmode);
}

// private methods

// stops file handle leakage on exceptions
class ScopedFileHandle{
public:
    ScopedFileHandle(int fd) :_fd(fd){}
    ~ScopedFileHandle(){ if(_fd >= 0) close(_fd); }
    operator int() const { return _fd; }
private:
    int _fd;
};

int ServoPi::read_byte_data(unsigned char address, unsigned char reg)
{
	/*
	internal method for reading data from the i2c bus
	*/
	ScopedFileHandle i2cbus(open(fileName, O_RDWR));
    if (i2cbus < 0)
	{
		throw std::runtime_error("read_byte_data: Failed to open i2c port for read");
	}

	if (ioctl(i2cbus, I2C_SLAVE, address) < 0)
	{
		throw std::runtime_error("read_byte_data: Failed to write to i2c port for read");
	}

	buf[0] = reg;

	if ((write(i2cbus, buf, 1)) != 1)
	{
		throw std::runtime_error("read_byte_data: Failed to write to i2c device for read");
	}

	if (read(i2cbus, buf, 1) != 1)
	{ // Read back data into buf[]
		throw std::runtime_error("read_byte_data: Failed to read from slave");
	}

	close(i2cbus);

	return (buf[0]);
}

void ServoPi::write_byte_data(unsigned char address, unsigned char reg, unsigned char value)
{
	/**
	* private method for writing a byte to the I2C port
	*/
    ScopedFileHandle i2cbus(open(fileName, O_RDWR));
    if (i2cbus < 0)
	{
		throw std::runtime_error("write_byte_data: Failed to open i2c port for write");
	}

	if (ioctl(i2cbus, I2C_SLAVE, address) < 0)
	{
		throw std::runtime_error("write_byte_data: Failed to write to i2c port for write");
	}

	buf[0] = reg;
	buf[1] = value;

	if ((write(i2cbus, buf, 2)) != 2)
	{
		throw std::runtime_error("write_byte_data: Failed to write to i2c device for write");
	}

	close(i2cbus);
}