/*
 * set_date.cpp
 * 
 * RTCPi class > set_date function test program
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
	test.start_test("RTCPi class > set_date()");
	
    RTCPi rtc;  // new RTCPi object

    struct tm datetime; // create a tm struct to store the date

	// set the date
	datetime.tm_sec = 31; // seconds
	datetime.tm_min = 26; // minutes
	datetime.tm_hour = 17;// hours
	datetime.tm_wday = 4;// dayofweek
	datetime.tm_mday = 10;// day
	datetime.tm_mon = 06;// month - 1
	datetime.tm_year = 120; // years since 1900

	rtc.set_date(datetime);  // send the date to the RTC Pi

    uint8_t seconds = test.i2c_emulator_read_byte_data(test.DS1307_SECONDS);
    uint8_t minutes = test.i2c_emulator_read_byte_data(test.DS1307_MINUTES);
    uint8_t hours = test.i2c_emulator_read_byte_data(test.DS1307_HOURS);
    uint8_t dayofweek = test.i2c_emulator_read_byte_data(test.DS1307_DAYOFWEEK);
    uint8_t day = test.i2c_emulator_read_byte_data(test.DS1307_DAY);
    uint8_t month = test.i2c_emulator_read_byte_data(test.DS1307_MONTH);
    uint8_t year = test.i2c_emulator_read_byte_data(test.DS1307_YEAR);

    if (seconds != 0x31){
            test.test_fail("failed to set seconds");
	}    

    if (minutes != 0x26){
            test.test_fail("failed to set minutes");
	}

    if (hours != 0x17){
            test.test_fail("failed to set hours");
	}

    if (dayofweek != 0x04){
            test.test_fail("failed to set dayofweek");
	}

    if (day != 0x10){
            test.test_fail("failed to set day");
	}

    if (month != 0x07){
            test.test_fail("failed to set month");
	}

    if (year != 0x20){
            test.test_fail("failed to set year");
	}  

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
