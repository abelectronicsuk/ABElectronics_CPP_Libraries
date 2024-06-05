/*
 * rtc_set_date.cpp
 * 
 * ExpanderPi class > rtc_set_date function test program
 *   
*/

#include <stdexcept>
#include <iostream>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("ExpanderPi class > rtc_set_date()");
	
    ExpanderPi rtc;  // new ExpanderPi object

    struct tm datetime{}; // create a tm struct to store the date

	// set the date
	datetime.tm_sec = 31; // seconds
	datetime.tm_min = 26; // minutes
	datetime.tm_hour = 17;// hours
	datetime.tm_wday = 4;// dayofweek
	datetime.tm_mday = 10;// day
	datetime.tm_mon = 06;// month - 1
	datetime.tm_year = 120; // years since 1900

	rtc.rtc_set_date(datetime);  // send the date to the RTC Pi

    uint8_t seconds = TestLibs::i2c_emulator_read_byte_data(TestLibs::DS1307_SECONDS);
    uint8_t minutes = TestLibs::i2c_emulator_read_byte_data(TestLibs::DS1307_MINUTES);
    uint8_t hours = TestLibs::i2c_emulator_read_byte_data(TestLibs::DS1307_HOURS);
    uint8_t dayofweek = TestLibs::i2c_emulator_read_byte_data(TestLibs::DS1307_DAYOFWEEK);
    uint8_t day = TestLibs::i2c_emulator_read_byte_data(TestLibs::DS1307_DAY);
    uint8_t month = TestLibs::i2c_emulator_read_byte_data(TestLibs::DS1307_MONTH);
    uint8_t year = TestLibs::i2c_emulator_read_byte_data(TestLibs::DS1307_YEAR);

    if (seconds != 0x31){
            TestLibs::test_fail("failed to set seconds");
	}    

    if (minutes != 0x26){
            TestLibs::test_fail("failed to set minutes");
	}

    if (hours != 0x17){
            TestLibs::test_fail("failed to set hours");
	}

    if (dayofweek != 0x04){
            TestLibs::test_fail("failed to set dayofweek");
	}

    if (day != 0x10){
            TestLibs::test_fail("failed to set day");
	}

    if (month != 0x07){
            TestLibs::test_fail("failed to set month");
	}

    if (year != 0x20){
            TestLibs::test_fail("failed to set year");
	}  

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
