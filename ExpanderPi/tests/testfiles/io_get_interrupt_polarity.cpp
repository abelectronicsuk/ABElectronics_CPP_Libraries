/*
 * io_get_interrupt_polarity.cpp
 * 
 * ExpanderPi class > io_get_interrupt_polarity function test program
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
	test.start_test("ExpanderPi class > io_get_interrupt_polarity()");

	ExpanderPi bus(false);

	uint8_t x = 0;

	test.i2c_emulator_write_byte_data(test.MCP23017_IOCON, 0xfd);
    x = bus.io_get_interrupt_polarity();
    if (x != 0){
        test.test_exception_failed("get port failed when set to 0");
	}
    
	test.i2c_emulator_write_byte_data(test.MCP23017_IOCON, 0x02);
    x = bus.io_get_interrupt_polarity();
    if (x != 1){
        test.test_exception_failed("get port failed when set to 0");
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
