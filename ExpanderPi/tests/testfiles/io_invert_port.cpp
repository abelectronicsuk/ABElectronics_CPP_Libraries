/*
 * io_invert_port.cpp
 * 
 * ExpanderPi class > io_invert_port function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("ExpanderPi class > io_invert_port()");
	ExpanderPi bus(false);

	// out of bounds tests
	try
	{
		bus.io_invert_port(2, 0);
		TestLibs::test_exception_failed("port high boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
    for (int x = 0; x < 256; x++)
	{
		TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_IPOLA, 0); // reset registers

        bus.io_invert_port(0, x);

		if (TestLibs::i2c_emulator_read_byte_data(TestLibs::MCP23017_IPOLA) != x) // check value has been set in register
		{
			TestLibs::test_fail("unexpected register value");
		}

		TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_IPOLA, 0); // reset registers

		bus.io_invert_port(1, x);
		
		if (TestLibs::i2c_emulator_read_byte_data(TestLibs::MCP23017_IPOLB) != x) // check value has been set in register
		{
			TestLibs::test_fail("unexpected register value");
		}
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
