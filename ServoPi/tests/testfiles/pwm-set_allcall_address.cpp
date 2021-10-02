/*
 * pwm-set_allcall_address.cpp
 *
 *	PWM class > set_allcall_address function test program 
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
	test.start_test("PWM class > set_allcall_address()");

	PWM pwm(0x40, true); // create PWM object

	// out of bounds test for address register
	try{
	pwm.set_allcall_address(0x39);
	test.test_exception_failed("All Call I2C address low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
	pwm.set_allcall_address(0x80);
	test.test_exception_failed("All Call I2C address high out of bounds");
	}
	catch(const std::exception& e){	}

	pwm.set_allcall_address(0x52); // set all call address to 0x52

	test.test_i2c_register(test.PCA9685_AllCallAddress, 0xA4); // Check the AllCallAddress register.  Value should be shifted left 1 bit.

	test.test_i2c_register(test.PCA9685_Mode1, 0x01); // Check if the ALLCALL bit in Mode1 register is set
	
	test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}