/*
 * rtc_disable_output.cpp
 * 
 * ExpanderPi class > rtc_disable_output function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("ExpanderPi class > rtc_disable_output()");
	
    ExpanderPi rtc;  // new ExpanderPi object
    
    TestLibs::i2c_emulator_write_byte_data(TestLibs::DS1307_CONTROL, 0xFF); // set register value

    rtc.rtc_disable_output(); // disable the OUT pin

    uint8_t x = TestLibs::i2c_emulator_read_byte_data(TestLibs::DS1307_CONTROL);

    if (x != 0x6f){ // register bits 4 and 7 should be set to 0
            TestLibs::test_fail("failed to disable output");
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
