/*
 * pwm-set_pwm.cpp
 *
 *	PWM class > set_pwm function test program 
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

	TestLibs::start_test("PWM class > set_pwm()");

	PWM pwm(0x40, true); // create PWM object

	// out of bounds test for channel
	try{
		pwm.set_pwm(0, 1, 1);
		TestLibs::test_exception_failed("Channel low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
		pwm.set_pwm(17, 1, 1);
		TestLibs::test_exception_failed("Channel high out of bounds");
	}
	catch(const std::exception& e){	}

	// out of bounds test for on_time
	try{
		pwm.set_pwm(1, -1, 1);
		TestLibs::test_exception_failed("on_time low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
		pwm.set_pwm(1, 4096, 1);
		TestLibs::test_exception_failed("on_time high out of bounds");
	}
	catch(const std::exception& e){	}

	// out of bounds test for off_time
	try{
		pwm.set_pwm(1, 1, -1);
		TestLibs::test_exception_failed("off_time low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
		pwm.set_pwm(1, 1, 4096);
		TestLibs::test_exception_failed("off_time high out of bounds");
	}
	catch(const std::exception& e){	}

	pwm.set_pwm(1, 0x0160, 0x0DC1);

	TestLibs::test_i2c_register(TestLibs::PCA9685_LED0_ON_Low, 0x60); // LED0_ON_High expected to be 0x60
	TestLibs::test_i2c_register(TestLibs::PCA9685_LED0_ON_High, 0x01); // LED0_ON_High expected to be 0x01

	TestLibs::test_i2c_register(TestLibs::PCA9685_LED0_OFF_Low, 0xC1); // LED0_OFF_High expected to be 0xC1
	TestLibs::test_i2c_register(TestLibs::PCA9685_LED0_OFF_High, 0x0D); // LED0_OFF_High expected to be 0x0D
	
	pwm.set_pwm(10, 0x0285, 0x0F72);

	TestLibs::test_i2c_register(TestLibs::PCA9685_LED0_ON_Low + 36, 0x85); // LED9_ON_High expected to be 0x85
	TestLibs::test_i2c_register(TestLibs::PCA9685_LED0_ON_High + 36, 0x02); // LED9_ON_High expected to be 0x02

	TestLibs::test_i2c_register(TestLibs::PCA9685_LED0_OFF_Low + 36, 0x72); // LED9_OFF_High expected to be 0x72
	TestLibs::test_i2c_register(TestLibs::PCA9685_LED0_OFF_High + 36, 0x0F); // LED9_OFF_High expected to be 0x0F

	
	
	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}