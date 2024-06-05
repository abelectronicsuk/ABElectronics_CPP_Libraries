/*
 * io_set_interrupt_type.cpp
 * 
 * ExpanderPi class > io_set_interrupt_type function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("ExpanderPi class > io_set_interrupt_type()");

	ExpanderPi bus(false);

	// out of bounds tests
	try
	{
		bus.io_set_interrupt_type(2, 0);
		TestLibs::test_exception_failed("port high boundary out of bounds");
	}
	catch(const std::exception& e){	}

    uint8_t y;
	
    for (int x = 0; x < 256; x++)
	{
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_INTCONA, 0x00);
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_INTCONB, 0x00);

        bus.io_set_interrupt_type(0, x);
		
        y = TestLibs::i2c_emulator_read_word_data(TestLibs::MCP23017_INTCONA);
        if (x != y){
            TestLibs::test_exception_failed("set port failed on port 0");
            break;
		}

        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_INTCONA, 0x00);
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_INTCONB, 0x00);

        bus.io_set_interrupt_type(1, x);
		
        y = TestLibs::i2c_emulator_read_word_data(TestLibs::MCP23017_INTCONB);
        if (x != y){
            TestLibs::test_exception_failed("set port failed on port 1");
            break;
		}
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
