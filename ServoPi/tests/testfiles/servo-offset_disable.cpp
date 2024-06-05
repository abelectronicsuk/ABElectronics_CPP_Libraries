/*
 * servo-offset_disable.cpp
 *
 *	Servo class > offset_disable function test program 
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

	TestLibs::start_test("Servo class > offset_disable()");

	Servo servo(0x40, 1, 2, false, true); // create Servo object

	uint16_t off_value;
	uint16_t on_value;

	uint8_t low_byte;
	uint8_t high_byte;

	for (uint8_t c = 1; c < 17; c++){
		servo.move(c, 200, 200);

        low_byte = TestLibs::i2c_emulator_read_byte_data(TestLibs::PCA9685_LED0_OFF_Low + 4 * (c - 1));
        high_byte = TestLibs::i2c_emulator_read_byte_data(TestLibs::PCA9685_LED0_OFF_High + 4 * (c - 1));

		off_value = (uint16_t)(low_byte | high_byte << 8); // value should be 409

		low_byte = TestLibs::i2c_emulator_read_byte_data(TestLibs::PCA9685_LED0_ON_Low + 4 * (c - 1));
        high_byte = TestLibs::i2c_emulator_read_byte_data(TestLibs::PCA9685_LED0_ON_High + 4 * (c - 1));

		on_value = (uint16_t)(low_byte | high_byte << 8); // value should be 0

		if (off_value != 409){
			TestLibs::test_fail("Servo.move Off value before offset enabled incorrect");
		}

		if (on_value != 0){
			TestLibs::test_fail("Servo.move On value before offset enabled incorrect");
		}
	}

	servo.offset_enable();

	for (uint8_t c = 1; c < 17; c++){

        low_byte = TestLibs::i2c_emulator_read_byte_data(TestLibs::PCA9685_LED0_OFF_Low + 4 * (c - 1));
        high_byte = TestLibs::i2c_emulator_read_byte_data(TestLibs::PCA9685_LED0_OFF_High + 4 * (c - 1));

		off_value = (uint16_t)(low_byte | high_byte << 8);

        low_byte = TestLibs::i2c_emulator_read_byte_data(TestLibs::PCA9685_LED0_ON_Low + 4 * (c - 1));
        high_byte = TestLibs::i2c_emulator_read_byte_data(TestLibs::PCA9685_LED0_ON_High + 4 * (c - 1));

		on_value = (uint16_t)(low_byte | high_byte << 8);

		// off_value should equal on_value + 409
		if (off_value != (on_value + 409)){
			TestLibs::test_fail("Offset incorrect");
		}
	}

	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
