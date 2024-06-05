/*
 * get_port_direction.cpp
 * 
 * IOPi class > get_port_direction function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOPi class > get_port_direction()");
    
	IoPi bus(0x20, false);
	uint8_t x;

	// out of bounds tests
	try
	{
		bus.get_port_direction(2);
        TestLibs::test_exception_failed("port out of bounds");
	}

	catch (exception &e){}

	for (uint8_t a = 0; a < 255; a++){
		TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_IODIRA, a);
        x = bus.get_port_direction(0);
        if (x != a){
            TestLibs::test_exception_failed("get port failed when set to 0");
            break;
		}
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_IODIRB, a);
        x = bus.get_port_direction(1);
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
