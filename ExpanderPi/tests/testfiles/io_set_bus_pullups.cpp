/*
 * io_set_bus_pullups.cpp
 * 
 * ExpanderPi class > io_set_bus_pullups function test program
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
	test.start_test("ExpanderPi class > io_set_bus_pullups()");

	ExpanderPi bus(false);

    for (uint16_t a = 0; a < 65535; a++){
        bus.io_set_bus_pullups(a); 

        uint16_t x = 0;
        
        x = test.i2c_emulator_read_word_data(test.MCP23017_GPPUA); // read value from registers
        if (x != a){
            test.test_fail("failed to set bus pullup");
            break;
		}
    }

    test.test_outcome();
	
	(void)argc;
	(void)argv;
	return (0);
}
