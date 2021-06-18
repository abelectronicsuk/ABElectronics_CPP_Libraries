/*
 * servo-output_enable.cpp
 *
 *	Servo class > output_enable function test program 
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
	start_test("Servo class > output_enable()");

	Servo servo(0x40, 1, 2, false, true); // create Servo object

	digitalWrite(7, State::On); // ser the OE output to on

	servo.output_enable();

	test_gpio_state(7, State::Off); // test if the OE output has been set to off
	
	test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
