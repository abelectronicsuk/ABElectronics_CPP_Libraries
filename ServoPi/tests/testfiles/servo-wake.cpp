/*
 * servo-wake.cpp
 *
 *	Servo class > wake function test program 
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
	test.start_test("Servo class > wake()");

	Servo servo(0x40, 1, 2, false, true); // create Servo object

	test.i2c_emulator_write_byte_data(test.PCA9685_Mode1, 0x10); // Enable sleep mode in MODE1 register

	servo.wake();

	test.test_i2c_register(test.PCA9685_Mode1, 0x00); // MODE1 expected to be 0x00
	
	test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
