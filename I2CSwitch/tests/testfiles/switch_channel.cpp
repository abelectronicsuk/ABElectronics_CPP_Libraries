/*
 * switch_channel.cpp
 * 
 * I2CSwitch class > switch_channel function test program
 *   
*/

#include <stdio.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_I2CSwitch.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
    TestLibs test;
	test.start_test("I2CSwitch class > switch_channel()");
	
    I2CSwitch i2cswitch(0x70);  // new I2CSwitch object

    // out of bounds test
	try{
		i2cswitch.switch_channel(0);
		test.test_exception_failed("switch_channel low out of bounds");
	}
	catch(const std::exception& e){	}

    try{
		i2cswitch.switch_channel(5);
		test.test_exception_failed("switch_channel high out of bounds");
	}
	catch(const std::exception& e){	}
    
    uint8_t x = 0;

    test.i2c_emulator_write_byte_data(0x00, 0x00); // set register value

    i2cswitch.switch_channel(1);

    x = test.i2c_emulator_read_byte_data(0x00);

    if (x != 0x01){ // register bit 1 set to 1
            test.test_fail("failed to switch channel");
	}

    i2cswitch.switch_channel(2);

    x = test.i2c_emulator_read_byte_data(0x00);

    if (x != 0x02){ // register bit 1 set to 1
            test.test_fail("failed to switch channel");
	}

    i2cswitch.switch_channel(3);

    x = test.i2c_emulator_read_byte_data(0x00);

    if (x != 0x04){ // register bit 1 set to 1
            test.test_fail("failed to switch channel");
	}

    i2cswitch.switch_channel(4);

    x = test.i2c_emulator_read_byte_data(0x00);

    if (x != 0x08){ // register bit 1 set to 1
            test.test_fail("failed to switch channel");
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
