/*
 * pwm.cpp
 *
 *	PWM class test program 
 *
 *  compile with "g++ pwm.cpp ../testlibs.cpp ../../ABE_ServoPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o pwm -L/usr/local/lib "
 *  run with "./pwm"
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
	start_test("PWM class > pwm()");

	// out of bounds test for address register
	try{
	PWM pwm(0x39, true);
	test_exception_failed("I2C address low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
	PWM pwm(0x80, true);
	test_exception_failed("I2C address high out of bounds");
	}
	catch(const std::exception& e){	}

	PWM pwm(0x40, true); // create PWM object

	test_i2c_register(PCA9685::Mode1, 0x00); // MODE1 expected to be 0x00
	test_i2c_register(PCA9685::Mode2, 0x0C); // MODE2 expected to be 0x0C

	test_gpio_direction(7, Direction::Output); // GPIO 7 expected to be an output

	test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
