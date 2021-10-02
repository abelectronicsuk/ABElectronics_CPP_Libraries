/*
 * disable_output.cpp
 * 
 * RTCPi class > disable_output function test program
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
	test.start_test("RTCPi class > disable_output()");
	
    RTCPi rtc;  // new RTCPi object
    
    test.i2c_emulator_write_byte_data(test.DS1307_CONTROL, 0xFF); // set register value

    rtc.disable_output(); // disable the OUT pin

    uint8_t x = test.i2c_emulator_read_byte_data(test.DS1307_CONTROL);

    if (x != 0x6f){ // register bits 4 and 7 should be set to 0
            test.test_fail("failed to disable output");
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
