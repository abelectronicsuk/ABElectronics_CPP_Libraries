/*
 * get_interrupt_type.cpp
 * 
 * IOPi class > get_interrupt_type function test program
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
	test.start_test("IOPi class > get_interrupt_type()");

	IoPi bus(0x20, false);
	uint8_t x = 0;

	// out of bounds tests
	try
	{
		bus.get_interrupt_type(2);
		test.test_exception_failed("port out of bounds");
	}
	catch (exception &e){}

	for (uint8_t a = 0; a < 255; a++){
		test.i2c_emulator_write_byte_data(test.MCP23017_INTCONB, 0);
		test.i2c_emulator_write_byte_data(test.MCP23017_INTCONA, a);
        x = bus.get_interrupt_type(0);
        if (x != a){
            test.test_exception_failed("get port failed when set to 0");
            break;
		}
		test.i2c_emulator_write_byte_data(test.MCP23017_INTCONA, 0);
        test.i2c_emulator_write_byte_data(test.MCP23017_INTCONB, a);
        x = bus.get_interrupt_type(1);
        if (x != a){
            test.test_exception_failed("get port failed when set to 1");
            break;
		}
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
