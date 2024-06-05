/*
 * io_get_interrupt_on_bus.cpp
 * 
 * ExpanderPi class > io_get_interrupt_on_bus function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("ExpanderPi class > io_get_interrupt_on_bus()");

	uint16_t x;

    ExpanderPi bus(false);

    for (uint16_t a = 0; a < 65535; a++){
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_GPINTENA, a);
        x = bus.io_get_interrupt_on_bus();
        if (x != a){
            TestLibs::test_fail("failed to get interrupt on bus");
            break;
		}        
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
