/*
 * demo-servomove.cpp
 *
 *	Control a servo on channel 1 using the Servo class and change the position between three positions.
 *
 *	The Servo Pi library uses Wiring Pi library.  This is because the Servo Pi uses the GPIO port to control the Output Enable function.  
 *	
 *	If Wiring Pi is not installed you can install it using the command "sudo apt-get install wiringpi"
 *
 *  compile with "g++ demo-servomove.cpp ../ABE_ServoPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o demo-servomove -L/usr/local/lib -lwiringPi"
 *  run with "./demo-servomove"
 */

#include <stdint.h>
#include <stdio.h>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <iostream>

#include "../ABE_ServoPi.h"

using namespace ABElectronics_CPP_Libraries;

void clearscreen()
{
	printf("\033[2J\033[1;1H");
}

int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0); // needed to print to the command line

	// initialise a servo object with an I2C address of 0x40 and the Output Enable pin enabled.
	Servo servo(0x40, 1.0, 2.0, true);

	//Set the PWM frequency to 60 Hz and enable the output
	servo.set_frequency(60);
	servo.output_enable();

	while (1)
	{
		servo.move(1, 0, 250); // move the servo to position 0 of 250 steps
		usleep(500000);	// sleep 0.5 seconds
		servo.move(1, 125, 250); // move the servo to position 125 of 250 steps
		usleep(500000);	// sleep 0.5 seconds
		servo.move(1, 250, 250); // move the servo to position 250 of 250 steps
		usleep(500000); // sleep 0.5 seconds
	}

	(void)argc;
	(void)argv;
	return (0);
}
