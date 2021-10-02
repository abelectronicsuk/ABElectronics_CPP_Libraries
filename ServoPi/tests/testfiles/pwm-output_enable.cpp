/*
 * pwm-output_enable.cpp
 *
 *	PWM class > output_enable function test program 
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
	test.start_test("PWM class > output_enable()");

	PWM pwm(0x40, true); // create PWM object

	test.digitalWrite(7, test.State::On); // ser the OE output to on

	pwm.output_enable();

	test.test_gpio_state(7, test.State::Off); // test if the OE output has been set to off
	
	test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}