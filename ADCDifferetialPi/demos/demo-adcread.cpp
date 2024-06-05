/*
 * demo-adcread.cpp
 *
 *  Version 1.2 Updated 28/05/2024
 *
 *      compile with "g++ demo-adcread.cpp ../ABE_ADCDifferentialPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o demo-adcread"
 *      run with "./demo-adcread"
 */

#include <cstdio>
#include <stdexcept>
#include <unistd.h>

#include "../ABE_ADCDifferentialPi.h"

using namespace std;
using namespace ABElectronics_CPP_Libraries;

void clear_screen ()
{
    printf("\033[2J\033[1;1H");
}

int main(){
	setvbuf (stdout, nullptr, _IONBF, 0); // needed to print to the command line

	ADCDifferentialPi adc(0x68, 0x69, 14);

	adc.set_conversion_mode(0);

	while (true){
        clear_screen();
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
}
