/*
 * pwm-output_disable.cpp
 *
 *	PWM class > output_disable function test program 
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
	start_test("PWM class > output_disable()");

	PWM pwm(0x40, true); // create PWM object

	digitalWrite(7, State::Off); // set the OE output to off

	pwm.output_disable();

	test_gpio_state(7, State::On); // test if the OE output has been set to on
	
	test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}