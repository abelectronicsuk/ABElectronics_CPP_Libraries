/*
 * pwm-disable_allcall_address.cpp
 *
 *	PWM class > disable_allcall_address function test program 
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
	start_test("PWM class > disable_allcall_address()");

	PWM pwm(0x40, true); // create PWM object

	i2c_emulator_write_byte_data(PCA9685::Mode1, 0x01); // change MODE1 register to be 0x01

	pwm.disable_allcall_address(); // MODE1 should be reset to default value

	test_i2c_register(PCA9685::Mode1, 0x00); // MODE1 expected to be 0x00	
	
	test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
