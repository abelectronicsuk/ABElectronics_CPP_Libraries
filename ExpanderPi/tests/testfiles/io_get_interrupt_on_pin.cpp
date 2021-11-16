/*
 * io_get_interrupt_on_pin.cpp
 * 
 * ExpanderPi class > io_get_interrupt_on_pin function test program
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
	test.start_test("ExpanderPi class > io_get_interrupt_on_pin()");

	ExpanderPi bus(false);
	uint8_t x = 0;
	uint16_t y = 0;

	// out of bounds tests
	try
	{
		bus.io_get_interrupt_on_pin(0);
		test.test_exception_failed("pin low out of bounds");
	}
	catch (exception &e){}

	try
	{
		bus.io_get_interrupt_on_pin(17);
		test.test_exception_failed("pin high out of bounds");
	}
	catch (exception &e){}

	for (uint8_t a = 1; a < 17; a++){
		y = 65535;
		
		y = test.test_set_bit(y, a-1, false);	
		test.i2c_emulator_write_word_data(test.MCP23017_GPINTENA, y);
        x = bus.io_get_interrupt_on_pin(a);
        if (x != 0){
            test.test_exception_failed("get pin failed on set to 0");
            break;
		}
		y = 0;
		y = test.test_set_bit(y, a-1, true);
        test.i2c_emulator_write_word_data(test.MCP23017_GPINTENA, y);
        x = bus.io_get_interrupt_on_pin(a);
        if (x != 1){
            test.test_exception_failed("get pin failed on set to 1");
            break;
		}
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
