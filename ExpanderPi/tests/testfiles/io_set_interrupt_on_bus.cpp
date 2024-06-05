/*
 * io_set_interrupt_on_bus.cpp
 * 
 * ExpanderPi class > io_set_interrupt_on_bus function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("ExpanderPi class > io_set_interrupt_on_bus()");

	ExpanderPi bus(false);
    
    uint16_t x;

    for (uint16_t a = 0; a < 65535; a++){
        bus.io_set_interrupt_on_bus(a);      

        x = TestLibs::i2c_emulator_read_word_data(TestLibs::MCP23017_GPINTENA); // read value from registers
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
