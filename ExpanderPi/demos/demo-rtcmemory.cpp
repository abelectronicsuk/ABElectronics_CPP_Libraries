/*
* demo-rtcmemory.cpp
*
*  Version 1.1 Updated 21/04/2020
*
*      compile with "g++ demo-rtcmemory.cpp ../ABE_ExpanderPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o demo-rtcmemory"
*      run with "./demo-rtcmemory"
*
*  This demo shows how to write to and read from the internal battery backed memory on the DS1307 RTC chip
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <iostream>

#include "../ABE_ExpanderPi.h"


int main(int argc, char **argv) {

	using namespace ABElectronics_CPP_Libraries;

	ExpanderPi expi;

	int inval = 6254; // declare the input value

	printf("Number written to SRAM: %d\n", inval);

	unsigned char bytearray[sizeof(inval)]; // byte array to be stored in the RTC SRAM

	int a = 0;

	for (a = 0; a < (int)sizeof(inval); a++) {
		bytearray[a] = (inval >> a * 8) & 0xFF;
	}

	expi.rtc_write_memory(0x08, bytearray, sizeof(inval)); // write the byte array to the RTC SRAM
	
	int outval = 0; // declare the output value

	// read the RTC SRAM into a 4 byte array.  
	// The array is allocated by the rtc_read_memory function, use a pointer to point to the memory location of this array.
	unsigned char *readarray = expi.rtc_read_memory(0x08, sizeof(inval));

	for (a = 0; a < (int)sizeof(outval); a++) { // convert the bytes from the readarray into a number
		outval |= readarray[a] << (a * 8);
	}

	free(readarray); // free the memory allocated to readarray

	printf("Number read from SRAM: %d", outval);

	(void)argc;
	(void)argv;
	return (0);
}