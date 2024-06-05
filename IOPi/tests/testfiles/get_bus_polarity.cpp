/*
 * get_bus_polarity.cpp
 * 
 * IOPi class > get_bus_polarity function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOPi class > get_bus_polarity()");

    IoPi bus(0x20, false);  // new IoPi object without initialization
    
    uint16_t x;

    for (uint16_t a = 0; a < 65534; a++){
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_IPOLA, a); // set register value
        x = bus.get_bus_polarity(); // read value from registers
        if (x != a){
            TestLibs::test_fail("failed to get bus polarity");
            break;
		}        
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
