/*
 * demo-iowrite.cpp
 *
 *  Version 1.2 Updated 28/05/2024
 *
 *      compile with "g++ demo-iowrite.cpp ../ABE_ExpanderPi.cpp -Wall -Wextra -Wpedantic -Woverflow  -o demo-iowrite"
 *      run with "./demo-iowrite"
 */
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include "../ABE_ExpanderPi.h"

using namespace std;

int main(int argc, char **argv){
	using namespace ABElectronics_CPP_Libraries;

	try
	{
		ExpanderPi expi;

		expi.io_set_port_direction(0, 0x00); // set the direction for bank 0 to be outputs
		expi.io_set_port_direction(1, 0x00); // set the direction for bank 1 to be outputs
		expi.io_write_port(1, 0xFF);
		while (true){
			expi.io_write_pin(1, 1); // turn pin 1 on and off at 1 second intervals
			usleep(1000000);
			expi.io_write_pin(1, 0);
			usleep(1000000);
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
