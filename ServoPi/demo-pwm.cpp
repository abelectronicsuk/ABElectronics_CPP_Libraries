/*
 * demo-pwm.cpp
 *
 *  Version 1.1 Updated 21/04/2020
 *
 *	Set the PWM output on channel 1 and change the pulse width between 0 and 4095
 *
 *	The ServoPi library uses Wiring Pi to access the GPIO port.  This is because the Servo Pi uses the GPIO port to control
 *	the Output Enable function.  
 *	
 *	If Wiring Pi is not installed you can install it using the command "sudo apt-get install wiringpi"
 *
 *  compile with "g++ demo-pwm.cpp ABE_ServoPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o demo-pwm -L/usr/local/lib -lwiringPi"
 *  run with "./demo-pwm"
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

	

	int x;

	// initialise the servo pi on I2C address 0x40 with the Output Enable pin enabled.
	ServoPi servo(0x40, 1);

	//Set PWM frequency to 1 Khz and enable the output
	servo.set_pwm_freq(1000, 0x40);
	servo.output_enable();



	while (1) {
		for (x = 1; x <= 4095; x = x + 5) {
			servo.set_pwm(1, 0, x, 0x40); // set the pwm width to x
		}

		for (x = 4095; x >= 0; x = x - 5) {
			servo.set_pwm(1, 0, x, 0x40); // set the pwm width to x
		}

	}

	(void)argc;
	(void)argv;
	return (0);
}
