/*
================================================
ABElectronics UK I2C Switch
 Version 1.0 Created 26/11/2019
================================================

Required package{
sudo apt-get install libi2c-dev
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
I2CSwitch(char address);


/**
* Enable the specified I2C channel and disable other channels
* @param channel - 1 to 4
*/
void switch_channel(char channel);


/**
* Sets the state of the specified I2C channel.
* All other channels keep their existing state.
* @param channel - 1 to 4
*/
void set_channel_state(char channel, char state);


/**
* Gets the state of the specified I2C channel
* @param channel - 1 to 4
* @returns - 0 = channel off, 1 = channel on
*/
char get_channel_state(char channel);


/**
* Reset the I2C switch.  All channels are set to off.
*/
void reset();

private:

// private variables
int i2cbus; // I2C bus 
char i2caddress; // I2C address
unsigned char buf[10];

// private methods
int read_byte_data();
void write_byte_data(char value);
char updatebyte(char byte, char bit, char value);
char checkbit(char byte, char bit);
int gpio_export(int pin);
int gpio_direction(int pin, int dir);
int gpio_write(int pin, int value);

};
}
