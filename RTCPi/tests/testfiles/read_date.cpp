/*
 * read_date.cpp
 * 
 * RTCPi class > read_date function test program
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
	test.start_test("RTCPi class > read_date()");
	
    RTCPi rtc;  // new RTCPi object

    // set date register values

    test.i2c_emulator_write_byte_data(test.DS1307_SECONDS, 0x25);
    test.i2c_emulator_write_byte_data(test.DS1307_MINUTES, 0x12);
    test.i2c_emulator_write_byte_data(test.DS1307_HOURS, 0x14);
    test.i2c_emulator_write_byte_data(test.DS1307_DAYOFWEEK, 0x03);
    test.i2c_emulator_write_byte_data(test.DS1307_DAY, 0x11);
    test.i2c_emulator_write_byte_data(test.DS1307_MONTH, 0x09);
    test.i2c_emulator_write_byte_data(test.DS1307_YEAR, 0x20);
    
    struct tm datetime; // create a tm struct to store the date

    datetime = rtc.read_date();

    // set the date
	if (datetime.tm_sec != 25){
            test.test_fail("failed to set seconds");
	}
	if (datetime.tm_min != 12){
            test.test_fail("failed to set minutes");
	}
	if (datetime.tm_hour != 14){
            test.test_fail("failed to set hour");
	}
	if (datetime.tm_wday != 3){
            test.test_fail("failed to set weekday");
	}
	if (datetime.tm_mday != 11){
            test.test_fail("failed to set day");
	}
	if (datetime.tm_mon != 8){
            test.test_fail("failed to set month");
	}
	if (datetime.tm_year != 120){
            test.test_fail("failed to set year");
	}


    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
