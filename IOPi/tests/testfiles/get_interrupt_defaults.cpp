/*
 * get_interrupt_defaults.cpp
 * 
 * IOPi class > get_interrupt_defaults function test program
 *   
*/

#include <stdio.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs test;
	test.start_test("IOPi class > get_interrupt_defaults()");

	IoPi bus(0x20, false);  // new IoPi object without initialisation

	uint8_t x = 0;

	// out of bounds tests
	try
	{
		bus.get_interrupt_defaults(2);
		test.test_exception_failed("get_interrupt_defaults high out of bounds");
	}
	catch(const std::exception& e){	}

	for (uint8_t a = 0; a < 255; a++){
        test.i2c_emulator_write_byte_data(test.MCP23017_DEFVALA, a);
		test.i2c_emulator_write_byte_data(test.MCP23017_DEFVALB, 0);
        x = bus.get_interrupt_defaults(0);
        if (x != a){
            test.test_fail("failed to get interrupt default on port 0");
            break;
		}
		test.i2c_emulator_write_byte_data(test.MCP23017_DEFVALA, 0);
		test.i2c_emulator_write_byte_data(test.MCP23017_DEFVALB, a);
        x = bus.get_interrupt_defaults(1);
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
