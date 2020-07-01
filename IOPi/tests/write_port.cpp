/*
write_port.cpp

Version 1.0 Created 01/07/2020

      compile with "g++ write_port.cpp ../ABE_IoPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o write_port"
      run with "./write_port"
 
This test validates the write_port function in the IOPi class.

Hardware Required: Logic Analyser on I2C Pins

=== Expected Result ============================

> Console Output:

port high boundary check: PASSED
Logic output Started
Logic output Ended

> Logic Analyser Output:

W 0x20 0xA0 0x02
W 0x20 0x12 0x00 0x00

W 0x20 0x12 0x00
W 0x20 0x13 0x00

looping to

W 0x20 0x12 0xFF
W 0x20 0x13 0xFF


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

	IoPi iopi(0x20, false);

	// out of bounds tests
	try
	{
		iopi.write_port(2, 0);
	}
	catch (exception &e)
	{
		cout << "port high boundary check: PASSED\n";
	}

	// Logic Analyser Check
    cout << "Logic output Started\n";


    for (int x = 0; x < 256; x++)
	{
        iopi.write_port(0, x);
		iopi.write_port(1, x);
	}

    cout << "Logic output Ended\n";

	(void)argc;
	(void)argv;
	return (0);
}
