/*
 * demo-io-interrupts.cpp
 *
 *  Version 1.2 Updated 01/07/2020
 * 
 *  This example shows how to use the interrupt methods on the IO port.
 *  The interrupts will be enabled and set so that a voltage applied
 *  to pins 1 t 8 will trigger INT A and pins 9 to 16 will trigger INT B.
 *  Using the read_interrupt_capture or read_port methods will
 *  reset the interrupts.
 *
 *      compile with "g++ demo-io-interrupts.cpp ../ABE_IoPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o demo-io-interrupts"
 *      run with "./demo-io-interrupts"
 */

#include <stdio.h>
#include <stdexcept>
#include <time.h>
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

	try
	{
		IoPi bus1(0x20);
		IoPi bus2(0x21);

		// initialise one of the io pi buses on i2c address  default address for bus 1

		bus1.set_port_direction(0, 0xFF); // set bank 0 to be inputs
		bus1.set_port_direction(1, 0xFF); // set bank 1 to be inputs
		bus1.set_port_pullups(0, 0xFF);   // disable internal pullups for port 0
		bus1.set_port_pullups(1, 0xFF);   // disable internal pullups for port 1

		bus1.invert_port(0, 0xFF);
		bus1.invert_port(1, 0xFF);
      
        // Set the interrupt polarity to be active high and mirroring disabled, so
        // pins 1 to 8 trigger INT A and pins 9 to 16 trigger INT B
        bus1.set_interrupt_polarity(1);
        bus1.mirror_interrupts(1);
    
        // Set the interrupts default value to trigger when 5V is applied to any pin
        bus1.set_interrupt_defaults(0, 0xFF);
        bus1.set_interrupt_defaults(1, 0xFF);
    
        // Set the interrupt type to be 1 for ports A and B so an interrupt is
        // fired when the pin matches the default value
        bus1.set_interrupt_type(0, 0xFF);
        bus1.set_interrupt_type(1, 0xFF);
    
        // Enable interrupts for pins 1 to 16
        bus1.set_interrupt_on_port(0, 0xFF);
        bus1.set_interrupt_on_port(1, 0xFF);

		while (1)
		{
			clearscreen();
			printf("%d\n", bus1.read_interrupt_capture(0));
			printf("%d\n", bus1.read_interrupt_capture(1));
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
