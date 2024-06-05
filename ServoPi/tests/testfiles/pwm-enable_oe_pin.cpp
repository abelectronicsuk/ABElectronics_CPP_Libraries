/*
 * pwm-enable_oe_pin.cpp
 *
 *	PWM class > enable_oe_pin function test program 
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
	TestLibs::start_test("PWM class > enable_oe_pin()");

	PWM pwm(0x40, true); // create PWM object

	pwm.enable_oe_pin();

	TestLibs::test_gpio_direction(7, TestLibs::Direction::Output); // GPIO 7 expected to be an output

	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
