/*
 * io_get_interrupt_defaults.cpp
 * 
 * ExpanderPi class > io_get_interrupt_defaults function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("ExpanderPi class > io_get_interrupt_defaults()");

	ExpanderPi bus(false);

	uint8_t x;

	// out-of-bounds tests
	try
	{
		bus.io_get_interrupt_defaults(2);
		TestLibs::test_exception_failed("get_interrupt_defaults high out of bounds");
	}
	catch(const std::exception& e){	}

	for (uint8_t a = 0; a < 255; a++){
        TestLibs::i2c_emulator_write_byte_data(TestLibs::MCP23017_DEFVALA, a);
		TestLibs::i2c_emulator_write_byte_data(TestLibs::MCP23017_DEFVALB, 0);
        x = bus.io_get_interrupt_defaults(0);
        if (x != a){
            TestLibs::test_fail("failed to get interrupt default on port 0");
            break;
		}
		TestLibs::i2c_emulator_write_byte_data(TestLibs::MCP23017_DEFVALA, 0);
		TestLibs::i2c_emulator_write_byte_data(TestLibs::MCP23017_DEFVALB, a);
        x = bus.io_get_interrupt_defaults(1);
        if (x != a){
            TestLibs::test_fail("failed to get interrupt default on port 1");
            break;
		}
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
