/*
================================================
ABElectronics UK RTC Pi real-time clock
Version 1.1 Updated 21/04/2020
================================================

Required package{
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
* @param - date - struct tm formated date and time
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
void set_frequency(unsigned char frequency);

/**
* write to the memory on the ds1307
* the ds1307 contains 56 - Byte, battery - backed RAM with Unlimited Writes
* @param address - 0x08 to 0x3F
* @param valuearray - byte array containing data to be written to memory
*/
void write_memory(unsigned char address, unsigned char *valuearray);

/**
* read from the memory on the ds1307
* the ds1307 contains 56-Byte, battery-backed RAM with Unlimited Writes
* @param address - 0x08 to 0x3F
* @param length - up to 32 bytes.  length can not exceed the avaiable address space.
* @returns - pointer to a byte array where the data will be saved
*/
unsigned char *read_memory(unsigned char address, int length);

private:

// Define local variables
unsigned char rtcConfig;
unsigned int rtcCentury;

int i2cbus;
unsigned char buf[10];
unsigned char writebuffer[60];
unsigned char readbuffer[60];

void read_byte_array(unsigned char reg, unsigned char length);
void write_byte_data(unsigned char reg, unsigned char value);
void write_byte_array(unsigned char buffer[], unsigned char length);
unsigned char bcd_to_dec(unsigned char bcd);
unsigned char dec_to_bcd(unsigned char dec);
unsigned char updatebyte(unsigned char byte, unsigned char bit, unsigned char value);

};
}