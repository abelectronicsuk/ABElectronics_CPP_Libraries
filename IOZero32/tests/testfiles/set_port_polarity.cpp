/*
 * set_port_polarity.cpp
 * 
 * IOZero32 class > set_port_polarity function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IOZero32.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOZero32 class > set_port_polarity()");
	IOZero32 bus(0x20);

	// out of bounds tests
	try
	{
		bus.set_port_polarity(2, 0);
		TestLibs::test_exception_failed("port high boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
    for (int x = 0; x < 256; x++)
	{
		TestLibs::i2c_emulator_write_word_data(TestLibs::PCA9535_INVERTPORT0, 0); // reset registers

        bus.set_port_polarity(0, x);

		if (TestLibs::i2c_emulator_read_byte_data(TestLibs::PCA9535_INVERTPORT0) != x) // check value has been set in register
		{
			TestLibs::test_fail("unexpected register value");
		}

		TestLibs::i2c_emulator_write_word_data(TestLibs::PCA9535_INVERTPORT0, 0); // reset registers

		bus.set_port_polarity(1, x);
		
		if (TestLibs::i2c_emulator_read_byte_data(TestLibs::PCA9535_INVERTPORT1) != x) // check value has been set in register
		{
			TestLibs::test_fail("unexpected register value");
		}
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
