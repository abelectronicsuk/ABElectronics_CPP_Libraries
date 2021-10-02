/*
 * set_interrupt_on_port.cpp
 * 
 * IOPi class > set_interrupt_on_port function test program
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
	test.start_test("IOPi class > set_interrupt_on_port()");

	IoPi iopi(0x20, false);

	// out of bounds tests
	try
	{
		iopi.set_interrupt_on_port(2, 0);
		test.test_exception_failed("port high boundary out of bounds");
	}
	catch(const std::exception& e){	}

    uint8_t y = 0;
	
    for (int x = 0; x < 256; x++)
	{
        test.i2c_emulator_write_word_data(test.MCP23017_GPINTENA, 0x00);
        test.i2c_emulator_write_word_data(test.MCP23017_GPINTENB, 0x00);
        iopi.set_interrupt_on_port(0, x);
		
        y = test.i2c_emulator_read_word_data(test.MCP23017_GPINTENA);
        if (x != y){
            test.test_exception_failed("set port failed on port 0");
            break;
		}

        test.i2c_emulator_write_word_data(test.MCP23017_GPINTENA, 0x00);
        test.i2c_emulator_write_word_data(test.MCP23017_GPINTENB, 0x00);
        iopi.set_interrupt_on_port(1, x);
		
        y = test.i2c_emulator_read_word_data(test.MCP23017_GPINTENB);
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
