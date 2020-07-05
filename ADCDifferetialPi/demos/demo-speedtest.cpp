/*
 * demo-speedtest.cpp
 *
 *  Version 1.1 Updated 21/04/2020
 *
 *      compile with "g++ demo-speedtest.cpp ../ABE_ADCDifferentialPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o demo-speedtest"
 *      run with "./demo-speedtest"
 */

#define _DEFAULT_SOURCE
#define numberofsamples 100

#include <stdio.h>
#include <stdexcept>
#include <sys/time.h>
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

	// create an ADCPi object
	ADCDifferentialPi adc(0x68, 0x69, 12);

	// set the conversion mode to continuous 
	adc.set_conversion_mode(1);


	struct timeval t1, t2;
	double elapsedTime;

	double samplearray[numberofsamples];

	// start timer
	gettimeofday(&t1, NULL);

	int x;

	for (x = 0; x < numberofsamples; x++){
		samplearray[x] = adc.read_voltage(1); // read from adc channel 1

	}

	// stop timer
	    gettimeofday(&t2, NULL);

	    // calculate the average value
	    double average = 0;
		double sum = 0;
	    for (x = 0; x < numberofsamples; x++){
	    	sum += samplearray[x];
	    }

	    average = sum/numberofsamples;

	    // compute and print the elapsed time in millisec
	    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
	    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms

	    // compute the sample rate
	    double samplerate = (numberofsamples / elapsedTime) * 1000;

	    printf("%d samples in %G ms.\nThe sample rate was %G samples per second\nThe average voltage was %Gv",numberofsamples,elapsedTime,samplerate,average);

	(void)argc;
	(void)argv;
	return (0);
}

