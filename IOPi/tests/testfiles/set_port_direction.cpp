/*
 * set_port_direction.cpp
 * 
 * IOPi class > set_port_direction function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOPi class > set_port_direction()");

	IoPi iopi(0x20, false);

	// out of bounds tests
	try
	{
		iopi.set_port_direction(2, 0);
		TestLibs::test_exception_failed("port high boundary out of bounds");
	}
	catch(const std::exception& e){	}

    uint8_t y;
	
    for (int x = 0; x < 256; x++)
	{
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_IODIRA, 0x00);
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_IODIRB, 0x00);

        iopi.set_port_direction(0, x);
		
        y = TestLibs::i2c_emulator_read_word_data(TestLibs::MCP23017_IODIRA);
        if (x != y){
            TestLibs::test_exception_failed("set port failed on port 0");
            break;
		}

        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_IODIRA, 0x00);
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_IODIRB, 0x00);

        iopi.set_port_direction(1, x);
		
        y = TestLibs::i2c_emulator_read_word_data(TestLibs::MCP23017_IODIRB);
        if (x != y){
            TestLibs::test_exception_failed("set port failed on port 1");
            break;
		}
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
