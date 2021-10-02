/*
 * get_interrupt_on_bus.cpp
 * 
 * IOPi class > get_interrupt_on_bus function test program
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
	test.start_test("IOPi class > get_interrupt_on_bus()");

	uint16_t x = 0;

    IoPi bus(0x20, false);  // new iopi object without initialisation

    for (uint16_t a = 0; a < 65535; a++){
        test.i2c_emulator_write_word_data(test.MCP23017_GPINTENA, a);
        x = bus.get_interrupt_on_bus();
        if (x != a){
            test.test_fail("failed to get interrupt on bus");
            break;
		}        
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
