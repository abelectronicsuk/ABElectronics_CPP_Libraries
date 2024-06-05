/*
 * servo-move.cpp
 *
 *	Servo class > move function test program 
 *  
 */

#include <cstdint>
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

	TestLibs::start_test("Servo class > move()");

	Servo servo(0x40, 1, 2, false, true); // create Servo object

	// out of bounds test for channel parameter
	try{
		servo.move(0, 200, 250);
		TestLibs::test_exception_failed("channel low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
		servo.move(17, 200, 250);
		TestLibs::test_exception_failed("channel high out of bounds");
	}
	catch(const std::exception& e){	}

	// out of bounds test for position parameter
	try{
		servo.move(1, -1, 250);
		TestLibs::test_exception_failed("position low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
		servo.move(1, 251, 250);
		TestLibs::test_exception_failed("position high out of bounds");
	}
	catch(const std::exception& e){	}

	// out of bounds test for steps parameter
	try{
		servo.move(1, 100, 0);
		TestLibs::test_exception_failed("steps low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
		servo.move(1, 100, 4096);
		TestLibs::test_exception_failed("steps high out of bounds");
	}
	catch(const std::exception& e){	}

	// loop through channels 1 to 16
	for (uint8_t channel = 1; channel < 17; channel ++){
		servo.move(channel, 200, 250); // set servo position

		uint16_t position = servo.get_position(channel, 250); // get servo position

		if (position != 200){
			TestLibs::test_fail(&"Incorrect position for channel " [ channel]);
		}
	}

	TestLibs::test_outcome();
	(void)argc;
	(void)argv;
	return (0);
}
