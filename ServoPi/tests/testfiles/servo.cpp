/*
 * servo.cpp
 *
 *	Servo class test program 
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
	test.start_test("Servo class > servo()");

	// out of bounds test for address register
	
	try{
	Servo servo1(0x39, 1, 2, false, false);
	test.test_exception_failed("I2C address low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
	Servo servo2(0x80, 1, 2, false, false);
	test.test_exception_failed("I2C address high out of bounds");
	}
	catch(const std::exception& e){	}

	

	Servo servo(0x40, 1, 2, false, true);
		
	test.test_i2c_register(test.PCA9685_Mode1, 0x00); // MODE1 expected to be 0x00
	test.test_i2c_register(test.PCA9685_Mode2, 0x0C); // MODE2 expected to be 0x0C

	Servo servo2(0x40, 1, 2, true, true); // enable device reset
	
	test.test_i2c_register(test.PCA9685_Mode1, 0x80); // MODE1 expected to be 0x80
	test.test_i2c_register(test.PCA9685_Mode2, 0x0C); // MODE2 expected to be 0x0C

	test.test_gpio_direction(7, test.Output); // GPIO 7 expected to be an output

	test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
