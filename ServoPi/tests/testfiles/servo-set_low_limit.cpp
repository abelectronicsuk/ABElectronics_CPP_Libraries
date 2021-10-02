/*
 * servo-set_low_limit.cpp
 *
 *	Servo class > set_low_limit function test program 
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
	test.start_test("Servo class > set_low_limit()");

	Servo servo(0x40, 1, 2, false, true); // create Servo object

	// out of bounds test for channel parameter
	try{
		servo.set_low_limit(2, -1);
		test.test_exception_failed("channel low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
		servo.set_low_limit(2, 17);
		test.test_exception_failed("channel high out of bounds");
	}
	catch(const std::exception& e){	}

	test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
