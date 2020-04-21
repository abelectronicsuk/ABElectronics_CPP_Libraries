/*
================================================
ABElectronics UK I2C Switch
Version 1.1 Updated 21/04/2020
================================================


 Required packages: i2c-dev and wiringPi
 apt-get install libi2c-dev wiringpi
 */

//#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <errno.h>
#include <fcntl.h>
#include <cstring>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/i2c-dev.h>
#include <time.h>
#include <wiringPi.h>
#include <unistd.h>

#include "ABE_I2CSwitch.h"

using namespace ABElectronics_CPP_Libraries;

#define fileName "/dev/i2c-1"
// change to /dev/i2c-0 if you are using a revision 0002 or 0003 model B

#define RESETPIN 2 // GPIO Reset Pin

// values used for I2C and GPIO communication
#define OUT 1
#define IN  0
#define LOW  0
#define HIGH 1
#define VALUE_MAX 30
#define BUFFER_MAX 3
#define DIRECTION_MAX 35


// public methods

I2CSwitch::I2CSwitch(unsigned char address)
{
	/**
	* Initialise the Servo Pi - run before calling any other methods
	* @param address - I2C address
	*/

	i2caddress = address;

	//Enable GPIO Reset pin

	if (wiringPiSetup () == -1) throw std::runtime_error("reset: Failed to reset switch. GPIO error!");

	pinMode (RESETPIN, OUTPUT) ;
	
	// set reset pin high
	digitalWrite (RESETPIN, 1);
}

void I2CSwitch::switch_channel(unsigned char channel) {
	/**
	* Enable the specified I2C channel and disable other channels
	* @param channel - 1 to 4
	*/
	if (channel < 1 || channel > 4){
		throw std::runtime_error("switch_channel: channel out of range. 1 - 4");
	}
	unsigned char cval = 0;
	cval = updatebyte(cval, channel - 1, 1);
	write_byte_data(cval);
}

void I2CSwitch::set_channel_state(unsigned char channel, unsigned char state) {
	/**
	* Sets the state of the specified I2C channel.
	* All other channels keep their existing state.
	* @param channel - 1 to 4
	* @param state - 0 or 1
	*/
	if (channel < 1 || channel > 4){
		throw std::runtime_error("set_channel_state: channel out of range. 1 - 4");
	}
	if (state > 1){
		throw std::runtime_error("set_channel_state: state out of range. 0 or 1");
		fprintf(stderr, "state out of range. 0 or 1\n");
	}
	unsigned char cval = read_byte_data();
	cval = updatebyte(cval, channel -1, state);
	write_byte_data(cval);
}

unsigned char I2CSwitch::get_channel_state(unsigned char channel) {
	/**
	* Gets the state of the specified I2C channel
	* @param channel - 1 to 4
	* @returns - 1 or 0
	*/
	if (channel < 1 || channel > 4){
		throw std::runtime_error("get_channel_state: channel out of range. 1 - 4");
	}
	unsigned char cval = read_byte_data();
	return (checkbit(cval, channel - 1));
}

void I2CSwitch::reset(){
	/**
	* Reset the I2C switch.  All channels are set to off.
	*/

	//Enable GPIO pins

	if (wiringPiSetup () == -1) throw std::runtime_error("reset: Failed to reset switch. GPIO error!");

	pinMode (RESETPIN, OUTPUT) ;
	
	// set reset pin low
	digitalWrite (RESETPIN, 0);
	
	// wait 1ms before setting reset pin high
	usleep (1000);  

	digitalWrite (RESETPIN, 1);

	// wait 1ms for the switch to reset
	usleep (1000);  
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

int I2CSwitch::read_byte_data()
{
	/*
	internal method for reading data from the i2c bus
	*/
	ScopedFileHandle i2cbus(open(fileName, O_RDWR));
    if (i2cbus < 0)
	{
		throw std::runtime_error("read_byte_data: Failed to open i2c port for read");
	}
	
	if (ioctl(i2cbus, I2C_SLAVE, i2caddress) < 0)
	{
		throw std::runtime_error("read_byte_data: Failed to write to i2c port for read");
	}

	if (read(i2cbus, buf, 1) != 1)
	{ // Read back data into buf[]
		throw std::runtime_error("read_byte_data: Failed to read from slave");
	}
	
	close(i2cbus);

	return (buf[0]);
}

void I2CSwitch::write_byte_data(unsigned char value)
{
	/**
	* private method for writing a byte to the I2C port
	*/
    ScopedFileHandle i2cbus(open(fileName, O_RDWR));
    if (i2cbus < 0)
	{
		throw std::runtime_error("write_byte_data: Failed to open i2c port for write");
	}

	if (ioctl(i2cbus, I2C_SLAVE, i2caddress) < 0)
	{
		throw std::runtime_error("write_byte_data: Failed to write i2c port for write");
	}

	buf[0] = value;

	if ((write(i2cbus, buf, 1)) != 1)
	{
		throw std::runtime_error("write_byte_data: Failed to write buffer to i2c device");
	}

	close(i2cbus);
}

unsigned char I2CSwitch::updatebyte(unsigned char byte, unsigned char bit, unsigned char value) {
	/*
	 internal method for setting the value of a single bit within a byte
	 */
	if (value == 0) {
		return (byte &= ~(1 << bit));

	} else {
		return (byte |= 1 << bit);
	}

}

unsigned char I2CSwitch::checkbit(unsigned char byte, unsigned char bit) {
	/*
	 internal method for reading the value of a single bit within a byte
	 */
	if (byte & (1 << bit)) {
		return (1);
	} else {
		return (0);
	}
}