/*
 * io_mirror_interrupts.cpp
 * 
 * ExpanderPi class > io_mirror_interrupts function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("ExpanderPi class > io_mirror_interrupts()");

	ExpanderPi bus(false);

	// out of bounds tests
	try
	{
		bus.io_mirror_interrupts(2);
		TestLibs::test_exception_failed("high boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	bus.io_mirror_interrupts(1);

	uint8_t a = TestLibs::i2c_emulator_read_byte_data(TestLibs::MCP23017_IOCON);
	if (a != 0x42) // check value has been set in register
	{
		TestLibs::test_fail("unexpected register value");
	}

    bus.io_mirror_interrupts(0);
	
	a = TestLibs::i2c_emulator_read_byte_data(TestLibs::MCP23017_IOCON);
	if (a != 0x02) // check value has been set in register
	{
		TestLibs::test_fail("unexpected register value");
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
