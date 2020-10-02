/*
 *  dac-raw.cpp
 *
 *  Version 1.0 Updated 02/10/2020
 *
 *  compile with "g++ dac-raw.cpp ../ABE_ADCDACPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o dac-raw"
 *  run with "./dac-raw"
 * 
 * 	Tests the set_dac_raw() function
 * 
 *  This test outputs a rising voltage on DAC channel 1 and falling voltage on DAC channel 2
 *  When displayed on an oscilloscope both channels should display opposing saw tooth waveforms.
 * 
 *  To test connect an oscilloscope to channels 1 and 2.  
 * 
 *  To test the DAC gain set the gain variable to 1 or 2.
 * 
 *  Voltages when the gain variable is set to 1 should range from 0V to 2.035V.
 *  Voltages when the gain variable is set to 2 should range from 0V to 3.299V.
 *   
 *  Console output:
 * 
 *  Test Running...
 * 
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

int gain = 1;

int main(int argc, char **argv){
	setvbuf (stdout, NULL, _IONBF, 0); // needed to print to the command line

	ADCDACPi adcdac;

	if (adcdac.open_dac() != 1){ // open the DAC spi channel
			return (1); // if the SPI bus fails to open exit the program
	}
    
    adcdac.set_dac_gain(gain);

    printf("Test Running...");

	while (1){
		for (int i = 0; i < 4096; i++){
            adcdac.set_dac_raw(i, 1);
            adcdac.set_dac_raw(4095 - i, 2);
        }
	}

	(void)argc;
	(void)argv;
	return (0);
}
