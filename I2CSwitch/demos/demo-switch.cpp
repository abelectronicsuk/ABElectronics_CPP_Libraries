/*
 * demo-switch.cpp
 *
 *  Version 1.1 Updated 21/04/2020
 *
 *	Set the I2C output to the specified channel.
 *
 *  compile with "g++ demo-switch.cpp ../ABE_I2CSwitch.cpp -Wall -Wextra -Wpedantic -Woverflow -o demo-switch -L/usr/local/lib -lwiringPi"
 *  run with "sudo ./demo-switch"
 */

#include <stdint.h>
#include <stdio.h>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <iostream>

#include "../ABE_I2CSwitch.h"

using namespace ABElectronics_CPP_Libraries;

void clearscreen() {
	printf("\033[2J\033[1;1H");
}



int main(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0); // needed to print to the command line

	// initialise the I2C switch on I2C address 0x70.
	I2CSwitch i2cswitch(0x70);

	// channel to select
	unsigned char channel = 1; 

	// reset the i2c switch
	i2cswitch.reset();

	// switch to the selected channel
	i2cswitch.switch_channel(channel); 

	// check the state of the selected channel
	if (i2cswitch.get_channel_state(channel) == 1){ 
    	printf("I2C switch set to channel %d \n", channel);
	}
	else{
		printf("Failed to change I2C switch to channel %d \n", channel);
	}

	(void)argc;
	(void)argv;
	return (0);
}
