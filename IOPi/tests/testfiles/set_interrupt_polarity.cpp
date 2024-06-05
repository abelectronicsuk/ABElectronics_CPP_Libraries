/*
 * set_interrupt_polarity.cpp
 * 
 * IOPi class > set_interrupt_polarity function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOPi class > set_interrupt_polarity()");

	IoPi bus(0x20, false);

	// out of bounds tests
	try
	{
		bus.set_interrupt_polarity(2);
		TestLibs::test_exception_failed("high boundary out of bounds");
	}
	catch(const std::exception& e){	}

    TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_IOCON, 0x80);

	bus.set_interrupt_polarity(1);

    uint8_t x = TestLibs::i2c_emulator_read_word_data(TestLibs::MCP23017_IOCON);

    if (x != 0x82){
            TestLibs::test_exception_failed("failed to set interrupt polarity to 1");
	}

    bus.set_interrupt_polarity(0);
    x = TestLibs::i2c_emulator_read_word_data(TestLibs::MCP23017_IOCON);

    if (x != 0x80){
            TestLibs::test_exception_failed("failed to set interrupt polarity to 0");
	}

	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
