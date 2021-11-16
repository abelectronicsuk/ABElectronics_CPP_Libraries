/*
 * rtc_disable_output.cpp
 * 
 * ExpanderPi class > rtc_disable_output function test program
 *   
*/

#include <stdio.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
    TestLibs test;
	test.start_test("ExpanderPi class > rtc_disable_output()");
	
    ExpanderPi rtc;  // new ExpanderPi object
    
    test.i2c_emulator_write_byte_data(test.DS1307_CONTROL, 0xFF); // set register value

    rtc.rtc_disable_output(); // disable the OUT pin

    uint8_t x = test.i2c_emulator_read_byte_data(test.DS1307_CONTROL);

    if (x != 0x6f){ // register bits 4 and 7 should be set to 0
            test.test_fail("failed to disable output");
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
