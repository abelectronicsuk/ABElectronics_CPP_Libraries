/*
 * set_port_direction.cpp
 * 
 * IOZero32 class > set_port_direction function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IOZero32.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOZero32 class > set_port_direction()");

	IOZero32 bus(0x20);

	// out of bounds tests
	try
	{
		bus.set_port_direction(2, 0);
		TestLibs::test_exception_failed("port high boundary out of bounds");
	}
	catch(const std::exception& e){	}

    uint8_t y;
	
    for (int x = 0; x < 256; x++)
	{
        TestLibs::i2c_emulator_write_word_data(TestLibs::PCA9535_CONFIGPORT0, 0x00);
        TestLibs::i2c_emulator_write_word_data(TestLibs::PCA9535_CONFIGPORT1, 0x00);

        bus.set_port_direction(0, x);
		
        y = TestLibs::i2c_emulator_read_word_data(TestLibs::PCA9535_CONFIGPORT0);
        if (x != y){
            TestLibs::test_exception_failed("set port failed on port 0");
            break;
		}

        TestLibs::i2c_emulator_write_word_data(TestLibs::PCA9535_CONFIGPORT0, 0x00);
        TestLibs::i2c_emulator_write_word_data(TestLibs::PCA9535_CONFIGPORT1, 0x00);

        bus.set_port_direction(1, x);
		
        y = TestLibs::i2c_emulator_read_word_data(TestLibs::PCA9535_CONFIGPORT1);
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
