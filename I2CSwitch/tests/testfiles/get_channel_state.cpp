/*
 * get_channel_state.cpp
 * 
 * I2CSwitch class > get_channel_state function test program
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
	test.start_test("I2CSwitch class > get_channel_state()");
	
    I2CSwitch i2cswitch(0x70);  // new I2CSwitch object

    // out of bounds test
	try{
		i2cswitch.get_channel_state(0);
		test.test_exception_failed("get_channel_state low out of bounds");
	}
	catch(const std::exception& e){	}

    try{
		i2cswitch.get_channel_state(5);
		test.test_exception_failed("get_channel_state high out of bounds");
	}
	catch(const std::exception& e){	}
    
    uint8_t x, y, z, a = 0;

    test.i2c_emulator_write_byte_data(0x00, 0x01); // set register value

    x = i2cswitch.get_channel_state(1);
    y = i2cswitch.get_channel_state(2);
    z = i2cswitch.get_channel_state(3);
    a = i2cswitch.get_channel_state(4);

    if (x != 1 && y != 0 && z != 0 && a != 0){ // register bit 1 set to 1
            test.test_fail("failed to get channel state 1");
	}

    test.i2c_emulator_write_byte_data(0x00, 0x02); // set register value

    x = i2cswitch.get_channel_state(1);
    y = i2cswitch.get_channel_state(2);
    z = i2cswitch.get_channel_state(3);
    a = i2cswitch.get_channel_state(4);

    if (x != 0 && y != 1 && z != 0 && a != 0){ // register bit 1 set to 1
            test.test_fail("failed to get channel state 2");
	}

    test.i2c_emulator_write_byte_data(0x00, 0x04); // set register value

    x = i2cswitch.get_channel_state(1);
    y = i2cswitch.get_channel_state(2);
    z = i2cswitch.get_channel_state(3);
    a = i2cswitch.get_channel_state(4);

    if (x != 0 && y != 0 && z != 1 && a != 0){ // register bit 1 set to 1
            test.test_fail("failed to get channel state 3");
	}

    test.i2c_emulator_write_byte_data(0x00, 0x08); // set register value

    x = i2cswitch.get_channel_state(1);
    y = i2cswitch.get_channel_state(2);
    z = i2cswitch.get_channel_state(3);
    a = i2cswitch.get_channel_state(4);

    if (x != 0 && y != 0 && z != 0 && a != 1){ // register bit 1 set to 1
            test.test_fail("failed to get channel state 4");
	}
  

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
