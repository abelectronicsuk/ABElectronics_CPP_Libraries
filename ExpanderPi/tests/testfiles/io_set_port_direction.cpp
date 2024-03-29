/*
 * io_set_port_direction.cpp
 * 
 * ExpanderPi class > io_set_port_direction function test program
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
	test.start_test("ExpanderPi class > io_set_port_direction()");

	ExpanderPi bus(false);

	// out of bounds tests
	try
	{
		bus.io_set_port_direction(2, 0);
		test.test_exception_failed("port high boundary out of bounds");
	}
	catch(const std::exception& e){	}

 
    uint8_t y = 0;
	
    for (int x = 0; x < 256; x++)
	{
        test.i2c_emulator_write_word_data(test.MCP23017_IODIRA, 0x00);
        test.i2c_emulator_write_word_data(test.MCP23017_IODIRB, 0x00);

        bus.io_set_port_direction(0, x);
		
        y = test.i2c_emulator_read_word_data(test.MCP23017_IODIRA);
        if (x != y){
            test.test_exception_failed("set port failed on port 0");
            break;
		}

        test.i2c_emulator_write_word_data(test.MCP23017_IODIRA, 0x00);
        test.i2c_emulator_write_word_data(test.MCP23017_IODIRB, 0x00);

        bus.io_set_port_direction(1, x);
		
        y = test.i2c_emulator_read_word_data(test.MCP23017_IODIRB);
        if (x != y){
            test.test_exception_failed("set port failed on port 1");
            break;
		}
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
