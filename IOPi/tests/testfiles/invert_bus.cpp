/*
 * invert_bus.cpp
 * 
 * IOPi class > invert_bus function test program
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
	test.start_test("IOPi class > invert_bus()");
	IoPi bus(0x20, false);  // new iopi object without initialisation

    for (uint16_t a = 0; a < 65535; a++){
        bus.invert_bus(a);  
		if (a != test.i2c_emulator_read_word_data(test.MCP23017_IPOLA)){
			test.test_fail("unexpected register value");
		}
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
