/*
 * read_interrupt_capture.cpp
 * 
 * IOPi class > read_interrupt_capture function test program
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
	test.start_test("IOPi class > read_interrupt_capture()");

	IoPi bus(0x20, false);
	uint8_t x = 0;

	// out of bounds tests
	try
	{
		bus.read_interrupt_capture(2);
		test.test_exception_failed("high boundary out of bounds");
	}
	catch(const std::exception& e){	}

	for (uint8_t a = 0; a < 255; a++){
		test.i2c_emulator_write_word_data(test.MCP23017_INTCAPA, a);
        x = bus.read_interrupt_capture(0);
        if (x != a){
            test.test_exception_failed("get interrupt capture failed when set to 0");
            break;
		}
        test.i2c_emulator_write_word_data(test.MCP23017_INTCAPB, a);
        x = bus.read_interrupt_capture(1);
        if (x != a){
            test.test_exception_failed("get interrupt capture failed when set to 1");
            break;
		}
	}

	test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
