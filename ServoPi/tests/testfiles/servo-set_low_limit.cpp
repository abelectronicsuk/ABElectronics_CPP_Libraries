/*
 * servo-set_low_limit.cpp
 *
 *	Servo class > set_low_limit function test program 
 *  
 */


#include <cstdio>
#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ServoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

void clear_screen() {
	printf("\033[2J\033[1;1H");
}


int main(int argc, char **argv) {

	TestLibs::start_test("Servo class > set_low_limit()");

	Servo servo(0x40, 1, 2, false, true); // create Servo object

	// out of bounds test for channel parameter
	try{
		servo.set_low_limit(2, -1);
		TestLibs::test_exception_failed("channel low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
		servo.set_low_limit(2, 17);
		TestLibs::test_exception_failed("channel high out of bounds");
	}
	catch(const std::exception& e){	}

	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
