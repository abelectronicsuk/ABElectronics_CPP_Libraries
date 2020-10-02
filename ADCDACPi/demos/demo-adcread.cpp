/*
 * demo-adcread.cpp
 *
 *  Version 1.1 Updated 21/04/2020
 *
 *      compile with "g++ demo-adcread.cpp ../ABE_ADCDACPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o demo-adcread"
 *      run with "./demo-adcread"
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

	if (adcdac.open_adc() != 1){ // open the ADC spi channel
			return (1); // if the SPI bus fails to open exit the program
	}

	while (1){
		clearscreen();
		printf("Pin 1: %G \n", adcdac.read_adc_voltage(1, 0)); // read the voltage from channel 1 in single ended mode
		printf("Pin 2: %G \n", adcdac.read_adc_voltage(2, 0)); // read the voltage from channel 2 in single ended mode

		usleep(200000); // sleep 0.2 seconds

	}

	(void)argc;
	(void)argv;
	return (0);
}
