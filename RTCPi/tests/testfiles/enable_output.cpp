/*
 * enable_output.cpp
 * 
 * RTCPi class > enable_output function test program
 *   
*/

#include <stdio.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_RTCPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
    TestLibs test;
	test.start_test("RTCPi class > enable_output()");
	
    RTCPi rtc;  // new RTCPi object
    
    test.i2c_emulator_write_byte_data(test.DS1307_CONTROL, 0x00); // set register value

    rtc.enable_output(); // enable the OUT pin

    uint8_t x = test.i2c_emulator_read_byte_data(test.DS1307_CONTROL);

    if (x != 0x90){ // register bits 4 and 7 should be set to 1
            test.test_fail("failed to enable output");
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
