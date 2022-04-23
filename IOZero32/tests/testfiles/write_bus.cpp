/*
 * write_bus.cpp
 * 
 * IOZero32 class > write_bus function test program
 *   
*/

#include <stdio.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IOZero32.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs test;
	test.start_test("IOZero32 class > write_bus()");

	IOZero32 bus(0x20);  // new IOZero32 object

    for (uint16_t a = 0; a < 65535; a++){
        bus.write_bus(a); 

        uint16_t x = 0;
        
        x = test.i2c_emulator_read_word_data(test.PCA9535_OUTPUTPORT0); // read value from registers
        if (x != a){
            test.test_fail("failed to set bus value");
            break;
		}
    }

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
