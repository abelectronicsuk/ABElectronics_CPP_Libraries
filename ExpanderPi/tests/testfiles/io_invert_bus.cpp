/*
 * io_invert_bus.cpp
 * 
 * ExpanderPi class > io_invert_bus function test program
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
	test.start_test("ExpanderPi class > io_invert_bus()");
	ExpanderPi bus(false);

    for (uint16_t a = 0; a < 65535; a++){
        bus.io_invert_bus(a);  
		if (a != test.i2c_emulator_read_word_data(test.MCP23017_IPOLA)){
			test.test_fail("unexpected register value");
		}
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
