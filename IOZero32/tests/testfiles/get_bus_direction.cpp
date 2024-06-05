/*
 * get_bus_direction.cpp
 * 
 * IOZero32 class > get_bus_direction function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IOZero32.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOZero32 class > get_bus_direction()");
	
    IOZero32 bus(0x20);  // new IOZero32 object
    
    uint16_t x;

    for (uint16_t a = 0; a < 65534; a++){
        TestLibs::i2c_emulator_write_word_data(TestLibs::PCA9535_CONFIGPORT0, a); // set register value
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
