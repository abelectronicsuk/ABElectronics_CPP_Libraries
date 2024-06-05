/*
 * adc-single-ended-mode.cpp
 *
 *  Version 1.1 Updated 28/05/2024
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
 *  Note: if one of the channels is left floating it will show a low voltage just above 0V 
 *        from background noise being picked up by the ADC pin.
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
	setvbuf (stdout, nullptr, _IONBF, 0); // needed to print to the command line

	ADCDACPi adc_dac;

	if (adc_dac.open_adc() != 1){ // open the ADC SPI channel
			return (1); // if the SPI bus fails to open exit the program
	}

	while (1){
		printf("Voltage Pin 1: %G \n", adc_dac.read_adc_voltage(1, 0)); // read the voltage from channel 1 in single-ended mode
		printf("Voltage Pin 2: %G \n", adc_dac.read_adc_voltage(2, 0)); // read the voltage from channel 2 in single-ended mode
        printf("Raw Pin 1: 0x%x \n", adc_dac.read_adc_raw(1, 0)); // read the raw value from channel 1 in single-ended mode
		printf("Raw Pin 2: 0x%x \n", adc_dac.read_adc_raw(2, 0)); // read the raw value from channel 2 in single-ended mode
		usleep(200000); // sleep 0.2 seconds
	}
}
