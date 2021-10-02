/*
 * servo-offset_enable.cpp
 *
 *	Servo class > offset_enable function test program 
 *  
 */

#include <stdint.h>
#include <stdio.h>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ServoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

void clearscreen() {
	printf("\033[2J\033[1;1H");
}



int main(int argc, char **argv) {
    TestLibs test;
	test.start_test("Servo class > offset_enable()");

		Servo servo(0x40, 1, 2, false, true); // create Servo object

	uint16_t off_value = 0;
	uint16_t on_value = 0;

	uint8_t lowbyte = 0;
	uint8_t highbyte = 0;

	for (uint8_t c = 1; c < 17; c++){
		servo.move(c, 200, 200); // set servo position for each channel
	}

	servo.offset_enable(); // enable the servo offset

	servo.offset_disable(); // disable the servo offset

	for (uint8_t c = 1; c < 17; c++){

		lowbyte = test.i2c_emulator_read_byte_data(test.PCA9685_LED0_OFF_Low + 4 * (c - 1));
		highbyte = test.i2c_emulator_read_byte_data(test.PCA9685_LED0_OFF_High + 4 * (c - 1));

		off_value = (uint16_t)(lowbyte | highbyte << 8);

		lowbyte = test.i2c_emulator_read_byte_data(test.PCA9685_LED0_ON_Low + 4 * (c - 1));
		highbyte = test.i2c_emulator_read_byte_data(test.PCA9685_LED0_ON_High + 4 * (c - 1));

		on_value = (uint16_t)(lowbyte | highbyte << 8);

		// off_value expected to be 409, on_value expected to be 0

		if (off_value != 409){
			test.test_fail("off_value offset incorrect");
		}

		if (on_value != 0){
			test.test_fail("on_value offset incorrect");
		}
	}

	test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
