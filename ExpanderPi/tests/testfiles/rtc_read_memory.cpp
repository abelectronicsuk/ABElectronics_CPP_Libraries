/*
 * rtc_read_memory.cpp
 * 
 * ExpanderPi class > rtc_read_memory function test program
 *   
*/

#include <stdio.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
    TestLibs test;
	test.start_test("ExpanderPi class > rtc_read_memory()");
	
    ExpanderPi rtc;  // new ExpanderPi object
    
    // out of bounds tests
	try
	{
		rtc.rtc_read_memory(0x07, 1);
		test.test_exception_failed("read memory address low boundary out of bounds");
	}
	catch(const std::exception& e){	}

    try
	{
		rtc.rtc_read_memory(0x40, 1);
		test.test_exception_failed("read memory address high boundary out of bounds");
	}
	catch(const std::exception& e){	}

    try
	{
		rtc.rtc_read_memory(0x08, 0);
		test.test_exception_failed("read memory length low boundary out of bounds");
	}
	catch(const std::exception& e){	}

    try
	{
		rtc.rtc_read_memory(0x08, 57);
		test.test_exception_failed("read memory length high boundary out of bounds");
	}
	catch(const std::exception& e){	}

    // create random values

    const uint8_t size = 56;

    uint8_t bytearray[size];

    for (uint8_t i = 0; i < size; i++){
        bytearray[i] = i;
        test.i2c_emulator_write_byte_data(0x08 + i, i); // set register value
    }

    uint8_t *readarray = rtc.rtc_read_memory(0x08, size);

	for (uint8_t a = 0; a < size; a++) { // convert the bytes from the readarray into a number
		if (readarray[a] != bytearray[a]){
            test.test_fail("failed to read memory");
            break;
        }
	}

	free(readarray); // free the memory allocated to readarray

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
