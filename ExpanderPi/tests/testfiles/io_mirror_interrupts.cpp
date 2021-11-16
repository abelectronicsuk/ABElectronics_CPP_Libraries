/*
 * io_mirror_interrupts.cpp
 * 
 * ExpanderPi class > io_mirror_interrupts function test program
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
	test.start_test("ExpanderPi class > io_mirror_interrupts()");

	ExpanderPi bus(false);

	// out of bounds tests
	try
	{
		bus.io_mirror_interrupts(2);
		test.test_exception_failed("high boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	bus.io_mirror_interrupts(1);

	uint8_t a = test.i2c_emulator_read_byte_data(test.MCP23017_IOCON);
	if (a != 0x42) // check value has been set in register
	{
		test.test_fail("unexpected register value");
	}

    bus.io_mirror_interrupts(0);
	
	a = test.i2c_emulator_read_byte_data(test.MCP23017_IOCON);
	if (a != 0x02) // check value has been set in register
	{
		test.test_fail("unexpected register value");
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
