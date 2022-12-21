/*
================================================
AB Electronics UK Servo Pi 16-Channel PWM Servo Controller
See CHANGELOG.md for the version number.
================================================

Note:  From version 1.1.3 the ServoPi class is called PWM.

Required packages: i2c-dev and wiringPi
apt-get install libi2c-dev wiringpi
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
#include <math.h>
#include <vector>
#include <unistd.h>
#include <iostream>

#ifdef TESTMODE
	#include "../UnitTest/testlibs.h"
#else
	#include <wiringPi.h>
#endif
#include "ABE_ServoPi.h"

#define fileName "/dev/i2c-1"  // change to /dev/i2c-0 if you are using a revision 0002 or 0003 model B

// Define registers values from the datasheet
#define MODE1 0x00
#define MODE2 0x01
#define SUBADR1 0x02
#define SUBADR2 0x03
#define SUBADR3 0x04
#define ALLCALLADR 0x05
#define LED0_ON_L 0x06
#define LED0_ON_H 0x07
#define LED0_OFF_L 0x08
#define LED0_OFF_H 0x09
#define ALL_LED_ON_L 0xFA
#define ALL_LED_ON_H 0xFB
#define ALL_LED_OFF_L 0xFC
#define ALL_LED_OFF_H 0xFD
#define PRE_SCALE 0xFE

// default values for config registers
#define MODE1_DEFAULT 0x00
#define MODE2_DEFAULT 0x0C

// define mode bits
#define MODE1_EXTCLK 6 // use external clock
#define MODE1_SLEEP 4 // sleep mode
#define MODE1_ALLCALL 0 // all call address

#define MODE2_INVRT 4 // invert output
#define MODE2_OCH 3 // output type
#define MODE2_OUTDRV 2 // output type
#define MODE2_OUTNE1 0 // output mode when not enabled

// values used for I2C and GPIO communication
#define OUT 1
#define IN 0
#define LOW 0
#define HIGH 1
#define VALUE_MAX 30
#define BUFFER_MAX 3
#define DIRECTION_MAX 35

// Output enable pin.  Change this if you connect the GPIO pin to something other than Wiring Pi pin 7
#define ENABLE_PIN 7

using namespace ABElectronics_CPP_Libraries;

// public PWM methods

PWM::PWM(uint8_t address, bool use_oe_pin)
{
	/**
	* Initialise the Servo Pi - run before calling any other methods
	* @param address - I2C address. Defaults to 0x40
	* @param use_oe_pin - Enable the Output Enable pin on the GPIO port.  Defaults to false.
	*/

	set_address(address);

	// Update control registers
	write_byte_data(MODE1, MODE1_DEFAULT);
	write_byte_data(MODE2, MODE2_DEFAULT);

	// set the GPIO pin as an output for the Output Enable Pin if use_oe_pin = 1

	if (use_oe_pin)
	{
		oe_pin_enabled = true;
		enable_oe_pin();
	}
}

void PWM::set_pwm_freq(double freq, uint8_t calibration)
{
	/**
	* Set the PWM frequency
	* @param freq - 40 to 1000
	* @param calibration - optional integer value to offset oscillator errors. Defaults to 0
	*/
	if (freq < 40 || freq > 1000){
		throw std::out_of_range("set_pwm_freq: freq out of range: 40 to 1000");
	}

	double scaleval = ((25000000 / 4096) / freq) - 0.5; // 25MHz
	uint8_t prescale = (uint8_t)floor(scaleval);
	prescale+= calibration;
	uint8_t oldmode = read_byte_data((uint8_t)MODE1);
	uint8_t newmode = (oldmode & 0x7F) | 0x10;

	write_byte_data((uint8_t)MODE1, newmode); // enable sleep mode
	write_byte_data((uint8_t)PRE_SCALE, prescale); // update prescale register
	write_byte_data((uint8_t)MODE1, oldmode); // disable sleep mode
	write_byte_data((uint8_t)MODE1, oldmode | (uint8_t)0x80); // restart
}

void PWM::set_pwm(uint8_t channel, uint16_t on_time, uint16_t off_time)
{
	/**
	* Set the output on a single channel
	* @param channel - 1 to 16
	* @param on_time - time period 0 to 4095
	* @param off_time - time period 0 to 4095
	*/

	if (channel < 1 || channel > 16){
			throw std::out_of_range("set_pwm: channel out of range");
	}

    if (on_time > 4095){
			throw std::out_of_range("set_pwm: on_time out of range");
	}

    if (off_time > 4095){
			throw std::out_of_range("set_pwm: off_time out of range");
	}

    if (on_time > off_time){
			throw std::out_of_range("set_pwm: on_time greater than off_time");
	}

	channel -= 1;
	write_byte_data((uint8_t)(LED0_ON_L + 4 * channel), (uint8_t)(on_time & 0xFF));
	write_byte_data((uint8_t)(LED0_ON_H + 4 * channel), (uint8_t)(on_time >> 8));
	write_byte_data((uint8_t)(LED0_OFF_L + 4 * channel), (uint8_t)(off_time & 0xFF));
	write_byte_data((uint8_t)(LED0_OFF_H + 4 * channel), (uint8_t)(off_time >> 8));
}

void PWM::set_pwm_on_time(uint8_t channel, uint16_t on_time)
{
	/**
	* Set the output on time on a single channel
	* @param channel - 1 to 16
	* @param on_time - time period 0 to 4095
	*/
	if (channel < 1 || channel > 16){
			throw std::out_of_range("set_pwm_on_time: channel out of range");
	}

    if (on_time > 4095){
			throw std::out_of_range("set_pwm_on_time: on_time out of range");
	}

	channel -= 1;
	write_byte_data((uint8_t)(LED0_ON_L + 4 * channel), (uint8_t)(on_time & 0xFF));
	write_byte_data((uint8_t)(LED0_ON_H + 4 * channel), (uint8_t)(on_time >> 8));
}

void PWM::set_pwm_off_time(uint8_t channel, uint16_t off_time)
{
	/**
	* Set the output off time on a single channel
	* @param channel - 1 to 16
	* @param off_time - time period 0 to 4095
	*/

	if (channel < 1 || channel > 16){
			throw std::out_of_range("set_pwm_off_time: channel out of range");
	}

    if (off_time > 4095){
			throw std::out_of_range("set_pwm_off_time: off_time out of range");
	}

	channel -= 1;
	write_byte_data((uint8_t)(LED0_OFF_L + 4 * channel), (uint8_t)(off_time & 0xFF));
	write_byte_data((uint8_t)(LED0_OFF_H + 4 * channel), (uint8_t)(off_time >> 8));
}

uint16_t PWM::get_pwm_on_time(uint8_t channel)
{
	/**
	* Get the output on time on a single channel
	* @param channel - 1 to 16
	* @return (uint16_t) on time
	*/
	if (channel < 1 || channel > 16){
			throw std::out_of_range("get_pwm_on_time: channel out of range");
	}

	channel = channel - 1;
    uint8_t lowbyte = read_byte_data(LED0_ON_L + 4 * channel);
    uint8_t highbyte = read_byte_data(LED0_ON_H + 4 * channel);
    return (uint16_t)(lowbyte | highbyte << 8);
}

uint16_t PWM::get_pwm_off_time(uint8_t channel)
{
	/**
	* Get the output off time on a single channel
	* @param channel - 1 to 16
	* @return (uint16_t) off time
	*/
	if (channel < 1 || channel > 16){
			throw std::out_of_range("get_pwm_off_time: channel out of range");
	}

	channel = channel - 1;
    uint8_t lowbyte = read_byte_data(LED0_OFF_L + 4 * channel);
    uint8_t highbyte = read_byte_data(LED0_OFF_H + 4 * channel);
    return (uint16_t)(lowbyte | highbyte << 8);
}

void PWM::set_all_pwm(uint16_t on_time, uint16_t off_time)
{
	/**
	* Set the output on all channels
	* @param on_time - time period 0 to 4095
	* @param off_time - time period 0 to 4095
	*/

	if (on_time > 4095){
			throw std::out_of_range("set_all_pwm: on_time out of range");
	}

    if (off_time > 4095){
			throw std::out_of_range("set_all_pwm: off_time out of range");
	}

    if ((on_time + off_time) > 4095){
			throw std::out_of_range("set_all_pwm: on_time + off_time must not exceed 4095");
	}

	write_byte_data((uint8_t)ALL_LED_ON_L, (uint8_t)(on_time & 0xFF));
	write_byte_data((uint8_t)ALL_LED_ON_H, (uint8_t)(on_time >> 8));
	write_byte_data((uint8_t)ALL_LED_OFF_L, (uint8_t)(off_time & 0xFF));
	write_byte_data((uint8_t)ALL_LED_OFF_H, (uint8_t)(off_time >> 8));
}

void PWM::output_disable()
{
	/**
	* Disable the output via the OE pin
	*/
	if (oe_pin_enabled) {
        #ifdef TESTMODE
        TestLibs test;
		test.digitalWrite(ENABLE_PIN, 1);
        #else
            digitalWrite(ENABLE_PIN, 1);
        #endif
	}
	else{
		throw std::runtime_error("output_disable: Attempted to set output state when OE pin is disabled.");
	}
}

void PWM::output_enable()
{
	/**
	* Enable the output via the OE pin
	*/
	if (oe_pin_enabled) {
		#ifdef TESTMODE
        TestLibs test;
		test.digitalWrite(ENABLE_PIN, 0);
        #else
            digitalWrite(ENABLE_PIN, 0);
        #endif
	}
	else{
		throw std::runtime_error("output_enable: Attempted to set output state when OE pin is enabled.");
	}
}

void PWM::set_allcall_address(uint8_t allcalladdress)
{
	/**
	* Set the I2C address for the All Call function
	* @param allcalladdress - I2C address 0x40 to 0x7F
	*/

	if (allcalladdress < 0x40 || allcalladdress > 0x7F){
			throw std::out_of_range("set_allcall_address: i2c address out of range 0x40 to 0x7F");
	}

	uint8_t oldmode = read_byte_data(MODE1);
	uint8_t newmode = oldmode | (1 << MODE1_ALLCALL);
	write_byte_data((uint8_t)MODE1, newmode);
	write_byte_data((uint8_t)ALLCALLADR, allcalladdress << 1);
}

void PWM::enable_allcall_address()
{
	/**
	* Enable the I2C address for the All Call function
	*/
	uint8_t oldmode = read_byte_data(MODE1);
	uint8_t newmode = oldmode | (1 << MODE1_ALLCALL);
	write_byte_data((uint8_t)MODE1, newmode);
}

void PWM::disable_allcall_address()
{
	/**
	* Disable the I2C address for the All Call function
	*/
	uint8_t oldmode = read_byte_data(MODE1);
	uint8_t newmode = oldmode & ~(1 << MODE1_ALLCALL);
	write_byte_data((uint8_t)MODE1, newmode);
}

void PWM::sleep()
{
	/**
	* Put the device into a sleep state
	*/
	uint8_t oldmode = read_byte_data(MODE1);
    uint8_t newmode = oldmode | (1 << MODE1_SLEEP);
    write_byte_data((uint8_t)MODE1, newmode);
}

void PWM::wake()
{
	/**
	* Wake the device from its sleep state
	*/
	uint8_t oldmode = read_byte_data(MODE1);
    uint8_t newmode = oldmode & ~(1 << MODE1_SLEEP);
    write_byte_data((uint8_t)MODE1, newmode);
}

bool PWM::is_sleeping()
{
	/**
	* Check the sleep status of the device
	* @return true or false
	*/
	if (read_byte_data(MODE1) & (1 << MODE1_SLEEP))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void PWM::invert_output(bool state)
{
	/**
	* Invert the PWM output on all channels
	* @param true = inverted, false = non-inverted
	*/
	if (state){
		uint8_t oldmode = read_byte_data(MODE2);
    	uint8_t newmode = oldmode | (1 << MODE2_INVRT);
    	write_byte_data((uint8_t)MODE2, newmode);
	}
    else{
		uint8_t oldmode = read_byte_data(MODE2);
    	uint8_t newmode = oldmode & ~(1 << MODE2_INVRT);
    	write_byte_data((uint8_t)MODE2, newmode);
	}
}

void PWM::set_address(uint8_t address){
	/**
	* Set the I2C address
	* @param address = i2c address
	*/
	if (address < 0x40 || address > 0x7F){
			throw std::out_of_range("set_address: i2c address out of range 0x40 to 0x7F");
	}

	i2caddress = address;
}

uint8_t PWM::get_address(){
	/**
	* Get the I2C address
	* @return i2c address
	*/
	return i2caddress;
}


void PWM::enable_oe_pin(){
	/**
	* Enable the Output Enable Pin on the GPIO header
	*/
    #ifdef TESTMODE
        TestLibs test;
        if (test.wiringPiSetup() == -1)
            throw std::runtime_error("Error setting up GPIO pin");
        oe_pin_enabled = true;
        test.pinMode(ENABLE_PIN, test.Direction::Output);
    #else
        if (wiringPiSetup() == -1)
		    throw std::runtime_error("Error setting up GPIO pin");
        oe_pin_enabled = true;
        pinMode(ENABLE_PIN, OUTPUT);
    #endif
}

// Private PWM methods

// Stops file handle leakage on exceptions
class ScopedFileHandle
{
public:
	ScopedFileHandle(int fd) : _fd(fd) {}
	~ScopedFileHandle()
	{
		if (_fd >= 0)
			close(_fd);
	}
	operator int() const { return _fd; }

private:
	int _fd;
};

uint8_t PWM::read_byte_data(uint8_t reg)
{
	/*
	Private method for reading data from the i2c bus
	*/

	#ifdef TESTMODE		
        TestLibs test;		
		buf[0] = test.i2c_emulator_read_byte_data(reg);
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

	buf[0] = reg;

	if ((write(i2cbus, buf, 1)) != 1)
	{
		throw std::runtime_error("read_byte_data: Failed to write to i2c device for read");
	}

	if (read(i2cbus, buf, 1) != 1)
	{ // Read back data into buf[]
		throw std::runtime_error("read_byte_data: Failed to read from slave");
	}

	close(i2cbus);

	#endif

	return (buf[0]);
}

void PWM::write_byte_data(uint8_t reg, uint8_t value)
{
	/**
	* Private method for writing a byte to the I2C port
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

	if (ioctl(i2cbus, I2C_SLAVE, i2caddress) < 0)
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


// Public Servo Methods
/**
 * Servo class for controlling analogue RC servos with the Servo PWM Pi Zero
 */

Servo::Servo(uint8_t address, double low_limit, double high_limit, bool reset, bool use_oe_pin)
{
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

	if (use_oe_pin){
		pwm.enable_oe_pin();
	}

	if (address < 0x40 || address > 0x7F){
		throw std::out_of_range("Servo: i2c address out of range 0x40 to 0x7F");
	}
	else{
		pwm.set_address(address);
	}

    set_low_limit(low_limit);
    set_high_limit(high_limit);

    if (reset){
        set_frequency(50);
        calculate_offsets(); // reset the offset values
	}
    else{
		// get the on and off times from the PWM controller
		for (uint8_t i = 0; i < 16; i++){
			offset[i] = pwm.get_pwm_on_time(i + 1);
			pos[i] = pwm.get_pwm_off_time(i + 1) - offset[i];
		}
	}
}

void Servo::move(uint8_t channel, uint16_t position, uint16_t steps)
{
	/**
	* Set the servo position
	* @param channel - 1 to 16
	* @param position - value between 0 and the maximum number of steps.
	* @param steps - The number of steps between the low and high limits.
	*                This can be any number between 1 and 4095.
	*                On a typical RC servo a step value of 250 is recommended.
	*                Defaults to 250
	*/

	if (channel < 1 || channel > 16){
			throw std::out_of_range("move: channel out of range");
	}

    if (steps < 1 || steps > 4095){
			throw std::out_of_range("move: steps out of range");
	}

	if (position > steps){
			throw std::out_of_range("move: position greater than steps");
	}

	uint16_t high = highpos[channel - 1];
    uint16_t low = lowpos[channel - 1];
	
	uint16_t pwm_value = uint16_t((((high - low) / double(steps)) * double(position)) + low);

    pos[channel - 1] = pwm_value;

	if (use_offset){
		pwm.set_pwm(channel, offset[channel - 1], pwm_value + offset[channel - 1]);
	}
	else{
		pwm.set_pwm(channel, 0, pwm_value);
	}
}

uint16_t Servo::get_position(uint8_t channel, uint16_t steps)
{
	/**
	* Get the servo position
	* @param channel - 1 to 16
	* @param steps - The number of steps between the low and high limits.
	*                This can be any number between 1 and 4095.
	*                On a typical RC servo a step value of 250 is recommended.
	*                Defaults to 250
	* @return position - value between 0 and the maximum number of steps.
	*         Due to rounding errors when calculating the position, the returned value may not be the same as the set value.
	*/
	if (channel < 1 || channel > 16){
			throw std::out_of_range("get_position: channel out of range");
	}

	if (steps < 1 || steps > 4095){
			throw std::out_of_range("get_position: steps out of range");
	}

	uint16_t pwm_value = uint16_t(pwm.get_pwm_off_time(channel));

	if (use_offset){
		pwm_value = pwm_value - offset[channel - 1];
	}

    return uint16_t(ceil((steps * (pwm_value - lowpos[channel - 1])) / (highpos[channel - 1] - lowpos[channel - 1])));
}

void Servo::set_low_limit(double low_limit, uint8_t channel)
{
	/**
	* Set the pulse length for the lower servo limits. Typically around 1 ms.
	* Warning: Setting the pulse limit below 1 ms may damage your servo.
	* @param low_limit - Pulse length in milliseconds for the lower limit.
	* @param channel - The channel for which the low limit will be set.
	*                  If this value is omitted or set to 0 the low limit will be set for all channels., defaults to 0
	*/

	if (channel > 16){
			throw std::out_of_range("set_low_limit: channel out of range");
	}

	uint16_t pos = uint16_t(4096.0 * (low_limit / 1000.0) * frequency);

	if (pos > 4095){
		throw std::out_of_range("set_low_limit: pulse time to high for the current frequency");
	}

	if (channel > 0){
		// update the specified channel
		lowpos[channel - 1] = pos;
	}
	else{
		// no channel specified so update all channels
		for (uint8_t i = 0; i < 16; i++){
			lowpos[i] = pos;
		}
	}
}

void Servo::set_high_limit(double high_limit, uint8_t channel)
{
	/**
	* Set the pulse length for the upper servo limits. Typically around 2ms.
	* Warning: Setting the pulse limit above 2ms may damage your servo.
	* @param high_limit - Pulse length in milliseconds for the upper limit.
	* @param channel - The channel for which the upper limit will be set.
                   If this value is omitted or set to 0 the upper limit will be set for all channels., defaults to 0
	*/

	if (channel > 16){
			throw std::out_of_range("set_high_limit: channel out of range");
	}

	uint16_t pos = uint16_t(4096.0 * (high_limit / 1000.0) * frequency);

	if (pos > 4095){
		throw std::out_of_range("set_high_limit: pulse time to high for the current frequency");
	}

	if (channel > 0){
		// update the specified channel
		highpos[channel - 1] = pos;
	}
	else{
		// no channel specified so update all channels
		for (uint8_t i = 0; i < 16; i++){
			highpos[i] = pos;
		}
	}
}

void Servo::set_frequency(uint16_t freq, uint8_t calibration)
{
	/**
	* Set the PWM frequency
	* @param freq - 40 to 1000
	* @param calibration - optional integer value to offset oscillator errors. Defaults to 0
	*/
	pwm.set_pwm_freq(freq, calibration);
	frequency = freq;
}

void Servo::output_disable()
{
	/**
	* Disable the output via the OE pin
	*/
	pwm.output_disable();
}

void Servo::output_enable()
{
	/**
	* Enable the output via the OE pin
	*/
	pwm.output_enable();
	calculate_offsets();
}

void Servo::offset_enable()
{
	/**
	* Enable pulse offsets.
	* This will set servo pulses to be staggered across the channels to reduce surges in the current draw
	*/
	use_offset = true;
	calculate_offsets();
}

void Servo::offset_disable()
{
	/**
	* Disable pulse offsets.
	* This will set all servo pulses to start at the same time.
	*/
	use_offset = false;
	refresh_channels();
}

void Servo::sleep()
{
	/**
	* Put the device into a sleep state
	*/
	pwm.sleep();
}

void Servo::wake()
{
	/**
	* Wake the device from its sleep state
	*/
	pwm.wake();
}

bool Servo::is_sleeping()
{
	/**
	* Check the sleep status of the device
	* @return true or false
	*/
	return pwm.is_sleeping();
}

// Private Servo Methods
PWM Servo::pwm(0x40, false);

void Servo::refresh_channels()
{
	/**
 	* Private method for refreshing the servo positions
 	*/
 	for (uint8_t i = 0; i < 16; i++){
		if (pos[i] == 0){
			pwm.set_pwm(i + 1, 0, 0);
		}
		else{
			if (use_offset){
				pwm.set_pwm(i + 1, offset[i], pos[i] + offset[i]);
			}
			else{
				pwm.set_pwm(i + 1, 0, pos[i]);
			}
		}
	}
}

void Servo::calculate_offsets()
{
	/**
	* Private method for calculating the start positions to stagger the servo position pulses
 	*/
 	uint16_t x = 0;
    for (uint8_t i = 0; i < 16; i++){
		offset[i] = x;
		x = x + highpos[i];
		if (x > 4095 - highpos[i]){
			x = highpos[0] / 2;			
		}
		
		refresh_channels();
	}
}