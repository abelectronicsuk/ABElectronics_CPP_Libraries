/*
 * io_get_port_polarity.cpp
 * 
 * ExpanderPi class > io_get_port_polarity function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("ExpanderPi class > io_get_port_polarity()");

	ExpanderPi bus(false);
	uint8_t x;

	// out of bounds tests
	try
	{
		bus.io_get_port_polarity(2);
		TestLibs::test_exception_failed("port out of bounds");
	}
	catch (exception &e){}

	for (uint8_t a = 0; a < 255; a++){
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_IPOLA, a);
        x = bus.io_get_port_polarity(0);
        if (x != a){
            TestLibs::test_exception_failed("get port failed when set to 0");
            break;
		}
        TestLibs::i2c_emulator_write_word_data(TestLibs::MCP23017_IPOLB, a);
        x = bus.io_get_port_polarity(1);
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
