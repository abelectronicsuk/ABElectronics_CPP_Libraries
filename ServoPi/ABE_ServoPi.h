/*
================================================
AB Electronics UK Servo Pi 16-Channel PWM Servo Controller
See CHANGELOG.md for the version number.
================================================

Note:  From version 1.1.3 the ServoPi class is called PWM.

Required packages: i2c-dev and wiringPi
apt-get install libi2c-dev wiringpi
*/

#ifndef SERVOPI_ABE_SERVOPI_H_
#define SERVOPI_ABE_SERVOPI_H_

#include <vector>

namespace ABElectronics_CPP_Libraries
{
class PWM
{

public:


/**
* Initialise the Servo Pi - run before calling any other methods
* @param address - I2C address. Defaults to 0x40
* @param use_oe_pin - Enable the Output Enable pin on the GPIO port. Defaults to false.
*/
PWM(uint8_t address=0x40, bool use_oe_pin=false);


/**
* Set the PWM frequency
* @param freq - 40 to 1000
* @param calibration - optional integer value to offset oscillator errors. Defaults to 0
*/
void set_pwm_freq(double freq, uint8_t calibration=0);


/**
* Set the output for single channel
* @param channel - 1 to 16
* @param on_time - time period 0 to 4095
* @param off_time - time period 0 to 4095
*/
void set_pwm(uint8_t channel, uint16_t on_time, uint16_t off_time);


/**
* Set the output on time for a single channel
* @param channel - 1 to 16
* @param on_time - time period 0 to 4095
*/
void set_pwm_on_time(uint8_t channel, uint16_t on_time);


/**
* Set the output off time for a single channel
* @param channel - 1 to 16
* @param off_time - time period 0 to 4095
*/
void set_pwm_off_time(uint8_t channel, uint16_t off_time);


/**
* Get the output on time for a single channel
* @param channel - 1 to 16
* @return (uint16_t) on time
*/
uint16_t get_pwm_on_time(uint8_t channel);


/**
* Get the output off time for a single channel
* @param channel - 1 to 16
* @return (uint16_t) off time
*/
uint16_t get_pwm_off_time(uint8_t channel);


/**
* Set the output for all channels
* @param on - time period 0 to 4095
* @param off - time period 0 to 4095
*/
void set_all_pwm(uint16_t on_time, uint16_t off_time);


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
* @param allcalladdress - I2C address 0x40 to 0x7F
*/
void set_allcall_address(uint8_t allcalladdress);


/**
* Enable the I2C address for the All Call function
*/
void enable_allcall_address();

/**
* Disable the I2C address for the All Call function
*/
void disable_allcall_address();


/**
* Put the device into a sleep state
*/
void sleep();


/**
* Wake the device from its sleep state
*/
void wake();


/**
* Check the sleep status of the device
* @return true or false
*/
bool is_sleeping();


/**
* Invert the PWM output on all channels
* @param state = true = inverted, false = non-inverted
*/
void invert_output(bool state);

/**
* Set the I2C address
* @param address = i2c address
*/
void set_address(uint8_t address);

/**
* Get the I2C address
* @return i2c address
*/
uint8_t get_address();

/**
* Enable the Output Enable Pin on the GPIO header
*/
void enable_oe_pin();

private:

// Private variables
int i2cbus; // I2C bus 
uint8_t i2caddress; // I2C address
uint8_t buf[10];
bool oe_pin_enabled = false;

// Private methods
uint8_t read_byte_data(uint8_t reg);
void write_byte_data(uint8_t reg, uint8_t value);
};


class Servo
{
/**
 * Servo class for controlling analogue RC servos with the Servo PWM Pi Zero
 */
public:


/**
* Initialise the Servo object
* @param address - i2c address for the ServoPi board, defaults to 0x40
* @param low_limit - Pulse length in milliseconds for the lower servo limit, defaults to 1.0
* @param high_limit - Pulse length in milliseconds for the upper servo limit, defaults to 2.0
* @param reset - true = reset the controller and turn off all channels.
*                false = keep existing servo positions and frequency.
*                Defaults to true
* @param use_oe_pin - Enable the Output Enable pin on the GPIO port.  Defaults to true.
*/
Servo(uint8_t address=0x40, double low_limit=1.0, double high_limit=2.0, bool reset=true, bool use_oe_pin=true);


/**
* Set the servo position
* @param channel - 1 to 16
* @param position - value between 0 and the maximum number of steps.
* @param steps - The number of steps between the low and high limits.
*                This can be any number between 0 and 4095.
*                On a typical RC servo a step value of 250 is recommended.
*                Defaults to 250
*/
void move(uint8_t channel, uint16_t position, uint16_t steps=250);


/**
* Get the servo position
* @param channel - 1 to 16
* @param steps - The number of steps between the low and high limits.
*                This can be any number between 0 and 4095.
*                On a typical RC servo a step value of 250 is recommended.
*                Defaults to 250
* @return position - value between 0 and the maximum number of steps.
*         Due to rounding errors when calculating the position, the returned value may not be the same as the set value.
*/
uint16_t get_position(uint8_t channel, uint16_t steps=250);


/**
* Set the pulse length for the lower servo limits. Typically around 1 ms.
* Warning: Setting the pulse limit below 1 ms may damage your servo.
* @param low_limit - Pulse length in milliseconds for the lower limit.
* @param channel - The channel for which the low limit will be set.
*                  If this value is omitted or set to 0 the low limit will be set for all channels., defaults to 0
*/
void set_low_limit(double low_limit, uint8_t channel=0);


/**
* Set the pulse length for the upper servo limits. Typically around 2ms.
* Warning: Setting the pulse limit above 2ms may damage your servo.
* @param high_limit - Pulse length in milliseconds for the upper limit.
* @param channel - The channel for which the upper limit will be set.
                   If this value is omitted or set to 0 the upper limit will be set for all channels., defaults to 0
*/
void set_high_limit(double high_limit, uint8_t channel=0);


/**
* Set the PWM frequency
* @param freq - 40 to 1000
* @param calibration - optional integer value to offset oscillator errors. Defaults to 0
*/
void set_frequency(uint16_t freq, uint8_t calibration=0);


/**
* Disable the output via the OE pin
*/
void output_disable();


/**
* Enable the output via the OE pin
*/
void output_enable();


/**
* Enable pulse offsets.
* This will set servo pulses to be staggered across the channels to reduce surges in the current draw
*/
void offset_enable();


/**
* Disable pulse offsets.
* This will set all servo pulses to start at the same time.
*/
void offset_disable();

/**
* Put the device into a sleep state
*/
void sleep();


/**
* Wake the device from its sleep state
*/
void wake();


/**
* Check the sleep status of the device
* @return true or false
*/
bool is_sleeping();



private:

// Private variables
std::vector <uint16_t> pos {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
std::vector <uint16_t> lowpos {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
std::vector <uint16_t> highpos {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
std::vector <uint16_t> offset {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint16_t frequency = 50;
bool use_offset = false;

// Private methods
static PWM pwm;

/**
 * Private method for refreshing the servo positions
 */
void refresh_channels(); 

/**
 * Private method for calculating the start positions to stagger the servo position pulses
 */
void calculate_offsets();
};
}


#endif /* SERVOPI_ABE_SERVOPI_H_ */