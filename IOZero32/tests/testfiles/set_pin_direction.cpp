/*
 * set_pin_direction.cpp
 * 
 * IOZero32 class > set_pin_direction function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IOZero32.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOZero32 class > set_pin_direction()");

	IOZero32 bus(0x20);

	// out of bounds tests
	try
	{
		bus.set_pin_direction(0, 0);
		TestLibs::test_exception_failed("pin low boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	try
	{
		bus.set_pin_direction(17, 0);
		TestLibs::test_exception_failed("pin high boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	try
	{
		bus.set_pin_direction(1, 2);
		TestLibs::test_exception_failed("value high boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
    for (int x = 1; x <= 8; x++)
	{
        TestLibs::i2c_emulator_write_word_data(TestLibs::PCA9535_CONFIGPORT0, 0x00);
        bus.set_pin_direction(x, 1);

        uint8_t y = TestLibs::i2c_emulator_read_word_data(TestLibs::PCA9535_CONFIGPORT0);
        if (!TestLibs::test_get_bit(y, x - 1)){
            TestLibs::test_exception_failed("set pin to 1 failed on port 0");
            break;
		}
	}

    for (int x = 1; x <= 8; x++)
	{
        TestLibs::i2c_emulator_write_word_data(TestLibs::PCA9535_CONFIGPORT0, 0xFF);
        bus.set_pin_direction(x, 0);

        uint8_t y = TestLibs::i2c_emulator_read_word_data(TestLibs::PCA9535_CONFIGPORT0);
        if (TestLibs::test_get_bit(y, x - 1)){
            TestLibs::test_exception_failed("set pin to 0 failed on port 0");
            break;
		}
	}

    for (int x = 9; x <= 16; x++)
	{
        TestLibs::i2c_emulator_write_word_data(TestLibs::PCA9535_CONFIGPORT1, 0x00);
        bus.set_pin_direction(x, 1);

        uint8_t y = TestLibs::i2c_emulator_read_word_data(TestLibs::PCA9535_CONFIGPORT1);
        if (!TestLibs::test_get_bit(y, x - 9)){
            TestLibs::test_exception_failed("set pin to 1 failed on port 1");
            break;
		}
	}

    for (int x = 9; x <= 16; x++)
	{
        TestLibs::i2c_emulator_write_word_data(TestLibs::PCA9535_CONFIGPORT1, 0xFF);
        bus.set_pin_direction(x, 0);

        uint8_t y = TestLibs::i2c_emulator_read_word_data(TestLibs::PCA9535_CONFIGPORT1);
        if (TestLibs::test_get_bit(y, x - 9)){
            TestLibs::test_exception_failed("set pin to 1 failed on port 1");
            break;
		}
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
