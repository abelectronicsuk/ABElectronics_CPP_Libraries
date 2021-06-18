/*
 * servo-output_disable.cpp
 *
 *	Servo class > output_disable function test program 
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
	start_test("Servo class > output_disable()");

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

	Servo servo(0x40, 1, 2, false, true); // create Servo object

	digitalWrite(7, State::Off); // set the OE output to off

	servo.output_disable();

	test_gpio_state(7, State::On); // test if the OE output has been set to on
	
	test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
