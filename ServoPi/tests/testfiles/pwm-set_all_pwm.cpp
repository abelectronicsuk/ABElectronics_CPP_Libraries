/*
 * pwm-set_all_pwm.cpp
 *
 *	PWM class > set_all_pwm function test program 
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
	TestLibs::start_test("PWM class > set_all_pwm()");

	PWM pwm(0x40, true); // create PWM object

	// out of bounds test for on_time
	try{
		pwm.set_all_pwm(-1, 1);
		TestLibs::test_exception_failed("on_time low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
		pwm.set_all_pwm(4097, 1);
		TestLibs::test_exception_failed("on_time high out of bounds");
	}
	catch(const std::exception& e){	}

	// out of bounds test for off_time
	try{
		pwm.set_all_pwm(1, -1);
		TestLibs::test_exception_failed("off_time low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
		pwm.set_all_pwm(1, 4097);
		TestLibs::test_exception_failed("off_time high out of bounds");
	}
	catch(const std::exception& e){	}

	pwm.set_all_pwm(0x02d5, 0x0cb7);

	TestLibs::test_i2c_register(TestLibs::PCA9685_All_LED_ON_Low, 0xD5);
	TestLibs::test_i2c_register(TestLibs::PCA9685_All_LED_ON_High, 0x02);

	TestLibs::test_i2c_register(TestLibs::PCA9685_All_LED_OFF_Low, 0xB7);
	TestLibs::test_i2c_register(TestLibs::PCA9685_All_LED_OFF_High, 0x0C);
	
	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}