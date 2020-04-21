/*
================================================
ABElectronics UK ADC Servo Pi 16 Channel PWM controller
Version 1.1 Updated 21/04/2020
================================================

Required package{
apt-get install libi2c-dev
*/

#ifndef SERVOPI_ABE_SERVOPI_H_
#define SERVOPI_ABE_SERVOPI_H_

#endif /* SERVOPI_ABE_SERVOPI_H_ */

namespace ABElectronics_CPP_Libraries
{
class ServoPi
{

public:


/**
* Initialise the Servo Pi - run before calling any other methods
* @param address - I2C address
* @param use_oe_pin - Enable the Output Enable pin on the GPIO port
*/
ServoPi(unsigned char address, unsigned char use_oe_pin);


/**
* Set the PWM frequency
* @param freq - required frequency
* @param address - I2C address
*/
void set_pwm_freq(double freq, unsigned char address);

/**
* Set the output on single channels
* @param channel - 1 to 16
* @param on - time period 0 to 4096
* @param off - time period 0 to 4096
* @param address - I2C address
*/
void set_pwm(unsigned char channel, int on, int off, unsigned char address);

/**
* Set the output on all channels
* @param on - time period 0 to 4096
* @param off - time period 0 to 4096
* @param address - I2C address
*/
void set_all_pwm(int on, int off, unsigned char address);

/**
* Disable the output via OE pin
*/
void output_disable();

/**
* Enable the output via OE pin
*/
void output_enable();

/**
* Set the I2C address for the All Call function
* @param allcalladdress - I2C address
*/
void set_allcall_address(unsigned char allcalladdress, unsigned char address);

/**
* Enable the I2C address for the All Call function
* @param address - I2C address
*/
void enable_allcall_address(unsigned char address);

/**
* Disable the I2C address for the All Call function
* @param address - I2C address
*/
void disable_allcall_address(unsigned char address);

private:

// private variables
int i2cbus;
unsigned char buf[10];



// private methods
int read_byte_data(unsigned char address, unsigned char reg);
void write_byte_data(unsigned char address, unsigned char reg, unsigned char value);
};
}
