/*
 * io_read_bus.cpp
 * 
 * ExpanderPi class > io_read_bus function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("ExpanderPi class > io_read_bus()");

    ExpanderPi bus(false);

	uint16_t x;

    for (uint16_t a = 0; a < 65534; a++){
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_GPIOA, a); // set register value
        x = bus.io_read_bus(); // read value from registers
        if (x != a){
            TestLibs::test_fail("failed to get bus value");
            break;
		}        
	}

	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
