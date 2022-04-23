/*
 * IOZero32.cpp
 * 
 * IOZero32 class test program
 *   
*/

#include <stdio.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IOZero32.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs test;
	test.start_test("IOZero32 class > IOZero32()");
	

	// out of bounds tests
	try
	{
		IOZero32 bus1(0x19);
		test.test_exception_failed("I2C address low out of bounds");
	}
	catch(const std::exception& e){	}

	try
	{
		IOZero32 bus1(0x28);
		test.test_exception_failed("I2C address high out of bounds");
	}
	catch(const std::exception& e){	}

	test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
