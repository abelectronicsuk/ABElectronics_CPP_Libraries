/*
 * set_pin_polarity.cpp
 * 
 * IOZero32 class > set_pin_polarity function test program
 *   
*/

#include <stdexcept>
#include <cmath>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IOZero32.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOZero32 class > set_pin_polarity()");

	IOZero32 bus(0x20);

	// out of bounds tests
	try
	{
		bus.set_pin_polarity(0, 0);
		TestLibs::test_exception_failed("pin low boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	try
	{
		bus.set_pin_polarity(17, 0);
		TestLibs::test_exception_failed("pin high boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	try
	{
		bus.set_pin_polarity(1, 2);
		TestLibs::test_exception_failed("value high boundary out of bounds");
	}
	catch(const std::exception& e){	}

	

    for (int x = 1; x < 17; x++)
	{
		TestLibs::i2c_emulator_write_word_data(TestLibs::PCA9535_INVERTPORT0, 0); // reset register
        bus.set_pin_polarity(x, 1);
		if (TestLibs::i2c_emulator_read_word_data(TestLibs::PCA9535_INVERTPORT0) != pow(2, x-1)) // check bit has been set in register
		{
			TestLibs::test_fail("unexpected register value");
		}
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
