/*
 * demo-pwm.cpp
 *
 *  Version 1.2 Updated 28/05/2024
 *
 *	Set the PWM output on channel 1 using the PWM class and change the pulse width between 0 and 4095
 *
 *	The ServoPi library uses Wiring Pi library.  This is because the Servo Pi uses the GPIO port to control the Output Enable function.  
 *	
 *	If Wiring Pi is not installed you can install it using the command "sudo apt-get install wiringpi"
 *
 *  compile with "g++ demo-pwm.cpp ../ABE_ServoPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o demo-pwm -L/usr/local/lib -lwiringPi"
 *  run with "./demo-pwm"
 */

#include <cstdio>
#include <cstdint>

#include "../ABE_ServoPi.h"

using namespace ABElectronics_CPP_Libraries;

void clear_screen() {
	printf("\033[2J\033[1;1H");
}

int main() {
	setvbuf(stdout, nullptr, _IONBF, 0); // needed to print to the command line

	// initialize the servo pi on I2C address 0x40 with the Output Enable pin enabled.
	PWM pwm(0x40, true);

	//Set PWM frequency to 1 Khz and enable the output
	pwm.set_pwm_freq(1000);
	pwm.output_enable();

	int x;

	while (true) {
		for (x = 1; x <= 4095; x = x + 5) {
			pwm.set_pwm(1, 0, x); // set the PWM width to x
		}

		for (x = 4095; x >= 0; x = x - 5) {
			pwm.set_pwm(1, 0, x); // set the PWM width to x
		}
	}
}
