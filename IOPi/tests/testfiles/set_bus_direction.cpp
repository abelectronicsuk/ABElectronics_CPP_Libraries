/*
 * set_bus_direction.cpp
 * 
 * IOPi class > set_bus_direction function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOPi class > set_bus_direction()");

	IoPi bus(0x20, false);  // new iopi object without initialisation

    uint16_t x;

    for (uint16_t a = 0; a < 65535; a++){
        bus.set_bus_direction(a);      

        x = TestLibs::i2c_emulator_read_word_data(TestLibs::MCP23017_IODIRA); // read value from registers
        if (x != a){
            TestLibs::test_fail("failed to set bus direction");
            break;
		} 
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
