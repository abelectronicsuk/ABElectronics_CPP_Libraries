/*
 * pwm-enable_allcall_address.cpp
 *
 *	PWM class > enable_allcall_address function test program 
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
	TestLibs::start_test("PWM class > enable_allcall_address()");

	PWM pwm(0x40, true); // create PWM object

	pwm.enable_allcall_address(); // change MODE1 register to be 0x01

	TestLibs::test_i2c_register(TestLibs::PCA9685_Mode1, 0x01); // MODE1 expected to be 0x01
		
	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
