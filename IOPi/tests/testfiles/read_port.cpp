/*
 * read_port.cpp
 * 
 * IOPi class > read_port function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOPi class > read_port()");

	IoPi bus(0x20, true);
	uint8_t x;

	// out of bounds tests
	try
	{
		bus.read_port(2);
		TestLibs::test_exception_failed("high boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
	for (uint8_t a = 0; a < 255; a++){
		TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_GPIOA, a);
        x = bus.read_port(0);
        if (x != a){
            TestLibs::test_exception_failed("get port value failed when set to 0");
            break;
		}
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_GPIOB, a);
        x = bus.read_port(1);
        if (x != a){
            TestLibs::test_exception_failed("get port value failed when set to 1");
            break;
		}
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
