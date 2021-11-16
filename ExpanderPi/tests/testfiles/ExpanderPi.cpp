/*
 * ExpanderPi.cpp
 * 
 * ExpanderPi class test program
 *   
*/

#include <stdio.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs test;
	test.start_test("ExpanderPi class > ExpanderPi()");
	

	test.i2c_emulator_write_word_data(test.MCP23017_IODIRA, 0x0000); // Set IODIRA and IODIRB to be 0x00
	test.i2c_emulator_write_word_data(test.MCP23017_GPPUA, 0xFFFF); // Set GPPUA and GPPUB to be 0xFF
	test.i2c_emulator_write_word_data(test.MCP23017_IPOLA, 0xFFFF); // Set IPOLA and IPOLB to be 0xFF

	ExpanderPi bus(true); // create ExpanderPi object

	test.test_i2c_register(test.MCP23017_IOCON, 0x02); // IOCON expected to be 0x02

	test.test_i2c_register(test.MCP23017_IODIRA, 0xFF); // IODIRA expected to be 0xFF
	test.test_i2c_register(test.MCP23017_IODIRB, 0xFF); // IODIRB expected to be 0xFF

	test.test_i2c_register(test.MCP23017_GPPUA, 0x00); // GPPUA expected to be 0xFF
	test.test_i2c_register(test.MCP23017_GPPUB, 0x00); // IODIRB expected to be 0xFF

	test.test_i2c_register(test.MCP23017_IPOLA, 0x00); // IPOLA expected to be 0xFF
	test.test_i2c_register(test.MCP23017_IPOLB, 0x00); // IPOLB expected to be 0xFF

	test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
