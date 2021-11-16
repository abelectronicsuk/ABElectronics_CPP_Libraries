/*
 * io_read_port.cpp
 * 
 * ExpanderPi class > io_read_port function test program
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
	test.start_test("ExpanderPi class > io_read_port()");

	ExpanderPi bus(true);
	uint8_t x = 0;

	// out of bounds tests
	try
	{
		bus.io_read_port(2);
		test.test_exception_failed("high boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	for (uint8_t a = 0; a < 255; a++){
		test.i2c_emulator_write_word_data(test.MCP23017_GPIOA, a);
        x = bus.io_read_port(0);
        if (x != a){
            test.test_exception_failed("get port value failed when set to 0");
            break;
		}
        test.i2c_emulator_write_word_data(test.MCP23017_GPIOB, a);
        x = bus.io_read_port(1);
        if (x != a){
            test.test_exception_failed("get port value failed when set to 1");
            break;
		}
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
