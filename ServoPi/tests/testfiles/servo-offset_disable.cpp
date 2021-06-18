/*
 * servo-offset_disable.cpp
 *
 *	Servo class > offset_disable function test program 
 *  
 */

#include <stdint.h>
#include <stdio.h>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include "../testlibs.h"
#include "../../ABE_ServoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

void clearscreen() {
	printf("\033[2J\033[1;1H");
}



int main(int argc, char **argv) {
	start_test("Servo class > offset_disable()");

	Servo servo(0x40, 1, 2, false, true); // create Servo object

	uint16_t off_value = 0;
	uint16_t on_value = 0;

	uint8_t lowbyte = 0;
	uint8_t highbyte = 0;

	for (uint8_t c = 1; c < 17; c++){
		servo.move(c, 200, 200);

		lowbyte = i2c_emulator_read_byte_data(PCA9685::LED0_OFF_Low + 4 * (c - 1));
		highbyte = i2c_emulator_read_byte_data(PCA9685::LED0_OFF_High + 4 * (c - 1));

		off_value = (uint16_t)(lowbyte | highbyte << 8); // value should be 409

		lowbyte = i2c_emulator_read_byte_data(PCA9685::LED0_ON_Low + 4 * (c - 1));
		highbyte = i2c_emulator_read_byte_data(PCA9685::LED0_ON_High + 4 * (c - 1));

		on_value = (uint16_t)(lowbyte | highbyte << 8); // value should be 0

		if (off_value != 409){
			test_fail("Servo.move Off value before offset enabled incorrect");
		}

		if (on_value != 0){
			test_fail("Servo.move On value before offset enabled incorrect");
		}
	}

	servo.offset_enable();

	on_value = 0;

	for (uint8_t c = 1; c < 17; c++){

		lowbyte = i2c_emulator_read_byte_data(PCA9685::LED0_OFF_Low + 4 * (c - 1));
		highbyte = i2c_emulator_read_byte_data(PCA9685::LED0_OFF_High + 4 * (c - 1));

		off_value = (uint16_t)(lowbyte | highbyte << 8);

		lowbyte = i2c_emulator_read_byte_data(PCA9685::LED0_ON_Low + 4 * (c - 1));
		highbyte = i2c_emulator_read_byte_data(PCA9685::LED0_ON_High + 4 * (c - 1));

		on_value = (uint16_t)(lowbyte | highbyte << 8);

		// off_value should equal on_value + 409
		if (off_value != (on_value + 409)){
			test_fail("Offset incorrect");
		}
	}

	test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
