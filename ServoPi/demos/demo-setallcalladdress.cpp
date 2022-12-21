/*
 * demo-setallcalladdress.cpp
 *
 *  Set the All Call I2C address to 0x60 and enable All Call functionality.  This allows you to
 *  access several Servo Pi boards at the same time from a single I2C address.
 *
 *	The ServoPi library uses Wiring Pi library.  This is because the Servo Pi uses the GPIO port to control	the Output Enable function.  
 *	
 *	If Wiring Pi is not installed you can install it using the command "sudo apt-get install wiringpi"
 *
 *      compile with "g++ demo-setallcalladdress.cpp ../ABE_ServoPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o demo-setallcalladdress -L/usr/local/lib -lwiringPi"
 *      run with "./demo-setallcalladdress"
 */

#include <stdint.h>
#include <stdio.h>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <iostream>

#include "../ABE_ServoPi.h"

using namespace ABElectronics_CPP_Libraries;

void clearscreen() {
	printf("\033[2J\033[1;1H");
}



int main(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0); // needed to print to the command line

	// initialise the servo pi on I2C address 0x40.  Check the returned value to ensure the Servo Pi has been initialised correctly

	PWM pwm(0x40, 1);

	pwm.set_allcall_address(0x70);
	pwm.enable_allcall_address();

	(void)argc;
	(void)argv;
	return (0);
}
