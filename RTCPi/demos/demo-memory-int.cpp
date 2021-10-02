/*
* demo-memory-int.cpp
*
*  Version 1.2 Updated 02/10/2021
*
*      compile with "g++ ../ABE_RTCPi.cpp demo-memory-int.cpp -Wall -Wextra -Wpedantic -Woverflow -o demo-memory-int"
*      run with "./demo-memory-int"
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

#include "../ABE_RTCPi.h"


int main(int argc, char **argv) {

	using namespace ABElectronics_CPP_Libraries;

	RTCPi rtc;

	int inval = 6254; // declare the input value

	printf("Number written to SRAM: %d\n", inval);

	uint8_t bytearray[sizeof(inval)]; // byte array to be stored in the RTC SRAM

	int a = 0;

	for (a = 0; a < (int)sizeof(inval); a++) {
		bytearray[a] = (inval >> a * 8) & 0xFF;
	}

	rtc.write_memory(0x08, bytearray, sizeof(inval)); // write the byte array to the RTC SRAM
		
	int outval = 0; // declare the output value

	// read the RTC SRAM into a 4 byte array.  
	// The array is allocated by the rtc_read_memory function, use a pointer to point to the memory location of this array.
	uint8_t *readarray = rtc.read_memory(0x08, (int)sizeof(inval));

	for (a = 0; a < (int)sizeof(outval); a++) { // convert the bytes from the readarray into a number
		outval |= readarray[a] << (a * 8);
	}

	free(readarray); // free the memory allocated to readarray

	printf("Number read from SRAM: %d", outval);

	(void)argc;
	(void)argv;
	return (0);
}
