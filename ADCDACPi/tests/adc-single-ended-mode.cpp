/*
 * adc-single-ended-mode.cpp
 *
 *  Version 1.0 Updated 02/10/2020
 *
 *  compile with "g++ adc-single-ended-mode.cpp ../ABE_ADCDACPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o adc-single-ended-mode"
 *  run with "./adc-single-ended-mode"
 * 
 *  This test displays the voltage on each ADC input in volts and raw hex format.
 *  Voltage values should range from 0.0V to 3.299V
 *  Hex values should range from 0x000 to 0xfff
 * 
 *  To test apply a voltage on each ADC channel from 0V to 3.3V
 *  
 *  Console output when 1.5V is applied to channel 1 should be:
 * 
 *  Voltage Pin 1: 1.50095
 *  Voltage Pin 2: 0.00322266
 *  Raw Pin 1: 0x747
 *  Raw Pin 2: 0x7
 * 
 *  Note: if one if the channels is left floating it will show a low voltage just above 0V 
 *        from background noise being picked up by the ADC pin.
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
		
		printf("Voltage Pin 1: %G \n", adcdac.read_adc_voltage(1, 0)); // read the voltage from channel 1 in single ended mode
		printf("Voltage Pin 2: %G \n", adcdac.read_adc_voltage(2, 0)); // read the voltage from channel 2 in single ended mode
        printf("Raw Pin 1: 0x%x \n", adcdac.read_adc_raw(1, 0)); // read the raw value from channel 1 in single ended mode
		printf("Raw Pin 2: 0x%x \n", adcdac.read_adc_raw(2, 0)); // read the raw value from channel 2 in single ended mode
		usleep(200000); // sleep 0.2 seconds

	}

	(void)argc;
	(void)argv;
	return (0);
}
