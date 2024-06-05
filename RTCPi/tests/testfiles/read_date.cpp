/*
 * read_date.cpp
 * 
 * RTCPi class > read_date function test program
 *   
*/

#include <iostream>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_RTCPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("RTCPi class > read_date()");
	
    RTCPi rtc;  // new RTCPi object

    // set date register values

    TestLibs::i2c_emulator_write_byte_data(TestLibs::DS1307_SECONDS, 0x25);
    TestLibs::i2c_emulator_write_byte_data(TestLibs::DS1307_MINUTES, 0x12);
    TestLibs::i2c_emulator_write_byte_data(TestLibs::DS1307_HOURS, 0x14);
    TestLibs::i2c_emulator_write_byte_data(TestLibs::DS1307_DAYOFWEEK, 0x03);
    TestLibs::i2c_emulator_write_byte_data(TestLibs::DS1307_DAY, 0x11);
    TestLibs::i2c_emulator_write_byte_data(TestLibs::DS1307_MONTH, 0x09);
    TestLibs::i2c_emulator_write_byte_data(TestLibs::DS1307_YEAR, 0x20);
    
    struct tm datetime = rtc.read_date();

    // set the date
	if (datetime.tm_sec != 25){
            TestLibs::test_fail("failed to set seconds");
	}
	if (datetime.tm_min != 12){
            TestLibs::test_fail("failed to set minutes");
	}
	if (datetime.tm_hour != 14){
            TestLibs::test_fail("failed to set hour");
	}
	if (datetime.tm_wday != 3){
            TestLibs::test_fail("failed to set weekday");
	}
	if (datetime.tm_mday != 11){
            TestLibs::test_fail("failed to set day");
	}
	if (datetime.tm_mon != 8){
            TestLibs::test_fail("failed to set month");
	}
	if (datetime.tm_year != 120){
            TestLibs::test_fail("failed to set year");
	}


    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
