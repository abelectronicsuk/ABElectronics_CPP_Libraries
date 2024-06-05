/*
 * servo-output_disable.cpp
 *
 *	Servo class > output_disable function test program 
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

	TestLibs::start_test("Servo class > output_disable()");

	// out of bounds test for address register
	try{
	PWM pwm(0x39, true);
	TestLibs::test_exception_failed("I2C address low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
	PWM pwm(0x80, true);
	TestLibs::test_exception_failed("I2C address high out of bounds");
	}
	catch(const std::exception& e){	}

	Servo servo(0x40, 1, 2, false, true); // create Servo object

	TestLibs::digitalWrite(7, TestLibs::State::Off); // set the OE output to off

	servo.output_disable();

	TestLibs::test_gpio_state(7, TestLibs::State::On); // test if the OE output has been set to on
	
	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
