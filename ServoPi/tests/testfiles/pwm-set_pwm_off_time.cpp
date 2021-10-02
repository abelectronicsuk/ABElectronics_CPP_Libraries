/*
 * pwm-set_pwm_off_time.cpp
 *
 *	PWM class > set_pwm_off_time function test program 
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
	test.start_test("PWM class > set_pwm_off_time()");

	PWM pwm(0x40, true); // create PWM object

	// out of bounds test for channel
	try{
		pwm.set_pwm_off_time(0, 1);
		test.test_exception_failed("Channel low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
		pwm.set_pwm_off_time(17, 1);
		test.test_exception_failed("Channel high out of bounds");
	}
	catch(const std::exception& e){	}

	// out of bounds test for off_time
	try{
		pwm.set_pwm_off_time(1, -1);
		test.test_exception_failed("off_time low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
		pwm.set_pwm_off_time(1, 4096);
		test.test_exception_failed("off_time high out of bounds");
	}
	catch(const std::exception& e){	}

	pwm.set_pwm_off_time(1, 0x0802);

	test.test_i2c_register(test.PCA9685_LED0_OFF_Low, 0x02); // LED0_OFF_High expected to be 0x02
	test.test_i2c_register(test.PCA9685_LED0_OFF_High, 0x08); // LED0_OFF_High expected to be 0x08
	
	pwm.set_pwm_off_time(10, 0x06A4);

	test.test_i2c_register(test.PCA9685_LED0_OFF_Low + 36, 0xA4); // LED9_OFF_High expected to be 0xA4
	test.test_i2c_register(test.PCA9685_LED0_OFF_High + 36, 0x06); // LED9_OFF_High expected to be 0x06

	
	test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}