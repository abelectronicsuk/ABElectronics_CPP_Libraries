/*
 * set_bus_polarity.cpp
 * 
 * IOZero32 class > set_bus_polarity function test program
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
	test.start_test("IOZero32 class > set_bus_polarity()");
	IOZero32 bus(0x20);  // new IOZero32 object

    for (uint16_t a = 0; a < 65535; a++){
        bus.set_bus_polarity(a);  
		if (a != test.i2c_emulator_read_word_data(test.PCA9535_INVERTPORT0)){
			test.test_fail("unexpected register value");
		}
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
