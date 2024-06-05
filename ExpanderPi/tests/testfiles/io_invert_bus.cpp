/*
 * io_invert_bus.cpp
 * 
 * ExpanderPi class > io_invert_bus function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("ExpanderPi class > io_invert_bus()");
	ExpanderPi bus(false);

    for (uint16_t a = 0; a < 65535; a++){
        bus.io_invert_bus(a);  
		if (a != TestLibs::i2c_emulator_read_word_data(TestLibs::MCP23017_IPOLA)){
			TestLibs::test_fail("unexpected register value");
		}
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
