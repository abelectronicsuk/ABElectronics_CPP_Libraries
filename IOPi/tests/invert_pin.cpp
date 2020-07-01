/*
invert_pin.cpp

Version 1.0 Created 01/07/2020

      compile with "g++ invert_pin.cpp ../ABE_IoPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o invert_pin"
      run with "./invert_pin"
 
This test validates the invert_pin function in the IOPi class.

Hardware Required: Logic Analyser on I2C Pins

=== Expected Result ============================

> Console Output:

pin low boundary check: PASSED
pin high boundary check: PASSED
value high boundary check: PASSED
Logic output Started
Logic output Ended

> Logic Analyser Output:

W 0x20 0xA0 0x02
W 0x20 0x02 0x00 0x00

W 0x20 0x02
R 0x20 0x02 0x00
W 0x20 0x02 0x01

looping to

W 0x20 0x02
R 0x20 0x02 0x7F
W 0x20 0x02 0xFF

W 0x20 0x03
R 0x20 0x03 0x00
W 0x20 0x03 0x01

looping to

W 0x20 0x03
R 0x20 0x03 0x7F
W 0x20 0x03 0xFF


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
		iopi.invert_pin(0, 0);
	}
	catch (exception &e)
	{
		cout << "pin low boundary check: PASSED\n";
	}

	try
	{
		iopi.invert_pin(17, 0);
	}
	catch (exception &e)
	{
		cout << "pin high boundary check: PASSED\n";
	}

	try
	{
		iopi.invert_pin(1, 2);
	}
	catch (exception &e)
	{
		cout << "value high boundary check: PASSED\n";
	}

	// Logic Analyser Check
    cout << "Logic output Started\n";

	iopi.invert_bus(0x0000);

    for (int x = 1; x < 17; x++)
	{
        iopi.invert_pin(x, 1);
	}

    cout << "Logic output Ended\n";

	(void)argc;
	(void)argv;
	return (0);
}
