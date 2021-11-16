/*
 * io_get_interrupt_defaults.cpp
 * 
 * ExpanderPi class > io_get_interrupt_defaults function test program
 *   
*/

#include <stdio.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs test;
	test.start_test("ExpanderPi class > io_get_interrupt_defaults()");

	ExpanderPi bus(false);

	uint8_t x = 0;

	// out of bounds tests
	try
	{
		bus.io_get_interrupt_defaults(2);
		test.test_exception_failed("get_interrupt_defaults high out of bounds");
	}
	catch(const std::exception& e){	}

	for (uint8_t a = 0; a < 255; a++){
        test.i2c_emulator_write_byte_data(test.MCP23017_DEFVALA, a);
		test.i2c_emulator_write_byte_data(test.MCP23017_DEFVALB, 0);
        x = bus.io_get_interrupt_defaults(0);
        if (x != a){
            test.test_fail("failed to get interrupt default on port 0");
            break;
		}
		test.i2c_emulator_write_byte_data(test.MCP23017_DEFVALA, 0);
		test.i2c_emulator_write_byte_data(test.MCP23017_DEFVALB, a);
        x = bus.io_get_interrupt_defaults(1);
        if (x != a){
            test.test_fail("failed to get interrupt default on port 1");
            break;
		}
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
