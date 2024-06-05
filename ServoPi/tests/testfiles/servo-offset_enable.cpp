/*
 * servo-offset_enable.cpp
 *
 *	Servo class > offset_enable function test program 
 *  
 */

#include <cstdint>
#include <cstdio>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ServoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

void clear_screen() {
	printf("\033[2J\033[1;1H");
}



int main(int argc, char **argv) {

	TestLibs::start_test("Servo class > offset_enable()");

		Servo servo(0x40, 1, 2, false, true); // create Servo object

	uint16_t off_value;
	uint16_t on_value;

	uint8_t low_byte;
	uint8_t high_byte;

	for (uint8_t c = 1; c < 17; c++){
		servo.move(c, 200, 200); // set servo position for each channel
	}

	servo.offset_enable(); // enable the servo offset

	servo.offset_disable(); // disable the servo offset

	for (uint8_t c = 1; c < 17; c++){

        low_byte = TestLibs::i2c_emulator_read_byte_data(TestLibs::PCA9685_LED0_OFF_Low + 4 * (c - 1));
        high_byte = TestLibs::i2c_emulator_read_byte_data(TestLibs::PCA9685_LED0_OFF_High + 4 * (c - 1));

		off_value = (uint16_t)(low_byte | high_byte << 8);

        low_byte = TestLibs::i2c_emulator_read_byte_data(TestLibs::PCA9685_LED0_ON_Low + 4 * (c - 1));
        high_byte = TestLibs::i2c_emulator_read_byte_data(TestLibs::PCA9685_LED0_ON_High + 4 * (c - 1));

		on_value = (uint16_t)(low_byte | high_byte << 8);

		// off_value expected to be 409, on_value expected to be 0

		if (off_value != 409){
			TestLibs::test_fail("off_value offset incorrect");
		}

		if (on_value != 0){
			TestLibs::test_fail("on_value offset incorrect");
		}
	}

	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
