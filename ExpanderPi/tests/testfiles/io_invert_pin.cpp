/*
 * io_invert_pin.cpp
 * 
 * ExpanderPi class > io_invert_pin function test program
 *   
*/

#include <stdio.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs test;
	test.start_test("ExpanderPi class > io_invert_pin()");

	ExpanderPi bus(false);

	// out of bounds tests
	try
	{
		bus.io_invert_pin(0, 0);
		test.test_exception_failed("pin low boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	try
	{
		bus.io_invert_pin(17, 0);
		test.test_exception_failed("pin high boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	try
	{
		bus.io_invert_pin(1, 2);
		test.test_exception_failed("value high boundary out of bounds");
	}
	catch(const std::exception& e){	}

	

    for (int x = 1; x < 17; x++)
	{
		test.i2c_emulator_write_word_data(test.MCP23017_IPOLA, 0); // reset register
        bus.io_invert_pin(x, 1);
		if (test.i2c_emulator_read_word_data(test.MCP23017_IPOLA) != pow(2, x-1)) // check bit has been set in register
		{
			test.test_fail("unexpected register value");
		}
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
