/*
 * pwm-sleep.cpp
 *
 *	PWM class > sleep function test program 
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

	TestLibs::start_test("PWM class > sleep()");

	PWM pwm(0x40, true); // create PWM object

	pwm.sleep();

	TestLibs::test_i2c_register(TestLibs::PCA9685_Mode1, 0x10); // MODE1 expected to be 0x10
	
	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}