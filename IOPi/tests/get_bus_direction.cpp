/*
get_bus_direction.cpp

Version 1.0 Created 01/07/2020

      compile with "g++ get_bus_direction.cpp ../ABE_IoPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o get_bus_direction"
      run with "./get_bus_direction"
 
This test validates the get_bus_direction function in the IOPi class.

Hardware Required: Logic Analyser on I2C Pins

=== Expected Result ============================

> Console Output:

Test Passed

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

	bool passed = true;
	uint16_t x = 0;

    IoPi bus(0x20, false);  // new iopi object without initialisation

    for (uint16_t a = 0; a < 65535; a++){
        bus.set_bus_direction(a);
        x = bus.get_bus_direction();
        if (x != a){
            passed = false;
            break;
		}        
	}

    if (!passed){
        cout << "Test Failed\n";
	}
    else{
        cout << "Test Passed\n";
	}

	(void)argc;
	(void)argv;
	return (0);
}
