/*
 * demo-dacwrite.cpp
 *
 *  Version 1.2 Updated 28/05/2024
 *
 *      compile with "g++ demo-dacwrite.cpp ../ABE_ADCDACPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o demo-dacwrite"
 *      run with "./demo-dacwrite"
 */

#include <cstdio>
#include <stdexcept>

#include "../ABE_ADCDACPi.h"

using namespace ABElectronics_CPP_Libraries;

void clear_screen ()
{
    printf("\033[2J\033[1;1H");
}

int main(int argc, char **argv){
	setvbuf (stdout, nullptr, _IONBF, 0); // needed to print to the command line

	ADCDACPi adc_dac;

	if (adc_dac.open_dac() != 1){ // open the DAC SPI channel
		return(1); // if the SPI bus fails to open exit the program
	}

	adc_dac.set_dac_gain(2); // set the DAC gain to 2 which will give a voltage range of 0 to 3.3V

	adc_dac.set_dac_voltage(1.2, 1); // set the voltage on channel 1 to 1.2V
	adc_dac.set_dac_voltage(3.1, 2); // set the voltage on channel 2 to 3.1V

	adc_dac.close_dac();

	printf("DAC values written\n");

	(void)argc;
	(void)argv;
	return (0);
}
