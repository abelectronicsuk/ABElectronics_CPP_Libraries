/*
 * get_interrupt_type.cpp
 * 
 * IOPi class > get_interrupt_type function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOPi class > get_interrupt_type()");

	IoPi bus(0x20, false);
	uint8_t x;

	// out of bounds tests
	try
	{
		bus.get_interrupt_type(2);
		TestLibs::test_exception_failed("port out of bounds");
	}
	catch (exception &e){}

	for (uint8_t a = 0; a < 255; a++){
		TestLibs::i2c_emulator_write_byte_data(TestLibs::MCP23017_INTCONB, 0);
		TestLibs::i2c_emulator_write_byte_data(TestLibs::MCP23017_INTCONA, a);
        x = bus.get_interrupt_type(0);
        if (x != a){
            TestLibs::test_exception_failed("get port failed when set to 0");
            break;
		}
		TestLibs::i2c_emulator_write_byte_data(TestLibs::MCP23017_INTCONA, 0);
        TestLibs::i2c_emulator_write_byte_data(TestLibs::MCP23017_INTCONB, a);
        x = bus.get_interrupt_type(1);
        if (x != a){
            TestLibs::test_exception_failed("get port failed when set to 1");
            break;
		}
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
