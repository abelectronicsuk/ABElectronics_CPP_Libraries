/*
* demo-rtcout.cpp
*
*  Created on: 12 June 2017
*
*      compile with "g++ ABE_RTCPi.cpp demo-rtcout.cpp -o demo-rtcout"
*      run with "./demo-rtcout"
*
*  This demo shows how to enable the clock square wave output on the RTC Pi and set the frequency
*/

#include <stdio.h>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <iostream>

#include "ABE_RTCPi.h"

int main(int argc, char **argv) {

	using namespace ABElectronics_CPP_Libraries;

	RTCPi rtc;


	
	// set the frequency of the output. Options are : 1 = 1Hz, 2 = 4.096KHz, 3 = 8.192KHz, 4 = 32.768KHz
	rtc.set_frequency(3);

	// enable the square-wave output
	rtc.enable_output();

	return (0);
}
