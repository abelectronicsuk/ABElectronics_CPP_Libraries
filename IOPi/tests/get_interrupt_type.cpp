/*
get_interrupt_type.cpp

Version 1.0 Created 01/07/2020

      compile with "g++ get_interrupt_type.cpp ../ABE_IoPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o get_interrupt_type"
      run with "./get_interrupt_type"
 
This test validates the get_interrupt_type method in the IOPi class.

Hardware Required: Logic Analyser on I2C Pins

=== Expected Result ============================

> Console Output:

high boundary check: PASSED
Test Passed

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

	IoPi bus(0x20, false);
	bool passed = true;
	uint8_t x = 0;

	// out of bounds tests
	try
	{
		bus.get_interrupt_type(2);
		passed = false;
	}
	catch (exception &e)
	{
		cout << "high boundary check: PASSED\n";
	}

	for (uint8_t a = 0; a < 255; a++){
         bus.set_interrupt_type(0, a);
        x = bus.get_interrupt_type(0);
        if (x != a){
            passed = false;
            break;
		}
        bus.set_interrupt_type(1, a);
        x = bus.get_interrupt_type(1);
        if (x != a){
            passed = false;
            break;
		}
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
