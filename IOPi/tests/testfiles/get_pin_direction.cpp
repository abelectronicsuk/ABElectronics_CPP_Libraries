/*
get_pin_direction.cpp
 * 
 * IOPi class > get_pin_direction function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOPi class > get_pin_direction()");

	IoPi bus(0x20, false);
	uint8_t x;
	uint16_t y;

	// out of bounds tests
	try
	{
		bus.get_pin_direction(0);
		TestLibs::test_exception_failed("pin low out of bounds");
	}
	catch (exception &e){}

	try
	{
		bus.get_pin_direction(17);
		TestLibs::test_exception_failed("pin high out of bounds");
	}
	catch (exception &e){}

	for (uint8_t a = 1; a < 17; a++){
		y = 65535;
		
		y = TestLibs::test_set_bit(y, a-1, false);	
		TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_IODIRA, y);
        x = bus.get_pin_direction(a);
        if (x != 0){
            TestLibs::test_exception_failed("get pin failed on set to 0");
            break;
		}
		y = 0;
		y = TestLibs::test_set_bit(y, a-1, true);
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_IODIRA, y);
        x = bus.get_pin_direction(a);
        if (x != 1){
            TestLibs::test_exception_failed("get pin failed on set to 1");
            break;
		}
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
