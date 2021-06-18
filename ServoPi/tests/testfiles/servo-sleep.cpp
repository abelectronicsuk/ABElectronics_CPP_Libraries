/*
 * servo-sleep.cpp
 *
 *	Servo class > sleep function test program 
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
	start_test("Servo class > sleep()");

	Servo servo(0x40, 1, 2, false, true); // create Servo object

	servo.sleep();

	test_i2c_register(PCA9685::Mode1, 0x10); // MODE1 expected to be 0x10

	test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
