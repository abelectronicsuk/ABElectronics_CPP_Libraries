/*
 * set_channel_state.cpp
 * 
 * I2CSwitch class > set_channel_state function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_I2CSwitch.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("I2CSwitch class > set_channel_state()");
	
    I2CSwitch i2cswitch(0x70);  // new I2CSwitch object

    // out of bounds test
	try{
		i2cswitch.set_channel_state(0, 0);
		TestLibs::test_exception_failed("set_channel_state channel low out of bounds");
	}
	catch(const std::exception& e){	}

    try{
		i2cswitch.set_channel_state(5, 0);
		TestLibs::test_exception_failed("set_channel_state channel high out of bounds");
	}
	catch(const std::exception& e){	}

    try{
		i2cswitch.set_channel_state(1, 2);
		TestLibs::test_exception_failed("set_channel_state state high out of bounds");
	}
	catch(const std::exception& e){	}

       
    uint8_t x;

    TestLibs::i2c_emulator_write_byte_data(0x00, 0x00); // set register value

    i2cswitch.set_channel_state(1, 1);

    x = TestLibs::i2c_emulator_read_byte_data(0x00);

    if (x != 0x01){
            TestLibs::test_fail("failed to set channel");
	}

    i2cswitch.set_channel_state(2, 1);

    x = TestLibs::i2c_emulator_read_byte_data(0x00);

    if (x != 0x03){
            TestLibs::test_fail("failed to set channel");
	}

    i2cswitch.set_channel_state(3, 1);

    x = TestLibs::i2c_emulator_read_byte_data(0x00);

    if (x != 0x07){
            TestLibs::test_fail("failed to set channel");
	}

    i2cswitch.set_channel_state(4, 1);

    x = TestLibs::i2c_emulator_read_byte_data(0x00);

    if (x != 0x0F){
            TestLibs::test_fail("failed to set channel");
	}

    i2cswitch.set_channel_state(1, 0);

    x = TestLibs::i2c_emulator_read_byte_data(0x00);

    if (x != 0x0E){
            TestLibs::test_fail("failed to set channel");
	}

    i2cswitch.set_channel_state(2, 0);

    x = TestLibs::i2c_emulator_read_byte_data(0x00);

    if (x != 0x0C){
            TestLibs::test_fail("failed to set channel");
	}

    i2cswitch.set_channel_state(3, 0);

    x = TestLibs::i2c_emulator_read_byte_data(0x00);

    if (x != 0x08){
            TestLibs::test_fail("failed to set channel");
	}

    i2cswitch.set_channel_state(4, 0);

    x = TestLibs::i2c_emulator_read_byte_data(0x00);

    if (x != 0x00){
            TestLibs::test_fail("failed to set channel");
	}


    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
