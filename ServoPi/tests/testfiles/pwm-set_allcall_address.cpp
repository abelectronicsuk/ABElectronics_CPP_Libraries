/*
 * pwm-set_allcall_address.cpp
 *
 *	PWM class > set_allcall_address function test program 
 *
 */

#include <cstdio>
#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ServoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

void clear_screen() {
	printf("\033[2J\033[1;1H");
}

int main(int argc, char **argv) {

	TestLibs::start_test("PWM class > set_allcall_address()");

	PWM pwm(0x40, true); // create PWM object

	// out of bounds test for address register
	try{
	pwm.set_allcall_address(0x39);
	TestLibs::test_exception_failed("All Call I2C address low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
	pwm.set_allcall_address(0x80);
	TestLibs::test_exception_failed("All Call I2C address high out of bounds");
	}
	catch(const std::exception& e){	}

	pwm.set_allcall_address(0x52); // set all call address to 0x52

	TestLibs::test_i2c_register(TestLibs::PCA9685_AllCallAddress, 0xA4); // Check the AllCallAddress register.  Value should be shifted left 1 bit.

	TestLibs::test_i2c_register(TestLibs::PCA9685_Mode1, 0x01); // Check if the ALLCALL bit in Mode1 register is set
	
	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}