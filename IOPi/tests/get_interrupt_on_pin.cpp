/*
get_interrupt_on_pin.cpp

Version 1.0 Created 01/07/2020

      compile with "g++ get_interrupt_on_pin.cpp ../ABE_IoPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o get_interrupt_on_pin"
      run with "./get_interrupt_on_pin"
 
This test validates the get_interrupt_on_pin method in the IOPi class.

Hardware Required: Logic Analyser on I2C Pins

=== Expected Result ============================

> Console Output:

low boundary check: PASSED
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
		bus.get_interrupt_on_pin(0);
		passed = false;
	}
	catch (exception &e)
	{
		cout << "low boundary check: PASSED\n";
	}
	try
	{
		bus.get_interrupt_on_pin(17);
		passed = false;
	}
	catch (exception &e)
	{
		cout << "high boundary check: PASSED\n";
	}

	for (uint8_t a = 1; a < 17; a++){
         bus.set_interrupt_on_pin(a, 0);
        x = bus.get_interrupt_on_pin(a);
        if (x != 0){
            passed = false;
            break;
		}
        bus.set_interrupt_on_pin(a, 1);
        x = bus.get_interrupt_on_pin(a);
        if (x != 1){
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
