/*
 * write_port.cpp
 * 
 * IOPi class > write_port function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOPi class > write_port()");

	IoPi iopi(0x20, false);

	// out of bounds tests
	try
	{
		iopi.write_port(2, 0);
		TestLibs::test_exception_failed("port high boundary out of bounds");
	}
	catch(const std::exception& e){	}
	
 
    uint8_t y;
	
    for (int x = 0; x < 256; x++)
	{
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_GPIOA, 0x00);
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_GPIOB, 0x00);

        iopi.write_port(0, x);
		
        y = TestLibs::i2c_emulator_read_word_data(TestLibs::MCP23017_GPIOA);
        if (x != y){
            TestLibs::test_exception_failed("set port failed on port 0");
            break;
		}

        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_GPIOA, 0x00);
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_GPIOB, 0x00);

        iopi.write_port(1, x);
		
        y = TestLibs::i2c_emulator_read_word_data(TestLibs::MCP23017_GPIOB);
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
