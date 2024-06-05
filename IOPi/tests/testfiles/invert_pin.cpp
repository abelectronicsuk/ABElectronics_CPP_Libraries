/*
 * invert_pin.cpp
 * 
 * IOPi class > invert_pin function test program
 *   
*/

#include <stdexcept>
#include <cmath>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOPi class > invert_pin()");

	IoPi iopi(0x20, false);

	// out of bounds tests
	try
	{
		iopi.invert_pin(0, 0);
		TestLibs::test_exception_failed("pin low boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	try
	{
		iopi.invert_pin(17, 0);
		TestLibs::test_exception_failed("pin high boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	try
	{
		iopi.invert_pin(1, 2);
		TestLibs::test_exception_failed("value high boundary out of bounds");
	}
	catch(const std::exception& e){	}

	

    for (int x = 1; x < 17; x++)
	{
		TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_IPOLA, 0); // reset register
        iopi.invert_pin(x, 1);
		if (TestLibs::i2c_emulator_read_word_data(TestLibs::MCP23017_IPOLA) != pow(2, x-1)) // check bit has been set in register
		{
			TestLibs::test_fail("unexpected register value");
		}
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
