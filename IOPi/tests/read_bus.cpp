/*
read_bus.cpp

Version 1.0 Created 01/07/2020

      compile with "g++ read_bus.cpp ../ABE_IoPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o read_bus"
      run with "./read_bus"
 
This test validates the read_bus function in the IOPi class.

Hardware Required: Logic Analyser on I2C Pins

=== Expected Result ============================

> Console Output:

Logic output Started
Logic output Ended

> Logic Analyser Output:

W 0x20 0xA0 0x02
W 0x20 0x12 0x00 0x00
W 0x20 0x00 0xFF 0xFF

W 0x20 0x12
R 0x20 0x00 0x00

"""
 
 */

#include <stdio.h>
#include <stdlib.h>
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

	// Reset to 0
	bus.write_bus(0x0000);

	// Enable pullups
    bus.set_bus_direction(0xFFFF);

	// Logic Analyser Check

	cout << "Logic output Started\n";

	uint16_t x = bus.read_bus();

	cout << "Logic output Ended\n";

	

	(void)argc;
	(void)argv;
	return (0);
}
