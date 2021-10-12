/*
 * set_channel_state.cpp
 * 
 * I2CSwitch class > set_channel_state function test program
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
	test.start_test("I2CSwitch class > set_channel_state()");
	
    I2CSwitch i2cswitch(0x70);  // new I2CSwitch object

    // out of bounds test
	try{
		i2cswitch.set_channel_state(0, 0);
		test.test_exception_failed("set_channel_state channel low out of bounds");
	}
	catch(const std::exception& e){	}

    try{
		i2cswitch.set_channel_state(5, 0);
		test.test_exception_failed("set_channel_state channel high out of bounds");
	}
	catch(const std::exception& e){	}

    try{
		i2cswitch.set_channel_state(1, 2);
		test.test_exception_failed("set_channel_state state high out of bounds");
	}
	catch(const std::exception& e){	}

       
    uint8_t x = 0;

    test.i2c_emulator_write_byte_data(0x00, 0x00); // set register value

    i2cswitch.set_channel_state(1, 1);

    x = test.i2c_emulator_read_byte_data(0x00);

    if (x != 0x01){
            test.test_fail("failed to set channel");
	}

    i2cswitch.set_channel_state(2, 1);

    x = test.i2c_emulator_read_byte_data(0x00);

    if (x != 0x03){
            test.test_fail("failed to set channel");
	}

    i2cswitch.set_channel_state(3, 1);

    x = test.i2c_emulator_read_byte_data(0x00);

    if (x != 0x07){
            test.test_fail("failed to set channel");
	}

    i2cswitch.set_channel_state(4, 1);

    x = test.i2c_emulator_read_byte_data(0x00);

    if (x != 0x0F){
            test.test_fail("failed to set channel");
	}

    i2cswitch.set_channel_state(1, 0);

    x = test.i2c_emulator_read_byte_data(0x00);

    if (x != 0x0E){
            test.test_fail("failed to set channel");
	}

    i2cswitch.set_channel_state(2, 0);

    x = test.i2c_emulator_read_byte_data(0x00);

    if (x != 0x0C){
            test.test_fail("failed to set channel");
	}

    i2cswitch.set_channel_state(3, 0);

    x = test.i2c_emulator_read_byte_data(0x00);

    if (x != 0x08){
            test.test_fail("failed to set channel");
	}

    i2cswitch.set_channel_state(4, 0);

    x = test.i2c_emulator_read_byte_data(0x00);

    if (x != 0x00){
            test.test_fail("failed to set channel");
	}


    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
