/*
 * set_interrupt_defaults.cpp
 * 
 * IOPi class > set_interrupt_defaults function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOPi class > set_interrupt_defaults()");

	IoPi iopi(0x20, false);

	// out of bounds tests
	try
	{
		iopi.set_interrupt_defaults(2, 0);
		TestLibs::test_exception_failed("port high boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
    uint8_t x;
    uint8_t y;

    for (int i = 0; i < 256; i++)
	{
        iopi.set_interrupt_defaults(0, i);
		iopi.set_interrupt_defaults(1, i);
        
        x = TestLibs::i2c_emulator_read_byte_data(TestLibs::MCP23017_DEFVALA); // read value from registers
        if (x != i){
            TestLibs::test_fail("failed to set interrupt default for port 0");
            break;
		}

        y = TestLibs::i2c_emulator_read_byte_data(TestLibs::MCP23017_DEFVALB); // read value from registers
        if (y != i){
            TestLibs::test_fail("failed to set interrupt default for port 1");
            break;
		}
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
