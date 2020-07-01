/*
set_bus_pullups.cpp

Version 1.0 Created 01/07/2020

      compile with "g++ set_bus_pullups.cpp ../ABE_IoPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o set_bus_pullups"
      run with "./set_bus_pullups"
 
This test validates the set_bus_pullups method in the IOPi class.

Hardware Required: Logic Analyser on I2C Pins

=== Expected Result ============================

> Console Output:

Logic output Started
Logic output Ended

> Logic Analyser Output:

W 0x20 0xA0 0x02

W 0x20 0x0C 0x00 0x00

looping to

W 0x20 0x0C 0xFE 0xFF

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

	IoPi bus(0x20, false);  // new iopi object without initialisation

	// Logic Analyser Check
    cout << "Logic output Started\n";

    for (uint16_t a = 0; a < 65535; a++){
        bus.set_bus_pullups(a);      
	}

    cout << "Logic output Ended\n";

	(void)argc;
	(void)argv;
	return (0);
}
