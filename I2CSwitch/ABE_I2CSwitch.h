/*
================================================
ABElectronics UK I2C Switch
================================================

I2C Switch class for the PCA9546A controller from NXP

Required packages: i2c-dev and wiringPi
apt-get install libi2c-dev wiringpi
*/

#ifndef I2CSWITCH_ABE_I2CSWITCH_H_
#define I2CSWITCH_ABE_I2CSWITCH_H_

#endif /* I2CSWITCH_ABE_I2CSWITCH_H_ */

namespace ABElectronics_CPP_Libraries
{
class I2CSwitch
{

public:
    // public methods

/**
* Initialise the Servo Pi - run before calling any other methods
* @param address - I2C address.  0x70 to 0x77
*/
I2CSwitch(uint8_t address);


/**
* Enable the specified I2C channel and disable other channels
* @param channel - 1 to 4
*/
void switch_channel(uint8_t channel);


/**
* Sets the state of the specified I2C channel.
* All other channels keep their existing state.
* @param channel - 1 to 4
*/
void set_channel_state(uint8_t channel, uint8_t state);


/**
* Gets the state of the specified I2C channel
* @param channel - 1 to 4
* @returns - 0 = channel off, 1 = channel on
*/
uint8_t get_channel_state(uint8_t channel);


/**
* Reset the I2C switch.  All channels are set to off.
*/
void reset();

private:

// private variables
int i2cbus; // I2C bus 
uint8_t i2caddress; // I2C address
uint8_t buf[10];

// private methods
int read_byte_data();
void write_byte_data(uint8_t value);
uint8_t updatebyte(uint8_t byte, uint8_t bit, uint8_t value);
uint8_t checkbit(uint8_t byte, uint8_t bit);
int gpio_export(int pin);
int gpio_direction(int pin, int dir);
int gpio_write(int pin, int value);

};
}
