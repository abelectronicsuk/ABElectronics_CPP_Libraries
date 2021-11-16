/*
 * io_read_pin.cpp
 * 
 * ExpanderPi class > io_read_pin function test program
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
	test.start_test("ExpanderPi class > io_read_pin()");

	ExpanderPi bus(true);

	// out of bounds tests
	try
	{
		bus.io_read_pin(0);
		test.test_exception_failed("value low boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	try
	{
		bus.io_read_pin(17);
		test.test_exception_failed("value high boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	for (uint8_t a = 1; a < 17; a++){
		test.i2c_emulator_write_word_data(test.MCP23017_GPIOA, pow(2, a-1)); // set register
		if (bus.io_read_pin(a) != 1)
		{
			test.test_fail("unexpected register value");
		}     
	}

    test.test_outcome();
	
	(void)argc;
	(void)argv;
	return (0);
}
