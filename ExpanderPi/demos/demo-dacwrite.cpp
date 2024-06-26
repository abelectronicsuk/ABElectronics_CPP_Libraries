/*
 * demo-dacwrite.cpp
 *
 *  Version 1.2 Updated 28/05/2024
 *
 *      compile with "g++ demo-dacwrite.cpp ../ABE_ExpanderPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o demo-dacwrite"
 *      run with "./demo-dacwrite"
 */

#include <cstdio>
#include <stdexcept>
#include <ctime>

#include "../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;

void clear_screen ()
{
    printf("\033[2J\033[1;1H");
}

int main(int argc, char **argv){
	setvbuf (stdout, nullptr, _IONBF, 0); // needed to print to the command line

	ExpanderPi expi;

	if (expi.dac_open() != 1){ // open the DAC SPI channel
		return(1); // if the SPI bus fails to open exit the program
	}

	expi.dac_set_voltage(1.5, 1, 2); // set the voltage on channel 1 to 1.2V and the gain to 2
	expi.dac_set_voltage(3.8, 2, 2); // set the voltage on channel 2 to 2.5V and the gain to 2

	expi.dac_close();

	printf("dac values written\n");

	(void)argc;
	(void)argv;
	return (0);
}
