/*
 * servo-set_frequency.cpp
 *
 *	Servo class > set_frequency function test program 
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

	TestLibs::start_test("Servo class > set_frequency()");

	Servo servo(0x40, 1, 2, false, true); // create Servo object

	// out of bounds test for frequency value
	try{
		servo.set_frequency(39, 0);
		TestLibs::test_exception_failed("Frequency low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
		servo.set_frequency(1001, 0);
		TestLibs::test_exception_failed("Frequency high out of bounds");
	}
	catch(const std::exception& e){	}

	servo.set_frequency(100, 2);

	/* 
		register values are calculated using the following formula

		floor(((25000000 / 4096) / frequency) - 1 + 0.5) + calibration

		value is written to the PRE_SCALE register
	*/

	TestLibs::test_i2c_register(TestLibs::PCA9685_Prescaler, 62); // Prescaler expected to be 62

	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
