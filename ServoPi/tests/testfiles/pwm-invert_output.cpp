/*
 * pwm-invert_output.cpp
 *
 *	PWM class > invert_output function test program 
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
	TestLibs::start_test("PWM class > invert_output()");

	PWM pwm(0x40, true); // create PWM object

	pwm.invert_output(true);

	TestLibs::test_i2c_register(TestLibs::PCA9685_Mode2, 0x1C); // MODE2 expected to be 0x1C

	pwm.invert_output(false);

	TestLibs::test_i2c_register(TestLibs::PCA9685_Mode2, 0x0C); // MODE2 expected to be 0x0C
	
	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}