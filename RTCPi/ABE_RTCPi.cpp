/*
================================================
ABElectronics UK RTC Pi real-time clock
See CHANGELOG.md for version number.
================================================

Required package{
apt-get install libi2c-dev
*/

//#define TESTMODE // used for unit testing, comment out when using with the Servo Pi board

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
#include <time.h>
#include <vector>
#include <unistd.h>

#ifdef TESTMODE
	#include "../UnitTest/testlibs.h"
#endif

#include "ABE_RTCPi.h"

using namespace ABElectronics_CPP_Libraries;

#define fileName "/dev/i2c-1" // change to /dev/i2c-0 if you are using a Raspberry Pi revision 0002 or 0003 model B

// Define registers values from datasheet
#define RTCADDRESS 0x68
#define SECONDS 0x00
#define MINUTES 0x01
#define HOURS 0x02
#define DAYOFWEEK 0x03
#define DAY 0x04
#define MONTH 0x05
#define YEAR 0x06
#define CONTROL 0x07

#define HI_NIBBLE(b) (((b) >> 4) & 0x0F)
#define LO_NIBBLE(b) ((b) & 0x0F)

RTCPi::RTCPi(){
	rtcCentury = 2000;
}

// stops file handle leakage on exceptions
class ScopedFileHandle{
public:
    ScopedFileHandle(int fd) :_fd(fd){}
    ~ScopedFileHandle(){ if(_fd >= 0) close(_fd); }
    operator int() const { return _fd; }
private:
    int _fd;
};

uint8_t RTCPi::read_byte_data(uint8_t reg)
{
	/**
	* private method for reading a byte from the I2C port
	*/
	#ifdef TESTMODE	
        TestLibs test;	
		readbuffer[0] = test.i2c_emulator_read_byte_data(reg);
	#else

	ScopedFileHandle i2cbus(open(fileName, O_RDWR));
	if (i2cbus < 0)
	{
		throw std::runtime_error("Failed to open i2c port for read");
	}

	if (ioctl(i2cbus, I2C_SLAVE, RTCADDRESS) < 0)
	{
		throw std::runtime_error("Failed to write to i2c port for read");
	}

	readbuffer[0] = reg;

	if ((write(i2cbus, readbuffer, 1)) != 1)
	{
		throw std::runtime_error("Failed to write to i2c device for read");
	}

	if (read(i2cbus, readbuffer, 1) != 1)
	{ // Read back data into buf[]
		throw std::runtime_error("Failed to read from slave");
	}

	close(i2cbus);

	#endif

	return (readbuffer[0]);
}

void RTCPi::read_byte_array(uint8_t reg, uint8_t length) {
	/*
	internal method for reading data from the i2c bus
	*/

    #ifdef TESTMODE
		TestLibs test;
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

	if (ioctl(i2cbus, I2C_SLAVE, RTCADDRESS) < 0)
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

void RTCPi::write_byte_data(uint8_t reg, uint8_t value) {
	/**
	* private method for writing a byte to the I2C port
	*/

    #ifdef TESTMODE
		TestLibs test;
		test.i2c_emulator_write_byte_data(reg, value);
	#else

    ScopedFileHandle i2cbus(open(fileName, O_RDWR));
    if (i2cbus < 0)
	{
		throw std::runtime_error("write_byte_data: Failed to open i2c port for write");
	}

	if (ioctl(i2cbus, I2C_SLAVE, RTCADDRESS) < 0)
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

    #endif
}

void RTCPi::write_byte_array(uint8_t buffer[], uint8_t length) {
	/*
	internal method for writing data to the i2c bus
	*/

    #ifdef TESTMODE
		TestLibs test;
        uint8_t address = buffer[0];
        if (length > 1){
            for (uint8_t i = 1; i <= length; i++){
                test.i2c_emulator_write_byte_data(address + (i-1), buffer[i]);
            }
        }		
	#else

	ScopedFileHandle i2cbus(open(fileName, O_RDWR));
    if (i2cbus < 0)
	{
		throw std::runtime_error("write_byte_array: Failed to open i2c port for write");
	}

	if (ioctl(i2cbus, I2C_SLAVE, RTCADDRESS) < 0)
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

uint8_t RTCPi::bcd_to_dec(uint8_t bcd) {
	/*
	internal method for converting a bcd formatted number to decimal
	*/

	return (uint8_t)((HI_NIBBLE(bcd) * 10) + (LO_NIBBLE(bcd)));
}

uint8_t RTCPi::dec_to_bcd(uint8_t dec) {
	/*
	internal method for converting a decimal formatted number to bcd
	*/
	return (uint8_t)((dec / 10) * 16) + (dec % 10);
}

uint8_t RTCPi::updatebyte(uint8_t byte, uint8_t bit, uint8_t value) {
	/*
	internal method for setting the value of a single bit within a byte
	*/
	if (value == 0) {
		return (byte &= ~(1 << bit));

	}
	else {
		return (byte |= 1 << bit);
	}

}

void RTCPi::set_date(struct tm date) {
	/**
	* Set the date on the RTC
	* @param - date - struct tm formated date and time
	*/
	writebuffer[0] = SECONDS; // register address for seconds
	writebuffer[1] = dec_to_bcd(date.tm_sec); // seconds
	writebuffer[2] = dec_to_bcd(date.tm_min); // minutes
	writebuffer[3] = dec_to_bcd(date.tm_hour);// hours
	writebuffer[4] = dec_to_bcd(date.tm_wday);// dayofweek
	writebuffer[5] = dec_to_bcd(date.tm_mday);// day
	writebuffer[6] = dec_to_bcd(date.tm_mon) + 1;// month
	writebuffer[7] = dec_to_bcd(date.tm_year % 100); // strip the century from the date

	write_byte_array(writebuffer, 8);
}

struct tm RTCPi::read_date() {
	/**
	* Read the date from the RTC.
	* @returns - date as a tm struct
	*/

	read_byte_array(0, 7);
	struct tm date;
	date.tm_sec = bcd_to_dec(readbuffer[0]); // seconds
	date.tm_min = bcd_to_dec(readbuffer[1]); // minutes
	date.tm_hour = bcd_to_dec(readbuffer[2]);// hours
	date.tm_wday = bcd_to_dec(readbuffer[3]);// dayofweek
	date.tm_mday = bcd_to_dec(readbuffer[4]);// day
	date.tm_mon = bcd_to_dec(readbuffer[5]) - 1;// month
	date.tm_year = bcd_to_dec(readbuffer[6]) + (rtcCentury - 1900);// year

	return date;
}

void RTCPi::enable_output() {
	/**
	* Enable the squarewave output pin
	*/
	uint8_t config = read_byte_data(CONTROL);
	config = updatebyte(config, 7, 1);
	config = updatebyte(config, 4, 1);
	write_byte_data(CONTROL, config);
}

void RTCPi::disable_output() {
	/**
	* Disable the squarewave output pin
	*/
    uint8_t config = read_byte_data(CONTROL);
	config = updatebyte(config, 7, 0);
	config = updatebyte(config, 4, 0);
	write_byte_data(CONTROL, config);
}

void RTCPi::set_frequency(uint8_t frequency) {
	/**
	* Set the squarewave output frequency
	* @param - 1 = 1Hz, 2 = 4.096KHz, 3 = 8.192KHz, 4 = 32.768KHz
	*/
    uint8_t config = read_byte_data(CONTROL);

	switch (frequency) {
		case 1:
			config = updatebyte(config, 0, 0);
			config = updatebyte(config, 1, 0);
			write_byte_data(CONTROL, config);
			break;
		case 2:
			config = updatebyte(config, 0, 1);
			config = updatebyte(config, 1, 0);
			write_byte_data(CONTROL, config);
			break;
		case 3:
			config = updatebyte(config, 0, 0);
			config = updatebyte(config, 1, 1);
			write_byte_data(CONTROL, config);
			break;
		case 4:
			config = updatebyte(config, 0, 1);
			config = updatebyte(config, 1, 1);
			write_byte_data(CONTROL, config);
			break;
		default:
			throw std::out_of_range("Error: set_frequency() - value must be between 1 and 4");
	}
}

void RTCPi::write_memory(uint8_t address, uint8_t *valuearray, uint8_t length) {
	/**
	* write to the memory on the ds1307
	* the ds1307 contains 56 - Byte, battery - backed RAM with Unlimited Writes
	* @param address - 0x08 to 0x3F
	* @param valuearray - byte array containing data to be written to memory
	*/

	if (address >= 0x08 && address <= 0x3F) {
		if (address <= (0x3F - (length - 1))) {
			
			uint8_t *writearray = (uint8_t*)malloc(length + 1);

			if (errno == ENOMEM) { // Fail!!!!
				free(writearray);
				throw std::runtime_error("memory allocation error: not enough system memory to allocate array");
			}
			else {

				writearray[0] = address;

				int a;
				for (a = 0; a < length; a++) {
					writearray[a + 1] = valuearray[a];
				}
				
				write_byte_array(writearray, length);
				
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

uint8_t *RTCPi::read_memory(uint8_t address, uint8_t length) {
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

			if (errno == ENOMEM) { // Fail!!!!
				free(writearray);
				throw std::runtime_error("memory allocation error: not enough system memory to allocate array");
				return NULL;
			}
			else {
				read_byte_array(address, length); // read the values from the SRAM into the read buffer

				// copy the read buffer into the writearray
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