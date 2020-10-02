/*
 * demo-dacwrite.cpp
 *
 *  Version 1.1 Updated 21/04/2020
 *
 *      compile with "g++ demo-dacwrite.cpp ../ABE_ADCDACPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o demo-dacwrite"
 *      run with "./demo-dacwrite"
 */

#include <stdint.h>
#include <stdio.h>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <iostream>

#include "../ABE_ADCDACPi.h"

using namespace ABElectronics_CPP_Libraries;

void clearscreen ()
{
    printf("\033[2J\033[1;1H");
}

int main(int argc, char **argv){
	setvbuf (stdout, NULL, _IONBF, 0); // needed to print to the command line

	ADCDACPi adcdac;

	if (adcdac.open_dac() != 1){ // open the DAC spi channel
		return(1); // if the SPI bus fails to open exit the program
	}

	adcdac.set_dac_gain(2); // set the dac gain to 2 which will give a voltage range of 0 to 3.3V

	adcdac.set_dac_voltage(1.2, 1); // set the voltage on channel 1 to 1.2V
	adcdac.set_dac_voltage(3.1, 2); // set the voltage on channel 2 to 3.1V

	adcdac.close_dac();

	printf("dac values written\n");

	(void)argc;
	(void)argv;
	return (0);
}
