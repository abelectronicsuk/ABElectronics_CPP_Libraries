/*
 * pwm-output_disable.cpp
 *
 *	PWM class > output_disable function test program 
 *
 */

#include <cstdio>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ServoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

void clear_screen() {
	printf("\033[2J\033[1;1H");
}

int main(int argc, char **argv) {
	TestLibs::start_test("PWM class > output_disable()");

	PWM pwm(0x40, true); // create PWM object

	TestLibs::digitalWrite(7, TestLibs::State::Off); // set the OE output to off

	pwm.output_disable();

	TestLibs::test_gpio_state(7, TestLibs::State::On); // test if the OE output has been set to on
	
	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}