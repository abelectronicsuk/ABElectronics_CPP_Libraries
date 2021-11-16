/*
 * io_set_interrupt_defaults.cpp
 * 
 * ExpanderPi class > io_set_interrupt_defaults function test program
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
	test.start_test("ExpanderPi class > io_set_interrupt_defaults()");

	ExpanderPi bus(false);

	// out of bounds tests
	try
	{
		bus.io_set_interrupt_defaults(2, 0);
		test.test_exception_failed("port high boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
    uint8_t x = 0;
    uint8_t y = 0;

    for (int i = 0; i < 256; i++)
	{
        bus.io_set_interrupt_defaults(0, i);
		bus.io_set_interrupt_defaults(1, i);
        
        x = test.i2c_emulator_read_byte_data(test.MCP23017_DEFVALA); // read value from registers
        if (x != i){
            test.test_fail("failed to set interrupt default for port 0");
            break;
		}

        y = test.i2c_emulator_read_byte_data(test.MCP23017_DEFVALB); // read value from registers
        if (y != i){
            test.test_fail("failed to set interrupt default for port 1");
            break;
		}
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
