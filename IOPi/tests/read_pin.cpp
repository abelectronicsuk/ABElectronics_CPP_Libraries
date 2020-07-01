/*
read_pin.cpp

Version 1.0 Created 01/07/2020

      compile with "g++ read_pin.cpp ../ABE_IoPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o read_pin"
      run with "./read_pin"
 
This test validates the read_pin method in the IOPi class.

Hardware Required: Logic Analyser on I2C Pins

=== Expected Result ============================

> Console Output:

pin low boundary check: PASSED
pin high boundary check: PASSED
Logic output Started
Logic output Ended

> Logic Analyser Output:

W 0x20 0xA0 0x02
W 0x20 0x12 0xFF 0xFF
W 0x20 0x0C 0x00 0x00
W 0x20 0x02 0x00 0x00

W 0x20 0x12
R 0x20 0x00

looping 8 times

W 0x20 0x13
R 0x20 0x00

looping 8 times

"""
 
 */

#include <stdio.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include "../ABE_IoPi.h"

using namespace std;

void clearscreen()
{
	printf("\033[2J\033[1;1H");
}

int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0); // needed to print to the command line

	using namespace ABElectronics_CPP_Libraries;

	IoPi bus(0x20, true);
	bool passed = true;

	// out of bounds tests
	try
	{
		bus.read_pin(0);
		passed = false;
	}
	catch (exception &e)
	{
		cout << "low boundary check: PASSED\n";
	}
	try
	{
		bus.read_pin(17);
		passed = false;
	}
	catch (exception &e)
	{
		cout << "high boundary check: PASSED\n";
	}

	for (uint8_t a = 1; a < 17; a++){
        bus.read_pin(a);        
	}

    if (passed){
        cout << "Test passed\n";
	}
    else{
        cout << "Test Failed\n";
	}

	(void)argc;
	(void)argv;
	return (0);
}
