/*
 * servo-is_sleeping.cpp
 *
 *	Servo class > is_sleeping function test program 
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
	start_test("Servo class > is_sleeping()");

	Servo servo(0x40, 1, 2, false, true); // create Servo object

	bool a = servo.is_sleeping(); // Value should be false when MODE1 is 0x00

	if (a){
		test_fail("Unexpected output for is_sleeping()");
	}

	i2c_emulator_write_byte_data(PCA9685::Mode1, 0x10); // update sleep bit to 1
	
	a = servo.is_sleeping(); // Value should be false when MODE1 is 0x00

	if (!a){
		test_fail("Unexpected output for is_sleeping()");
	}

	test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
