/*
 * write_bus.cpp
 * 
 * IOZero32 class > write_bus function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IOZero32.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOZero32 class > write_bus()");

	IOZero32 bus(0x20);  // new IOZero32 object

    for (uint16_t a = 0; a < 65535; a++){
        bus.write_bus(a); 

        uint16_t x;
        
        x = TestLibs::i2c_emulator_read_word_data(TestLibs::PCA9535_OUTPUTPORT0); // read value from registers
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
