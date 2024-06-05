/*
 * enable_output.cpp
 * 
 * RTCPi class > enable_output function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_RTCPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("RTCPi class > enable_output()");
	
    RTCPi rtc;  // new RTCPi object
    
    TestLibs::i2c_emulator_write_byte_data(TestLibs::DS1307_CONTROL, 0x00); // set register value

    rtc.enable_output(); // enable the OUT pin

    uint8_t x = TestLibs::i2c_emulator_read_byte_data(TestLibs::DS1307_CONTROL);

    if (x != 0x90){ // register bits 4 and 7 should be set to 1
            TestLibs::test_fail("failed to enable output");
	}

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
