/*
 * io_write_bus.cpp
 * 
 * ExpanderPi class > io_write_bus function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("ExpanderPi class > io_write_bus()");

	ExpanderPi bus(false);

    for (uint16_t a = 0; a < 65535; a++){
        bus.io_write_bus(a); 

        uint16_t x;
        
        x = TestLibs::i2c_emulator_read_word_data(TestLibs::MCP23017_GPIOA); // read value from registers
        if (x != a){
            TestLibs::test_fail("failed to set bus value");
            break;
		}
    }

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
