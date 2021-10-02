/*
 * set_frequency.cpp
 * 
 * RTCPi class > set_frequency function test program
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
	test.start_test("RTCPi class > set_frequency()");
	
    RTCPi rtc;  // new RTCPi object

    uint8_t x = 0;

    // out of bounds tests
	try
	{
		rtc.set_frequency(0);
		test.test_exception_failed("set frequency low boundary out of bounds");
	}
	catch(const std::exception& e){	}

    try
	{
		rtc.set_frequency(5);
		test.test_exception_failed("set frequency high boundary out of bounds");
	}
	catch(const std::exception& e){	}
    
    // 1Hz test
    test.i2c_emulator_write_byte_data(test.DS1307_CONTROL, 0xFF); // set register value

    rtc.set_frequency(1); // set frequency to 1Hz

    x = test.i2c_emulator_read_byte_data(test.DS1307_CONTROL);

    if (x != 0xfc){ // register bits 0 and 1 should be set to 0
            test.test_fail("failed to set 1hz");
	}

    // 4.096KHz test
    test.i2c_emulator_write_byte_data(test.DS1307_CONTROL, 0xFF); // set register value

    rtc.set_frequency(2); // set frequency to 4.096KHz

    x = test.i2c_emulator_read_byte_data(test.DS1307_CONTROL);

    if (x != 0xfd){ // register bits 0 and 1 should be set to 0
            test.test_fail("failed to set 4.096KHz");
	}

    // 8.192KHz test
    test.i2c_emulator_write_byte_data(test.DS1307_CONTROL, 0xFF); // set register value

    rtc.set_frequency(3); // set frequency to 8.192KHz

    x = test.i2c_emulator_read_byte_data(test.DS1307_CONTROL);

    if (x != 0xfe){ // register bits 0 and 1 should be set to 0
            test.test_fail("failed to set 8.192KHz");
	}

    // 32.768KHz
    test.i2c_emulator_write_byte_data(test.DS1307_CONTROL, 0x00); // set register value

    rtc.set_frequency(4); // set frequency to 32.768KHz

    x = test.i2c_emulator_read_byte_data(test.DS1307_CONTROL);

    if (x != 0x03){ // register bits 0 and 1 should be set to 0
            test.test_fail("failed to set 32.768KHz");
	}

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
