/*
 * demo-adcread.cpp
 *
 *  Version 1.2 Updated 28/05/2024
 *
 *      compile with "g++ demo-adcread.cpp ../ABE_ADCDACPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o demo-adcread"
 *      run with "./demo-adcread"
 */

#include <cstdio>
#include <stdexcept>
#include <unistd.h>

#include "../ABE_ADCDACPi.h"

using namespace ABElectronics_CPP_Libraries;

void clear_screen ()
{
    printf("\033[2J\033[1;1H");
}

int main(){
	setvbuf (stdout, NULL, _IONBF, 0); // needed to print to the command line

	ADCDACPi adc_dac;

	if (adc_dac.open_adc() != 1){ // open the ADC SPI channel
			return (1); // if the SPI bus fails to open exit the program
	}

	while (1){
        clear_screen();
		printf("Pin 1: %G \n", adc_dac.read_adc_voltage(1, 0)); // read the voltage from channel 1 in single-ended mode
		printf("Pin 2: %G \n", adc_dac.read_adc_voltage(2, 0)); // read the voltage from channel 2 in single-ended mode

		usleep(200000); // sleep 0.2 seconds

	}
}
