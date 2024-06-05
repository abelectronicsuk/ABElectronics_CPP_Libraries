/*
 * read_bus.cpp
 * 
 * IOZero32 class > read_bus function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IOZero32.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOZero32 class > read_bus()");

    IOZero32 bus(0x20);  // new IOZero32 object

	// Reset to 0
	bus.write_bus(0x0000);

	// Enable pullups
    bus.set_bus_direction(0xFFFF);

	uint16_t x;

    for (uint16_t a = 0; a < 65534; a++){
        TestLibs::i2c_emulator_write_word_data(TestLibs::PCA9535_INPUTPORT0, a); // set register value
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
