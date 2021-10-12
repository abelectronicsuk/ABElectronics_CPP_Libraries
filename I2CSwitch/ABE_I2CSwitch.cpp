/*
================================================
ABElectronics UK I2C Switch
================================================

I2C Switch class for the PCA9546A controller from NXP

Required packages: i2c-dev and wiringPi
apt-get install libi2c-dev wiringpi
*/

//#define TESTMODE // used for unit testing, comment out when using with the I2C Switch board

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
#include <unistd.h>

#ifdef TESTMODE
	#include "../UnitTest/testlibs.h"
#else
	#include <wiringPi.h>
#endif

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

I2CSwitch::I2CSwitch(uint8_t address)
{
	/**
	* Initialise the I2CSwitch Pi - run before calling any other methods
	* @param address - I2C address
	*/

	if (address < 0x70 || address > 0x77)
	{
		throw std::out_of_range("I2CSwitch address out of range: 0x70 to 0x77");
	}

	i2caddress = address;

	//Enable GPIO Reset pin

    #ifdef TESTMODE
        TestLibs test;
        test.digitalWrite (RESETPIN, 1);
    #else
	if (wiringPiSetup () == -1) throw std::runtime_error("reset: Failed to reset switch. GPIO error!");

	pinMode (RESETPIN, OUTPUT) ;
	
	// set reset pin high
	digitalWrite (RESETPIN, 1);
    #endif
}

void I2CSwitch::switch_channel(uint8_t channel) {
	/**
	* Enable the specified I2C channel and disable other channels
	* @param channel - 1 to 4
	*/
	if (channel < 1 || channel > 4){
		throw std::runtime_error("switch_channel: channel out of range. 1 - 4");
	}
	uint8_t cval = 0;
	cval = updatebyte(cval, channel - 1, 1);
	write_byte_data(cval);
}

void I2CSwitch::set_channel_state(uint8_t channel, uint8_t state) {
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
	uint8_t cval = read_byte_data();
	cval = updatebyte(cval, channel -1, state);
	write_byte_data(cval);
}

uint8_t I2CSwitch::get_channel_state(uint8_t channel) {
	/**
	* Gets the state of the specified I2C channel
	* @param channel - 1 to 4
	* @returns - 1 or 0
	*/
	if (channel < 1 || channel > 4){
		throw std::runtime_error("get_channel_state: channel out of range. 1 - 4");
	}
	uint8_t cval = read_byte_data();
	return (checkbit(cval, channel - 1));
}

void I2CSwitch::reset(){
	/**
	* Reset the I2C switch.  All channels are set to off.
	*/

	//Enable GPIO pins
	#ifdef TESTMODE
        TestLibs test;
        test.digitalWrite (RESETPIN, 0);
		test.digitalWrite (RESETPIN, 1);
    #else
	if (wiringPiSetup () == -1) throw std::runtime_error("reset: Failed to reset switch. GPIO error!");

	pinMode (RESETPIN, OUTPUT) ;
	
	// set reset pin low
	digitalWrite (RESETPIN, 0);
	
	// wait 1ms before setting reset pin high
	usleep (1000);  

	digitalWrite (RESETPIN, 1);

	#endif

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
	#ifdef TESTMODE		
        TestLibs test;		
		buf[0] = test.i2c_emulator_read_byte_data(0x00);
	#else

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

	#endif

	return (buf[0]);
}

void I2CSwitch::write_byte_data(uint8_t value)
{
	/**
	* private method for writing a byte to the I2C port
	*/

	#ifdef TESTMODE
		TestLibs test;
		test.i2c_emulator_write_byte_data(0x00, value);
	#else

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

	#endif
}

uint8_t I2CSwitch::updatebyte(uint8_t byte, uint8_t bit, uint8_t value) {
	/*
	 internal method for setting the value of a single bit within a byte
	 */
	if (value == 0) {
		return (byte &= ~(1 << bit));

	} else {
		return (byte |= 1 << bit);
	}

}

uint8_t I2CSwitch::checkbit(uint8_t byte, uint8_t bit) {
	/*
	 internal method for reading the value of a single bit within a byte
	 */
	if (byte & (1 << bit)) {
		return (1);
	} else {
		return (0);
	}
}