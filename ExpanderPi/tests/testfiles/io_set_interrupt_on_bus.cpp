/*
 * io_set_interrupt_on_bus.cpp
 * 
 * ExpanderPi class > io_set_interrupt_on_bus function test program
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
	test.start_test("ExpanderPi class > io_set_interrupt_on_bus()");

	ExpanderPi bus(false);
    
    uint16_t x = 0;

    for (uint16_t a = 0; a < 65535; a++){
        bus.io_set_interrupt_on_bus(a);      

        x = test.i2c_emulator_read_word_data(test.MCP23017_GPINTENA); // read value from registers
        if (x != a){
            test.test_fail("failed to set bus direction");
            break;
		} 
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
