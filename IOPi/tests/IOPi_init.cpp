/*
IOPi_init.cpp

Version 1.0 Created 01/07/2020

      compile with "g++ IOPi_init.cpp ../ABE_IoPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o IOPi_init"
      run with "./IOPi_init"
 
This test validates the IOPi method in the IOPi class.

Hardware Required: Logic Analyser on I2C Pins

=== Expected Result ============================

> Console Output:

Init low bounds passed
Init high bounds passed
Init creation without initialisation passed
Init creation with initialisation passed

> Logic Analyser Output:

W 0x20 0xA0 0x02

10ms delay

W 0x20 0xA0 0x02
W 0x20 0x00 0xFF 0xFF
W 0x20 0x0C 0x00 0x00
W 0x20 0x02 0x00 0x00

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

	// out of bounds tests
	try
	{
		IoPi bus1(0x19);
	}
	catch (exception &e)
	{
		cout << "Init low bounds passed\n";
	}

	try
	{
		IoPi bus1(0x28);
	}
	catch (exception &e)
	{
		cout << "Init high bounds passed\n";
	}

	try
	{
		IoPi bus2(0x20, false);
		cout << "Init creation without initialisation passed\n";
	}
	catch (exception &e)
	{
		cout << "Init creation without initialisation failed\n";
	}

	usleep(10000);

	try
	{
		IoPi bus3(0x20, true);
		cout << "Init creation with initialisation passed\n";
	}
	catch (exception &e)
	{
		cout << "Init creation with initialisation failed\n";
	}


	(void)argc;
	(void)argv;
	return (0);
}
