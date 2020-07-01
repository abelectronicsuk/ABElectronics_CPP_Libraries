/*
write_bus.cpp

Version 1.0 Created 01/07/2020

      compile with "g++ write_bus.cpp ../ABE_IoPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o write_bus"
      run with "./write_bus"
 
This test validates the write_bus method in the IOPi class.

Hardware Required: Logic Analyser on I2C Pins

=== Expected Result ============================

> Console Output:

Logic output Started
Logic output Ended

> Logic Analyser Output:

W 0x20 0xA0 0x02

W 0x20 0x12 0x00 0x00

looping to

W 0x20 0x12 0xFE 0xFF

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
        bus.write_bus(a);      
	}

    cout << "Logic output Ended\n";

	(void)argc;
	(void)argv;
	return (0);
}
