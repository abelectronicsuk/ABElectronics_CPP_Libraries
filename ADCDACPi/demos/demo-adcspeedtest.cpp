/*
 * demo-adcread.cpp
 *
 *  Version 1.2 Updated 28/05/2024
 *
 *      compile with "g++ demo-adcspeedtest.cpp ../ABE_ADCDACPi.cpp -Wall -Wextra -Wpedantic -Woverflow  -o demo-adcspeedtest"
 *      run with "./demo-adcspeedtest"
 */

#define number_of_samples 100000

#include <cstdio>
#include <stdexcept>
#include <sys/time.h>

#include "../ABE_ADCDACPi.h"

using namespace std;
using namespace ABElectronics_CPP_Libraries;

void clear_screen()
{
	printf("\033[2J\033[1;1H");
}

int main(int argc, char **argv)
{
	setvbuf(stdout, nullptr, _IONBF, 0); // needed to print to the command line

	ADCDACPi adc_dac;

	if (adc_dac.open_adc() != 1)
	{				// open the ADC SPI channel
		return (1); // if the SPI bus fails to open exit the program
	}

	struct timeval t1{};
    struct timeval t2{};
	double elapsed_time;

	double sample_array[number_of_samples];

	// start timer
	gettimeofday(&t1, nullptr);

	int x;
	for (x = 0; x < number_of_samples; x++)
	{
		sample_array[x] = adc_dac.read_adc_voltage(1, 0); // read from adc channel 1
	}

	// stop timer
	gettimeofday(&t2, nullptr);

	// calculate the average value
	double average;
	double sum = 0;
	for (x = 0; x < number_of_samples; x++)
	{
		sum += sample_array[x];
	}

	average = sum / number_of_samples;

	// compute and print the elapsed time in milliseconds
    elapsed_time = ((double)t2.tv_sec - (double)t1.tv_sec) * 1000.0;	// sec to ms
    elapsed_time += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms

	// compute the sample rate
	double sample_rate = (number_of_samples / elapsed_time) * 1000;

	printf("%d samples in %G ms.\nThe sample rate was %G samples per second\nThe average voltage was %Gv", number_of_samples, elapsed_time, sample_rate, average);

	(void)argc;
	(void)argv;
	return (0);
}
