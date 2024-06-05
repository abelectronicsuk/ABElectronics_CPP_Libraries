/*
 * get_bus_direction.cpp
 * 
 * IOPi class > get_bus_direction function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOPi class > get_bus_direction()");
	
    IoPi bus(0x20, false);  // new IoPi object without initialization
    
    uint16_t x;

    for (uint16_t a = 0; a < 65534; a++){
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_IODIRA, a); // set register value
        x = bus.get_bus_direction(); // read value from registers
        if (x != a){
            TestLibs::test_fail("failed to get bus direction");
            break;
		}        
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
