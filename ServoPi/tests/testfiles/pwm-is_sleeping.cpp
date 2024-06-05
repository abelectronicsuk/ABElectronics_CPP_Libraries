/*
 * pwm-is_sleeping.cpp
 *
 *	PWM class > is_sleeping function test program 
 *
 */

#include <cstdio>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ServoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

void clear_screen() {
	printf("\033[2J\033[1;1H");
}

int main(int argc, char **argv) {
	TestLibs::start_test("PWM class > is_sleeping()");

	PWM pwm(0x40, true); // create PWM object

	bool a = pwm.is_sleeping(); // Value should be false when MODE1 is 0x00

	if (a){
		TestLibs::test_fail("Unexpected output for is_sleeping()");
	}

	TestLibs::i2c_emulator_write_byte_data(TestLibs::PCA9685_Mode1, 0x10); // update sleep bit to 1
	
	a = pwm.is_sleeping(); // Value should be false when MODE1 is 0x00

	if (!a){
		TestLibs::test_fail("Unexpected output for is_sleeping()");
	}
	
	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}