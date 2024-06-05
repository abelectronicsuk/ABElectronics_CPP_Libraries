/*
 * adc-differential-mode.cpp
 *
 *  Version 1.1 Updated 28/05/2024
 *
 *  compile with "g++ adc-differential-mode.cpp ../ABE_ADCDACPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o adc-differential-mode"
 *  run with "./adc-differential-mode"
 * 
 *  This test displays the differential voltage between ADC inputs 1 and 2 in volts and raw hex format.
 *  Voltage values should range from 0.0V to 3.299V
 *  Hex values should range from 0x000 to 0xfff
 * 
 *  To test apply a voltage between ADC channels 1 and 2 from 0V to 3.3V.  
 *  Channel 1 should be the positive input.
 *  Channel 2 should be the negative input
 *  
 *  Console output when 1.5V is applied between channels 1 and 2 should be:
 * 
 *  Voltage: 1.50095
 *  Raw: 0x747
 * 
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
        clear_screen();
		printf("Voltage: %G \n", adc_dac.read_adc_voltage(1, 1)); // read the voltage between channel 1 and 2 in differential mode
        printf("Raw: 0x%x \n", adc_dac.read_adc_raw(1, 1)); // read the raw value between channel 1 and 2 in differential mode
		usleep(200000); // sleep 0.2 seconds
	}
}
