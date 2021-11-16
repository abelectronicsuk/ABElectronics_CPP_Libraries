/*
 * io_get_interrupt_on_port.cpp
 * 
 * ExpanderPi class > io_get_interrupt_on_port function test program
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
	test.start_test("ExpanderPi class > io_get_interrupt_on_port()");

	ExpanderPi bus(false);
	uint8_t x = 0;

	// out of bounds tests
	try
	{
		bus.io_get_interrupt_on_port(2);
		test.test_exception_failed("port out of bounds");
	}
	catch (exception &e){}

	for (uint8_t a = 0; a < 255; a++){
        test.i2c_emulator_write_word_data(test.MCP23017_GPINTENA, a);
        x = bus.io_get_interrupt_on_port(0);
        if (x != a){
            test.test_exception_failed("get port failed when set to 0");
            break;
		}
        test.i2c_emulator_write_word_data(test.MCP23017_GPINTENB, a);
        x = bus.io_get_interrupt_on_port(1);
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
