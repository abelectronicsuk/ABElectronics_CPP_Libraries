/*
 * get_bus_polarity.cpp
 * 
 * IOZero32 class > get_bus_polarity function test program
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
	test.start_test("IOZero32 class > get_bus_polarity()");

    IOZero32 bus(0x20);  // new IOZero32 object
    
    uint16_t x = 0;

    for (uint16_t a = 0; a < 65534; a++){
        test.i2c_emulator_write_word_data(test.PCA9535_INVERTPORT0, a); // set register value
        x = bus.get_bus_polarity(); // read value from registers
        if (x != a){
            test.test_fail("failed to get bus polarity");
            break;
		}        
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
