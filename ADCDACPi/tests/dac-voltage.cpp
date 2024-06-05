/*
 *  dac-voltage.cpp
 *
 *  Version 1.1 Updated 28/05/2024
 *
 *  compile with "g++ dac-voltage.cpp ../ABE_ADCDACPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o dac-voltage"
 *  run with "./dac-voltage"
 * 
 *  Tests the set_dac_voltage() function.
 * 
 *  This test outputs a rising voltage on DAC channel 1 and a falling voltage on DAC channel 2.
 *  When displayed on an oscilloscope both channels should display opposing saw tooth waveforms.
 * 
 *  To test connect an oscilloscope to channels 1 and 2.  
 * 
 *  To test the DAC gain set the gain variable to 1 or 2.
 * 
 *  Voltages when the gain variable is set to 1, should range from 0V to 2.035V.
 *  Voltages when the gain variable is set to 2, should range from 0V to 3.299V.
 *   
 *  Console output:
 * 
 *  Test Running...
 * 
 */

#include <cstdio>
#include <stdexcept>

#include "../ABE_ADCDACPi.h"

using namespace ABElectronics_CPP_Libraries;

void clear_screen ()
{
    printf("\033[2J\033[1;1H");
}

int gain = 1;

int main(){
	setvbuf (stdout, nullptr, _IONBF, 0); // needed to print to the command line

	ADCDACPi adc_dac;

	if (adc_dac.open_dac() != 1){ // open the DAC SPI channel
			return (1); // if the SPI bus fails to open exit the program
	}
    
    adc_dac.set_dac_gain(gain);

    double range = 2.047;

    if (gain == 2) range = 3.299;

    printf("Test Running...");

	while (1){
		for (double i = 0; i < range; i+= 0.01){
            adc_dac.set_dac_voltage(i, 1);
            adc_dac.set_dac_voltage(2.047 - i, 2);
        }
	}
}
