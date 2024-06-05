/*
 * IOPi.cpp
 * 
 * IOPi class test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOPi class > IOPi()");

	// out of bounds tests
	try
	{
		IoPi bus1(0x19);
		TestLibs::test_exception_failed("I2C address low out of bounds");
	}
	catch(const std::exception& e){	}

	try
	{
		IoPi bus1(0x28);
		TestLibs::test_exception_failed("I2C address high out of bounds");
	}
	catch(const std::exception& e){	}

	TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_IODIRA, 0x0000); // Set IODIRA and IODIRB to be 0x00
	TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_GPPUA, 0xFFFF); // Set GPPUA and GPPUB to be 0xFF
	TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_IPOLA, 0xFFFF); // Set IPOLA and IPOLB to be 0xFF

	IoPi bus2(0x20, true); // create IoPi object

	TestLibs::test_i2c_register(TestLibs::MCP23017_IOCON, 0x02); // IOCON expected to be 0x02

	TestLibs::test_i2c_register(TestLibs::MCP23017_IODIRA, 0xFF); // IODIRA expected to be 0xFF
	TestLibs::test_i2c_register(TestLibs::MCP23017_IODIRB, 0xFF); // IODIRB expected to be 0xFF

	TestLibs::test_i2c_register(TestLibs::MCP23017_GPPUA, 0x00); // GPPUA expected to be 0xFF
	TestLibs::test_i2c_register(TestLibs::MCP23017_GPPUB, 0x00); // IODIRB expected to be 0xFF

	TestLibs::test_i2c_register(TestLibs::MCP23017_IPOLA, 0x00); // IPOLA expected to be 0xFF
	TestLibs::test_i2c_register(TestLibs::MCP23017_IPOLB, 0x00); // IPOLB expected to be 0xFF

	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
