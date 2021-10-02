/*
 * pwm-set_address.cpp
 *
 *	PWM class > set_address function test program 
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
	test.start_test("PWM class > set_address()");

	PWM pwm(0x40, true); // create PWM object

	pwm.set_address(0x50); // set the address to 0x50

	uint8_t a = pwm.get_address();

	if (a != 0x50){ // I2C address should be 0x50
		test.test_fail("Unexpected I2C address");
	}
	
	test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}