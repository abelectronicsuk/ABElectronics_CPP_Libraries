/*
 * pwm-set_pwm_on_time.cpp
 *
 *	PWM class > set_pwm_on_time function test program 
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include "../testlibs.h"
#include "../../ABE_ServoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

void clearscreen() {
	printf("\033[2J\033[1;1H");
}

int main(int argc, char **argv) {
	start_test("PWM class > set_pwm_on_time()");

	PWM pwm(0x40, true); // create PWM object

	// out of bounds test for channel
	try{
		pwm.set_pwm_on_time(0, 1);
		test_exception_failed("Channel low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
		pwm.set_pwm_on_time(17, 1);
		test_exception_failed("Channel high out of bounds");
	}
	catch(const std::exception& e){	}

	// out of bounds test for off_time
	try{
		pwm.set_pwm_on_time(1, -1);
		test_exception_failed("on_time low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
		pwm.set_pwm_on_time(1, 4096);
		test_exception_failed("on_time high out of bounds");
	}
	catch(const std::exception& e){	}

	pwm.set_pwm_on_time(1, 0x0802);

	test_i2c_register(PCA9685::LED0_ON_Low, 0x02); // LED0_ON_High expected to be 0x02
	test_i2c_register(PCA9685::LED0_ON_High, 0x08); // LED0_ON_High expected to be 0x08
	
	pwm.set_pwm_on_time(10, 0x06A4);

	test_i2c_register(PCA9685::LED0_ON_Low + 36, 0xA4); // LED9_ON_High expected to be 0xA4
	test_i2c_register(PCA9685::LED0_ON_High + 36, 0x06); // LED9_ON_High expected to be 0x06
	
	test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}