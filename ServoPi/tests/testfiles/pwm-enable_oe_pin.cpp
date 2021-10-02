/*
 * pwm-enable_oe_pin.cpp
 *
 *	PWM class > enable_oe_pin function test program 
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
	test.start_test("PWM class > enable_oe_pin()");

	PWM pwm(0x40, true); // create PWM object

	pwm.enable_oe_pin();

	test.test_gpio_direction(7, test.Direction::Output); // GPIO 7 expected to be an output

	test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
