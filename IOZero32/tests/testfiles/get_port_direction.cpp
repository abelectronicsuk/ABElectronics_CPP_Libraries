/*
 * get_port_direction.cpp
 * 
 * IOZero32 class > get_port_direction function test program
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
	test.start_test("IOZero32 class > get_port_direction()");
    
	IOZero32 bus(0x20);
	uint8_t x = 0;

	// out of bounds tests
	try
	{
		bus.get_port_direction(2);
        test.test_exception_failed("port out of bounds");
	}

	catch (exception &e){}

	for (uint8_t a = 0; a < 255; a++){
		test.i2c_emulator_write_word_data(test.PCA9535_CONFIGPORT0, a);
        x = bus.get_port_direction(0);
        if (x != a){
            test.test_exception_failed("get port failed when set to 0");
            break;
		}
        test.i2c_emulator_write_word_data(test.PCA9535_CONFIGPORT1, a);
        x = bus.get_port_direction(1);
        if (x != a){
            test.test_exception_failed("get port failed when set to 1");
            break;
		}
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
