/*
 * demo-adcread.cpp
 *
 *  Version 1.2 Updated 28/05/2024
 *
 *      compile with "g++ demo-adcread.cpp ../ABE_ExpanderPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o demo-adcread"
 *      run with "./demo-adcread"
 */

#include <cstdio>
#include <stdexcept>
#include <ctime>
#include <unistd.h>

#include "../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;

void clear_screen ()
{
    printf("\033[2J\033[1;1H");
}

int main(){
	setvbuf (stdout, nullptr, _IONBF, 0); // needed to print to the command line

	ExpanderPi expi(true, false);

	if (expi.adc_open() != 1){ // open the DAC SPI channel
			return (1); // if the SPI bus fails to open exit the program
	}

	while (true){
        clear_screen();
		printf("Pin 1: %G \n", expi.adc_read_voltage(1, 0)); // read the voltage from channel 1 in single-ended mode
		printf("Pin 2: %G \n", expi.adc_read_voltage(2, 0)); // read the voltage from channel 2 in single-ended mode
		printf("Pin 3: %G \n", expi.adc_read_voltage(3, 0)); // read the voltage from channel 1 in single-ended mode
		printf("Pin 4: %G \n", expi.adc_read_voltage(4, 0)); // read the voltage from channel 2 in single-ended mode
		printf("Pin 5: %G \n", expi.adc_read_voltage(5, 0)); // read the voltage from channel 1 in single-ended mode
		printf("Pin 6: %G \n", expi.adc_read_voltage(6, 0)); // read the voltage from channel 2 in single-ended mode
		printf("Pin 7: %G \n", expi.adc_read_voltage(7, 0)); // read the voltage from channel 1 in single-ended mode
		printf("Pin 8: %G \n", expi.adc_read_voltage(8, 0)); // read the voltage from channel 2 in single-ended mode

		usleep(200000); // sleep 0.2 seconds

	}
}
