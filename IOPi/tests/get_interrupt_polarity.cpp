/*
get_interrupt_polarity.cpp

Version 1.0 Created 01/07/2020

      compile with "g++ get_interrupt_polarity.cpp ../ABE_IoPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o get_interrupt_polarity"
      run with "./get_interrupt_polarity"
 
This test validates the get_interrupt_polarity method in the IOPi class.

Hardware Required: Logic Analyser on I2C Pins

=== Expected Result ============================

> Console Output:

Test Passed

 
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

	bus.set_interrupt_polarity(0);
    x = bus.get_interrupt_polarity();
    if (x != 0){
        passed = false;
	}
    bus.set_interrupt_polarity(1);
    x = bus.get_interrupt_polarity();
    if (x != 1){
        passed = false;
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
