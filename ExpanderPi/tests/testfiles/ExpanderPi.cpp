/*
 * ExpanderPi.cpp
 * 
 * ExpanderPi class test program
 *   
*/

#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("ExpanderPi class > ExpanderPi()");
	

	TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_IODIRA, 0x0000); // Set IODIRA and IODIRB to be 0x00
	TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_GPPUA, 0xFFFF); // Set GPPUA and GPPUB to be 0xFF
	TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_IPOLA, 0xFFFF); // Set IPOLA and IPOLB to be 0xFF

    __attribute__((unused)) ExpanderPi bus(true); // create ExpanderPi object

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
