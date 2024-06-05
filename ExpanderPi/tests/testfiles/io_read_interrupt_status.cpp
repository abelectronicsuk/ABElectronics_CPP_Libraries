/*
 * io_read_interrupt_status.cpp
 * 
 * ExpanderPi class > io_read_interrupt_status function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("ExpanderPi class > io_read_interrupt_status()");

	ExpanderPi bus(false);
	uint8_t x;

	// out of bounds tests
	try
	{
		bus.io_read_interrupt_status(2);
		TestLibs::test_exception_failed("high boundary out of bounds");
	}
	catch(const std::exception& e){	}

	for (uint8_t a = 0; a < 255; a++){
		TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_INTFA, a);
        x = bus.io_read_interrupt_status(0);
        if (x != a){
            TestLibs::test_exception_failed("get interrupt status failed  when set to 0");
            break;
		}
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_INTFB, a);
        x = bus.io_read_interrupt_status(1);
        if (x != a){
            TestLibs::test_exception_failed("get interrupt status failed when set to 1");
            break;
		}
	}

	TestLibs::test_outcome();
	
	(void)argc;
	(void)argv;
	return (0);
}
