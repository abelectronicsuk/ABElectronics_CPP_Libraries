/*
 * demo-servomove.cpp
 *
 *  Created on: 26 June 2017
 *
 *	Control a servo on channel 1 and change the position between three positions.
 *
 *	The demo needs to be run as sudo.  This is because the Servo Pi uses the GPIO port to control
 *	the Output Enable function and GPIO needs to be accessed as root.
 *
 *	To run without sudo privileges change "servopi_init(0x40, 1);" to "servopi_init(0x40, 0);"
 *	to disable the output enable pin and remove "output_enable(0x40);"
 *
 *  compile with "g++ demo-servomove.cpp ABE_ServoPi.cpp -o demo-servomove"
 *  run with "sudo ./demo-servomove"
 */

#include <stdint.h>
#include <stdio.h>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <iostream>

#include "ABE_ServoPi.h"

using namespace ABElectronics_CPP_Libraries;

// define the the servo minimum, centre and maximum limits
#define servoMin 250 // Minimum pulse length out of 4096
#define servoMed 400 // Medium pulse length out of 4096
#define servoMax 500 // Maximum pulse length out of 4096

void clearscreen()
{
	printf("\033[2J\033[1;1H");
}

int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0); // needed to print to the command line

	// initialise the servo pi on I2C address 0x40 with the Output Enable pin enabled.
	ServoPi servo(0x40, 1);

	//Set PWM frequency to 60 Hz and enable the output
	servo.set_pwm_freq(60, 0x40);
	servo.output_enable();

	while (1)
	{
		servo.set_pwm(1, 0, servoMin, 0x40); // set the pwm width to servoMin
		usleep(500000);						 // sleep 0.5 seconds
		servo.set_pwm(1, 0, servoMed, 0x40); // set the pwm width to servoMed
		usleep(500000);						 // sleep 0.5 seconds
		servo.set_pwm(1, 0, servoMax, 0x40); // set the pwm width to servoMax
		usleep(500000);						 // sleep 0.5 seconds
	}

	return (0);
}
