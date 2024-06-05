/*
 * set_interrupt_on_pin.cpp
 * 
 * IOPi class > set_interrupt_on_pin function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOPi class > set_interrupt_on_pin()");

	IoPi iopi(0x20, false);

	// out of bounds tests
	try
	{
		iopi.set_interrupt_on_pin(0, 0);
		TestLibs::test_exception_failed("pin low boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	try
	{
		iopi.set_interrupt_on_pin(17, 0);
		TestLibs::test_exception_failed("pin high boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	try
	{
		iopi.set_interrupt_on_pin(1, 2);
		TestLibs::test_exception_failed("value high boundary out of bounds");
	}
	catch(const std::exception& e){	}

    for (int x = 1; x <= 8; x++)
	{
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_GPINTENA, 0x00);
        iopi.set_interrupt_on_pin(x, 1);

        uint8_t y = TestLibs::i2c_emulator_read_word_data(TestLibs::MCP23017_GPINTENA);
        if (!TestLibs::test_get_bit(y, x - 1)){
            TestLibs::test_exception_failed("set pin to 1 failed on port 0");
            break;
		}
	}

    for (int x = 1; x <= 8; x++)
	{
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_GPINTENA, 0xFF);
        iopi.set_interrupt_on_pin(x, 0);

        uint8_t y = TestLibs::i2c_emulator_read_word_data(TestLibs::MCP23017_GPINTENA);
        if (TestLibs::test_get_bit(y, x - 1)){
            TestLibs::test_exception_failed("set pin to 0 failed on port 0");
            break;
		}
	}

    for (int x = 9; x <= 16; x++)
	{
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_GPINTENB, 0x00);
        iopi.set_interrupt_on_pin(x, 1);

        uint8_t y = TestLibs::i2c_emulator_read_word_data(TestLibs::MCP23017_GPINTENB);
        if (!TestLibs::test_get_bit(y, x - 9)){
            TestLibs::test_exception_failed("set pin to 1 failed on port 1");
            break;
		}
	}

    for (int x = 9; x <= 16; x++)
	{
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_GPINTENB, 0xFF);
        iopi.set_interrupt_on_pin(x, 0);

        uint8_t y = TestLibs::i2c_emulator_read_word_data(TestLibs::MCP23017_GPINTENB);
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
