/*
 * io_read_pin.cpp
 * 
 * ExpanderPi class > io_read_pin function test program
 *   
*/

#include <stdexcept>
#include <cmath>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("ExpanderPi class > io_read_pin()");

	ExpanderPi bus(true);

	// out of bounds tests
	try
	{
		bus.io_read_pin(0);
		TestLibs::test_exception_failed("value low boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	try
	{
		bus.io_read_pin(17);
		TestLibs::test_exception_failed("value high boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	for (uint8_t a = 1; a < 17; a++){
		TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_GPIOA, (uint16_t )pow(2, a-1)); // set register
		if (bus.io_read_pin(a) != 1)
		{
			TestLibs::test_fail("unexpected register value");
		}     
	}

    TestLibs::test_outcome();
	
	(void)argc;
	(void)argv;
	return (0);
}
