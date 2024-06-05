/*
 * get_pin_polarity.cpp
 * 
 * IOZero32 class > get_pin_polarity function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IOZero32.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOZero32 class > get_pin_polarity()");

	IOZero32 bus(0x20);
	uint8_t x;
	uint16_t y;

	// out of bounds tests
	try
	{
		bus.get_pin_polarity(0);
		TestLibs::test_exception_failed("pin low out of bounds");
	}
	catch (exception &e){}

	try
	{
		bus.get_pin_polarity(17);
		TestLibs::test_exception_failed("pin high out of bounds");
	}
	catch (exception &e){}

	for (uint8_t a = 1; a < 17; a++){
		y = 65535;
		
		y = TestLibs::test_set_bit(y, a-1, false);	
		TestLibs::i2c_emulator_write_word_data(TestLibs::PCA9535_INVERTPORT0, y);
        x = bus.get_pin_polarity(a);
        if (x != 0){
            TestLibs::test_exception_failed("get pin failed on set to 0");
            break;
		}
		y = 0;
		y = TestLibs::test_set_bit(y, a-1, true);
        TestLibs::i2c_emulator_write_word_data(TestLibs::PCA9535_INVERTPORT0, y);
        x = bus.get_pin_polarity(a);
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
