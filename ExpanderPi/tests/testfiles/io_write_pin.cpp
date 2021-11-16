/*
 * io_write_pin.cpp
 * 
 * ExpanderPi class > io_write_pin function test program
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
	test.start_test("ExpanderPi class > io_write_pin()");

	ExpanderPi bus(false);

	// out of bounds tests
	try
	{
		bus.io_write_pin(0, 0);
		test.test_exception_failed("pin low boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	try
	{
		bus.io_write_pin(17, 0);
		test.test_exception_failed("pin high boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	try
	{
		bus.io_write_pin(1, 2);
		test.test_exception_failed("value high boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
    for (int x = 1; x <= 8; x++)
	{
        test.i2c_emulator_write_word_data(test.MCP23017_GPIOA, 0x00);
        bus.io_write_pin(x, 1);

        uint8_t y = test.i2c_emulator_read_word_data(test.MCP23017_GPIOA);
        if (!test.test_get_bit(y, x - 1)){
            test.test_exception_failed("set pin to 1 failed on port 0");
            break;
		}
	}

    for (int x = 1; x <= 8; x++)
	{
        test.i2c_emulator_write_word_data(test.MCP23017_GPIOA, 0xFF);
        bus.io_write_pin(x, 0);

        uint8_t y = test.i2c_emulator_read_word_data(test.MCP23017_GPIOA);
        if (test.test_get_bit(y, x - 1)){
            test.test_exception_failed("set pin to 0 failed on port 0");
            break;
		}
	}

    for (int x = 9; x <= 16; x++)
	{
        test.i2c_emulator_write_word_data(test.MCP23017_GPIOB, 0x00);
        bus.io_write_pin(x, 1);

        uint8_t y = test.i2c_emulator_read_word_data(test.MCP23017_GPIOB);
        if (!test.test_get_bit(y, x - 9)){
            test.test_exception_failed("set pin to 1 failed on port 1");
            break;
		}
	}

    for (int x = 9; x <= 16; x++)
	{
        test.i2c_emulator_write_word_data(test.MCP23017_GPIOB, 0xFF);
        bus.io_write_pin(x, 0);

        uint8_t y = test.i2c_emulator_read_word_data(test.MCP23017_GPIOB);
        if (test.test_get_bit(y, x - 9)){
            test.test_exception_failed("set pin to 1 failed on port 1");
            break;
		}
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
