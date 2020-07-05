/*
 * demo-adcread.cpp
 *
 *  Version 1.1 Updated 21/04/2020
 *
 *      compile with "g++ demo-adcread.cpp ../ABE_ADCDifferentialPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o demo-adcread"
 *      run with "./demo-adcread"
 */

#include <stdio.h>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <iostream>

#include "../ABE_ADCDifferentialPi.h"

using namespace std;
using namespace ABElectronics_CPP_Libraries;

void clearscreen ()
{
    printf("\033[2J\033[1;1H");
}

int main(int argc, char **argv){
	setvbuf (stdout, NULL, _IONBF, 0); // needed to print to the command line

	ADCDifferentialPi adc(0x68, 0x69, 18);

	adc.set_conversion_mode(0);

	while (1){
		clearscreen();
		printf("Pin 1: %G \n", adc.read_voltage(1)); // read from channel 1
		printf("Pin 2: %G \n", adc.read_voltage(2)); // read from channel 2
		printf("Pin 3: %G \n", adc.read_voltage(3)); // read from channel 3
		printf("Pin 4: %G \n", adc.read_voltage(4)); // read from channel 4
		printf("Pin 5: %G \n", adc.read_voltage(5)); // read from channel 5
		printf("Pin 6: %G \n", adc.read_voltage(6)); // read from channel 6
		printf("Pin 7: %G \n", adc.read_voltage(7)); // read from channel 7
		printf("Pin 8: %G \n", adc.read_voltage(8)); // read from channel 8
		usleep(200000); // sleep 0.2 seconds

	}

	(void)argc;
	(void)argv;
	return (0);
}
