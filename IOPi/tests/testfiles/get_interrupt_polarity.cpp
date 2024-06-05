/*
 * get_interrupt_polarity.cpp
 * 
 * IOPi class > get_interrupt_polarity function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("IOPi class > get_interrupt_polarity()");

	IoPi bus(0x20, false);

	uint8_t x;

	TestLibs::i2c_emulator_write_byte_data(TestLibs::MCP23017_IOCON, 0xfd);
    x = bus.get_interrupt_polarity();
    if (x != 0){
        TestLibs::test_exception_failed("get port failed when set to 0");
	}
    
	TestLibs::i2c_emulator_write_byte_data(TestLibs::MCP23017_IOCON, 0x02);
    x = bus.get_interrupt_polarity();
    if (x != 1){
        TestLibs::test_exception_failed("get port failed when set to 0");
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
