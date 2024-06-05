/*
 * write_bus.cpp
 * 
 * IOPi class > write_bus function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOPi class > write_bus()");

	IoPi bus(0x20, false);  // new iopi object without initialisation

    for (uint16_t a = 0; a < 65535; a++){
        bus.write_bus(a); 

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
