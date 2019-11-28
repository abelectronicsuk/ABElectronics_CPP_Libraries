/*
================================================
ABElectronics UK I2C Switch
 Version 1.0 Created 26/11/2019
================================================


 Required package{
 apt-get install libi2c-dev
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
//#include <math.h>
#include <unistd.h>

#include "ABE_I2CSwitch.h"

using namespace ABElectronics_CPP_Libraries;

#define fileName "/dev/i2c-1"
// change to /dev/i2c-0 if you are using a revision 0002 or 0003 model B

#define RESETPIN 27 // GPIO Reset Pin

// values used for I2C and GPIO communication
#define OUT 1
#define IN  0
#define LOW  0
#define HIGH 1
#define VALUE_MAX 30
#define BUFFER_MAX 3
#define DIRECTION_MAX 35


// public methods

I2CSwitch::I2CSwitch(char address)
{
	/**
	* Initialise the Servo Pi - run before calling any other methods
	* @param address - I2C address
	*/

	i2caddress = address;
}

void I2CSwitch::switch_channel(char channel) {
	/**
	* Enable the specified I2C channel and disable other channels
	* @param channel - 1 to 4
	*/
	if (channel < 1 || channel > 4){
		throw std::runtime_error("switch_channel: channel out of range. 1 - 4");
	}
	char cval = 0;
	cval = updatebyte(cval, channel - 1, 1);
	write_byte_data(cval);
}

void I2CSwitch::set_channel_state(char channel, char state) {
	/**
	* Sets the state of the specified I2C channel.
	* All other channels keep their existing state.
	* @param channel - 1 to 4
	* @param state - 0 or 1
	*/
	if (channel < 1 || channel > 4){
		throw std::runtime_error("set_channel_state: channel out of range. 1 - 4");
	}
	if (state < 0 || state > 1){
		throw std::runtime_error("set_channel_state: state out of range. 0 or 1");
		fprintf(stderr, "state out of range. 0 or 1\n");
	}
	char cval = read_byte_data();
	cval = updatebyte(cval, channel -1, state);
	write_byte_data(cval);
}

char I2CSwitch::get_channel_state(char channel) {
	/**
	* Gets the state of the specified I2C channel
	* @param channel - 1 to 4
	* @returns - 1 or 0
	*/
	if (channel < 1 || channel > 4){
		throw std::runtime_error("get_channel_state: channel out of range. 1 - 4");
	}
	char cval = read_byte_data();
	return (checkbit(cval, channel - 1));
}

void I2CSwitch::reset(){
	/**
	* Reset the I2C switch.  All channels are set to off.
	*/
	char failed = 0;

	//Enable GPIO pins

		if (-1 == gpio_export(RESETPIN))
			failed = 1;

		/*
		 * Set GPIO directions
		 */
		if (-1 == gpio_direction(RESETPIN, OUT))
			failed = 1;
	
	// set reset pin low
	if (-1 == gpio_write(RESETPIN, 0)) {
		failed = 1;	
	}
	
	// wait 1ms before setting reset pin high
	usleep (1000);  

	if (-1 == gpio_write(RESETPIN, 1)) {
		failed = 1;	
	}

	// wait 1ms for the switch to reset
	usleep (1000);  

	if (failed == 1){
		throw std::runtime_error("reset: Failed to reset switch. GPIO error!");
	}
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

void I2CSwitch::write_byte_data(char value)
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

char I2CSwitch::updatebyte(char byte, char bit, char value) {
	/*
	 internal method for setting the value of a single bit within a byte
	 */
	if (value == 0) {
		return (byte &= ~(1 << bit));

	} else {
		return (byte |= 1 << bit);
	}

}

char I2CSwitch::checkbit(char byte, char bit) {
	/*
	 internal method for reading the value of a single bit within a byte
	 */
	if (byte & (1 << bit)) {
		return (1);
	} else {
		return (0);
	}
}

int I2CSwitch::gpio_export(int pin)
{

	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;

	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (-1 == fd)
	{
		throw std::runtime_error("Failed to open export for writing");
	}

	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return (0);
}

int I2CSwitch::gpio_direction(int pin, int dir)
{
	static const char s_directions_str[] = "in\0out";
	char path[DIRECTION_MAX];
	int fd;

	snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
	fd = open(path, O_WRONLY);
	if (-1 == fd)
	{
		throw std::runtime_error("Failed to open gpio direction for writing");
	}

	if (-1 == write(fd, &s_directions_str[IN == dir ? 0 : 3], IN == dir ? 2 : 3))
	{
		throw std::runtime_error("Failed to set direction");
	}

	close(fd);
	return (0);
}

int I2CSwitch::gpio_write(int pin, int value)
{
	static const char s_values_str[] = "01";

	char path[VALUE_MAX];
	int fd;

	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_WRONLY);
	if (-1 == fd)
	{
		throw std::runtime_error("Failed to open gpio value for writing");
	}

	if (1 != write(fd, &s_values_str[LOW == value ? 0 : 1], 1))
	{
		throw std::runtime_error("Failed to write value");
	}

	close(fd);
	return (0);
}