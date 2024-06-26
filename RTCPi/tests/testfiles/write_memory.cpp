/*
 * write_memory.cpp
 * 
 * RTCPi class > write_memory function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_RTCPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("RTCPi class > write_memory()");
	
    RTCPi rtc;  // new RTCPi object
    
    // out-of-bounds tests
	try
	{
		rtc.write_memory(0x07, nullptr, 1);
		TestLibs::test_exception_failed("read memory address low boundary out of bounds");
	}
	catch(const std::exception& e){	}

    try
	{
		rtc.write_memory(0x40, nullptr, 1);
		TestLibs::test_exception_failed("read memory address high boundary out of bounds");
	}
	catch(const std::exception& e){	}


    // create random values

    const uint8_t size = 56;
    uint8_t x;

    uint8_t bytearray[size];

    for (uint8_t a = 0; a < size; a++){
        bytearray[a] = a;
    }

    rtc.write_memory(0x08, bytearray, size);

    for (uint8_t i = 0; i < size; i++){
        x = TestLibs::i2c_emulator_read_byte_data(0x08 + i); // get register value

        if (x != bytearray[i]){
            TestLibs::test_fail("failed to write memory");
            break;
        }
    }

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
