/*
 * servo-output_enable.cpp
 *
 *	Servo class > output_enable function test program 
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

	TestLibs::start_test("Servo class > output_enable()");

	Servo servo(0x40, 1, 2, false, true); // create Servo object

	TestLibs::digitalWrite(7, TestLibs::State::On); // ser the OE output to on

	servo.output_enable();

	TestLibs::test_gpio_state(7, TestLibs::State::Off); // test if the OE output has been set to off
	
	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
