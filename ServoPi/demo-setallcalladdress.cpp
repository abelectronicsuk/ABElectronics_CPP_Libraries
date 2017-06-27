/*
 * demo-setallcalladdress.cpp
 *
 *  Created on: 26 June 2017
 *
 *  Set the All Call I2C address to be 0x60 and enable All Call functionality.  This allows you to
 *  access several Servo Pi boards at the same time from a single I2C address.
 *
 *	The demo needs to be run as sudo.  This is because the Servo Pi uses the GPIO port to control
 *	the Output Enable function and GPIO needs to be accessed as root.
 *
 *	To run without sudo privileges change "servopi_init(0x40, 1);" to "servopi_init(0x40, 0);"
 *	to disable the output enable pin and remove "output_enable(0x40);"
 *
 *      compile with "g++ demo-setallcalladdress.cpp ABE_ServoPi.cpp -o demo-setallcalladdress"
 *      run with "sudo ./demo-setallcalladdress"
 */

#include <stdint.h>
#include <stdio.h>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <iostream>

#include "ABE_ServoPi.h"

using namespace ABElectronics_CPP_Libraries;

void clearscreen() {
	printf("\033[2J\033[1;1H");
}



int main(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0); // needed to print to the command line


	// initialise the servo pi on I2C address 0x40.  Check the returned value to ensure the Servo Pi initialised correctly

	ServoPi servo(0x40, 1);

	servo.set_allcall_address(0x60, 0x40);
	servo.enable_allcall_address(0x40);

	return (0);
}
