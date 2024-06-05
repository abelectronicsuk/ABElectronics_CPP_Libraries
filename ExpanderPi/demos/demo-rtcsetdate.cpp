/*
* demo-rtcsetdate.cpp
*
 *  Version 1.2 Updated 28/05/2024
*
*      compile with "g++ demo-rtcsetdate.cpp ../ABE_ExpanderPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o demo-rtcsetdate"
*      run with "./demo-rtcsetdate"
*
*  This demo shows how to write a date to the RTC and read it back again.
*/
#include <cstdint>
#include <cstdio>
#include <ctime>
#include <unistd.h>

#include "../ABE_ExpanderPi.h"

int main() {

	using namespace ABElectronics_CPP_Libraries;

	ExpanderPi expi;
	
	struct tm datetime{}; // Create a tm struct to store the date

	// set the date
	datetime.tm_sec = 00; // seconds
	datetime.tm_min = 20; // minutes
	datetime.tm_hour = 17;// hours
	datetime.tm_wday = 4;// dayofweek
	datetime.tm_mday = 10;// day
	datetime.tm_mon = 06;// month - 1
	datetime.tm_year = 117; // years since 1900

	expi.rtc_set_date(datetime);  // send the date to the RTC Pi
	
	char buffer[80]; // used for converting the date to a string
	
	while (true) {
		datetime = expi.rtc_read_date(); // read the date from the RTC into the tm struct

		if (strftime(buffer, sizeof buffer, "%Y-%m-%dT%H:%M:%S", &datetime)) { // convert the date into a string and print it to the console
			puts(buffer);
		}
		else {
			puts("strftime failed");
		}

		usleep(1000000); // sleep for a second
	}
}
