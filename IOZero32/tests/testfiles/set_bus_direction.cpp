/*
 * set_bus_direction.cpp
 * 
 * IOZero32 class > set_bus_direction function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IOZero32.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOZero32 class > set_bus_direction()");

	IOZero32 bus(0x20);  // new IOZero32 object

    uint16_t x;

    for (uint16_t a = 0; a < 65535; a++){
        bus.set_bus_direction(a);      

        x = TestLibs::i2c_emulator_read_word_data(TestLibs::PCA9535_CONFIGPORT0); // read value from registers
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
