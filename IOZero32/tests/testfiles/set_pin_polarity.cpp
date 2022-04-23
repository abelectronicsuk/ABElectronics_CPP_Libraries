/*
 * set_pin_polarity.cpp
 * 
 * IOZero32 class > set_pin_polarity function test program
 *   
*/

#include <stdio.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IOZero32.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs test;
	test.start_test("IOZero32 class > set_pin_polarity()");

	IOZero32 bus(0x20);

	// out of bounds tests
	try
	{
		bus.set_pin_polarity(0, 0);
		test.test_exception_failed("pin low boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	try
	{
		bus.set_pin_polarity(17, 0);
		test.test_exception_failed("pin high boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	try
	{
		bus.set_pin_polarity(1, 2);
		test.test_exception_failed("value high boundary out of bounds");
	}
	catch(const std::exception& e){	}

	

    for (int x = 1; x < 17; x++)
	{
		test.i2c_emulator_write_word_data(test.PCA9535_INVERTPORT0, 0); // reset register
        bus.set_pin_polarity(x, 1);
		if (test.i2c_emulator_read_word_data(test.PCA9535_INVERTPORT0) != pow(2, x-1)) // check bit has been set in register
		{
			test.test_fail("unexpected register value");
		}
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
