/*
 * read_interrupt_capture.cpp
 * 
 * IOPi class > read_interrupt_capture function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOPi class > read_interrupt_capture()");

	IoPi bus(0x20, false);
	uint8_t x;

	// out of bounds tests
	try
	{
		bus.read_interrupt_capture(2);
		TestLibs::test_exception_failed("high boundary out of bounds");
	}
	catch(const std::exception& e){	}

	for (uint8_t a = 0; a < 255; a++){
		TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_INTCAPA, a);
        x = bus.read_interrupt_capture(0);
        if (x != a){
            TestLibs::test_exception_failed("get interrupt capture failed when set to 0");
            break;
		}
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_INTCAPB, a);
        x = bus.read_interrupt_capture(1);
        if (x != a){
            TestLibs::test_exception_failed("get interrupt capture failed when set to 1");
            break;
		}
	}

	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
