/*
 * pwm-get_address.cpp
 *
 *	PWM class > get_address function test program 
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
	TestLibs::start_test("PWM class > get_address()");

	PWM pwm(0x40, true); // create PWM object

	uint8_t a = pwm.get_address();

	if (a != 0x40){ // I2C address should be 0x40
		TestLibs::test_fail("Unexpected I2C address");
	}
	
	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}