/*
 * set_bus_polarity.cpp
 * 
 * IOZero32 class > set_bus_polarity function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IOZero32.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOZero32 class > set_bus_polarity()");
	IOZero32 bus(0x20);  // new IOZero32 object

    for (uint16_t a = 0; a < 65535; a++){
        bus.set_bus_polarity(a);  
		if (a != TestLibs::i2c_emulator_read_word_data(TestLibs::PCA9535_INVERTPORT0)){
			TestLibs::test_fail("unexpected register value");
		}
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
