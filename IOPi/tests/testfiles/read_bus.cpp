/*
 * read_bus.cpp
 * 
 * IOPi class > read_bus function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOPi class > read_bus()");

    IoPi bus(0x20, false);  // new iopi object without initialisation

	// Reset to 0
	bus.write_bus(0x0000);

	// Enable pullups
    bus.set_bus_direction(0xFFFF);

	uint16_t x;

    for (uint16_t a = 0; a < 65534; a++){
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_GPIOA, a); // set register value
        x = bus.read_bus(); // read value from registers
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
