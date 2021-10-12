/*
 * I2CSwitch.cpp
 * 
 * I2CSwitch class > I2CSwitch function test program
 *   
*/

#include <stdio.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_I2CSwitch.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
    TestLibs test;
	test.start_test("I2CSwitch class > I2CSwitch()");
	
    // out of bounds test
	try{
		I2CSwitch i2cswitch1(0x6F);
		test.test_exception_failed("low out of bounds");
	}
	catch(const std::exception& e){	}

    try{
		I2CSwitch i2cswitch2(0x78);
		test.test_exception_failed("high out of bounds");
	}
	catch(const std::exception& e){	}

    I2CSwitch i2cswitch3(0x70);  // new I2CSwitch object

    test.test_gpio_state(2, true);

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
