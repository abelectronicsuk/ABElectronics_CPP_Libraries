/*
* demo-rtcmemory.cpp
*
 *  Version 1.2 Updated 28/05/2024
*
*      compile with "g++ demo-rtcmemory.cpp ../ABE_ExpanderPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o demo-rtcmemory"
*      run with "./demo-rtcmemory"
*
*  This demo shows how to write to and read from the internal battery-backed memory on the DS1307 RTC chip
*/
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <ctime>


#include "../ABE_ExpanderPi.h"


int main(int argc, char **argv) {

	using namespace ABElectronics_CPP_Libraries;

	ExpanderPi expi;

	int input_value = 6254; // declare the input value

	printf("Number written to SRAM: %d\n", input_value);

	unsigned char bytearray[sizeof(input_value)]; // byte array to be stored in the RTC SRAM

    int a;

	for (a = 0; a < (int)sizeof(input_value); a++) {
		bytearray[a] = (input_value >> a * 8) & 0xFF;
	}

	expi.rtc_write_memory(0x08, bytearray, sizeof(input_value)); // write the byte array to the RTC SRAM
	
	int out_value = 0; // declare the output value

	// read the RTC SRAM into a 4-byte array.  
	// The array is allocated by the rtc_read_memory function, use a pointer to point to the memory location of this array.
	unsigned char *read_array = expi.rtc_read_memory(0x08, sizeof(input_value));

	for (a = 0; a < (int)sizeof(out_value); a++) { // convert the bytes from the read_array into a number
        out_value |= read_array[a] << (a * 8);
	}

	free(read_array); // free the memory allocated to read_array

	printf("Number read from SRAM: %d", out_value);

	(void)argc;
	(void)argv;
	return (0);
}