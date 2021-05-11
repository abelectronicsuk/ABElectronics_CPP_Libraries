/*
 * demo-ioread.cpp
 *
 *  Version 1.1 Updated 21/04/2020
 *
 *      compile with "g++ demo-ioread.cpp ../ABE_ExpanderPi.cpp -Wall -Wextra -Wpedantic -Woverflow  -o demo-ioread"
 *      run with "./demo-ioread"
 */
#include <stdint.h>
#include <stdio.h>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include "../ABE_ExpanderPi.h"

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
		ExpanderPi expi;

		// initialise one of the io pi buses on i2c address  default address for bus 1

		expi.io_set_port_direction(0, 0xFF); // set bank 0 to be inputs
		expi.io_set_port_direction(1, 0xFF); // set bank 1 to be inputs
		expi.io_set_port_pullups(0, 0xFF);   // enable internal pullups for bank 0
		expi.io_invert_port(0, 0xFF);		  // invert output so bank will read as 0
		expi.io_set_port_pullups(1, 0xFF);   // enable internal pullups for bank 0
		expi.io_invert_port(1, 0xFF);		  // invert output so bank will read as 0

		while (1)
		{
			clearscreen();
			printf("Bus 1 Pin 1:  %x\n", expi.io_read_pin(1));
			printf("Bus 1 Pin 2:  %x\n", expi.io_read_pin(2));
			printf("Bus 1 Pin 3:  %x\n", expi.io_read_pin(3));
			printf("Bus 1 Pin 4:  %x\n", expi.io_read_pin(4));
			printf("Bus 1 Pin 5:  %x\n", expi.io_read_pin(5));
			printf("Bus 1 Pin 6:  %x\n", expi.io_read_pin(6));
			printf("Bus 1 Pin 7:  %x\n", expi.io_read_pin(7));
			printf("Bus 1 Pin 8:  %x\n", expi.io_read_pin(8));
			printf("Bus 1 Pin 9:  %x\n", expi.io_read_pin(9));
			printf("Bus 1 Pin 10: %x\n", expi.io_read_pin(10));
			printf("Bus 1 Pin 11: %x\n", expi.io_read_pin(11));
			printf("Bus 1 Pin 12: %x\n", expi.io_read_pin(12));
			printf("Bus 1 Pin 13: %x\n", expi.io_read_pin(13));
			printf("Bus 1 Pin 14: %x\n", expi.io_read_pin(14));
			printf("Bus 1 Pin 15: %x\n", expi.io_read_pin(15));
			printf("Bus 1 Pin 16: %x\n", expi.io_read_pin(16));
			usleep(100000);
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
