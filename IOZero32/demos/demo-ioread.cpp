/*
 * demo-ioread.cpp
 *
 *      compile with "g++ demo-ioread.cpp ../ABE_IOZero32.cpp -Wall -Wextra -Wpedantic -Woverflow -o demo-ioread"
 *      run with "./demo-ioread"
 * 
 *  This demo sets all pins on the IO Zero 32 as inputs and reads from each pin individually.
 * 
 *  Pull-up or pull-down resistors may be needed to keep the inputs from sitting in a floating state. 
 */

#include <stdio.h>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include "../ABE_IOZero32.h"

using namespace std;

void clearscreen()
{
	printf("\033[2J\033[1;1H");
}

int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0); // needed to print to the command line

	using namespace ABElectronics_CPP_Libraries;

	try
	{
		IOZero32 bus1(0x20);
		IOZero32 bus2(0x21);

		// initialise one of the io pi buses on I2C address  default address for bus 1

		bus1.set_port_direction(0, 0xFF); // set bank 0 to be inputs
		bus1.set_port_direction(1, 0xFF); // set bank 1 to be inputs

		bus2.set_port_direction(0, 0xFF); // set bank 0 to be inputs
		bus2.set_port_direction(1, 0xFF); // set bank 1 to be inputs

		while (1)
		{
			clearscreen();
			printf("Bus 1 Pin 1:  %x		Bus 2 Pin 1:  %x\n", bus1.read_pin(1), bus2.read_pin(1));
			printf("Bus 1 Pin 2:  %x		Bus 2 Pin 2:  %x\n", bus1.read_pin(2), bus2.read_pin(2));
			printf("Bus 1 Pin 3:  %x		Bus 2 Pin 3:  %x\n", bus1.read_pin(3), bus2.read_pin(3));
			printf("Bus 1 Pin 4:  %x		Bus 2 Pin 4:  %x\n", bus1.read_pin(4), bus2.read_pin(4));
			printf("Bus 1 Pin 5:  %x		Bus 2 Pin 5:  %x\n", bus1.read_pin(5), bus2.read_pin(5));
			printf("Bus 1 Pin 6:  %x		Bus 2 Pin 6:  %x\n", bus1.read_pin(6), bus2.read_pin(6));
			printf("Bus 1 Pin 7:  %x		Bus 2 Pin 7:  %x\n", bus1.read_pin(7), bus2.read_pin(7));
			printf("Bus 1 Pin 8:  %x		Bus 2 Pin 8:  %x\n", bus1.read_pin(8), bus2.read_pin(8));
			printf("Bus 1 Pin 9:  %x		Bus 2 Pin 9:  %x\n", bus1.read_pin(9), bus2.read_pin(9));
			printf("Bus 1 Pin 10: %x		Bus 2 Pin 10: %x\n", bus1.read_pin(10), bus2.read_pin(10));
			printf("Bus 1 Pin 11: %x		Bus 2 Pin 11: %x\n", bus1.read_pin(11), bus2.read_pin(11));
			printf("Bus 1 Pin 12: %x		Bus 2 Pin 12: %x\n", bus1.read_pin(12), bus2.read_pin(12));
			printf("Bus 1 Pin 13: %x		Bus 2 Pin 13: %x\n", bus1.read_pin(13), bus2.read_pin(13));
			printf("Bus 1 Pin 14: %x		Bus 2 Pin 14: %x\n", bus1.read_pin(14), bus2.read_pin(14));
			printf("Bus 1 Pin 15: %x		Bus 2 Pin 15: %x\n", bus1.read_pin(15), bus2.read_pin(15));
			printf("Bus 1 Pin 16: %x		Bus 2 Pin 16: %x\n", bus1.read_pin(16), bus2.read_pin(16));
			usleep(200000); // sleep 0.2 seconds
		}
	}
	catch (exception &e)
	{
		cout << e.what();
	}

	(void)argc;
	(void)argv;
	return (0);
}
