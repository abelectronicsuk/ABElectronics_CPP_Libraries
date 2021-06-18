/*
 * pwm-sleep.cpp
 *
 *	PWM class > sleep function test program 
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include "../testlibs.h"
#include "../../ABE_ServoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

void clearscreen() {
	printf("\033[2J\033[1;1H");
}

int main(int argc, char **argv) {
	start_test("PWM class > sleep()");

	PWM pwm(0x40, true); // create PWM object

	pwm.sleep();

	test_i2c_register(PCA9685::Mode1, 0x10); // MODE1 expected to be 0x10
	
	test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}