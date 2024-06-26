/*
================================================
AB Electronics UK RTC Pi real-time clock
See CHANGELOG.md for the version number.
================================================

Required package:
apt-get install libi2c-dev
*/

#ifndef RTCPI_ABE_RTCPI_H_
#define RTCPI_ABE_RTCPI_H_

#endif /* RTCPI_ABE_RTCPI_H_ */

namespace ABElectronics_CPP_Libraries
{
class RTCPi
{

public:

/**
* Initialise the RTC Pi Object
*/
RTCPi();

/**
* Set the date on the RTC
* @param - date - struct tm formatted date and time
*/
void set_date(struct tm date);


/**
* Read the date from the RTC.
* @returns - date as a tm struct
*/
struct tm read_date();

/**
* Enable the squarewave output pin
*/
void enable_output();

/**
* Disable the squarewave output pin
*/
void disable_output();

/**
* Set the squarewave output frequency
* @param - 1 = 1Hz, 2 = 4.096KHz, 3 = 8.192KHz, 4 = 32.768KHz
*/
void set_frequency(uint8_t frequency);

/**
* Write to the memory on the DS1307
* The DS1307 contains 56 - Byte, battery-backed RAM with Unlimited Writes
* @param address - 0x08 to 0x3F
* @param valuearray - byte array containing data to be written to memory
* @param length - up to 56 bytes.  length of byte array can not exceed the available address space.
*/
void write_memory(uint8_t address, uint8_t *valuearray, uint8_t length);

/**
* Read from the memory on the DS1307
* The ds1307 contains 56-Byte, battery-backed RAM with Unlimited Writes
* @param address - 0x08 to 0x3F
* @param length - up to 56 bytes.  length can not exceed the available address space.
* @returns - pointer to a byte array where the data will be saved
*/
uint8_t *read_memory(uint8_t address, uint8_t length);

private:

// Define local variables
uint16_t rtcCentury;

int i2cbus;
uint8_t buf[10];
uint8_t writebuffer[60];
uint8_t readbuffer[60];

uint8_t read_byte_data(uint8_t reg);
void read_byte_array(uint8_t reg, uint8_t length);
void write_byte_data(uint8_t reg, uint8_t value);
static void write_byte_array(uint8_t buffer[], uint8_t length);
static uint8_t bcd_to_dec(uint8_t bcd);
static uint8_t dec_to_bcd(uint8_t dec);
static uint8_t update_byte(uint8_t byte, uint8_t bit, uint8_t value);

};
}