/*
 * pwm-get_pwm_off_time.cpp
 *
 *	PWM class > get_pwm_off_time function test program 
 *
 */

#include <cstdint>
#include <cstdio>
#include <stdexcept>
#include <iostream>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ServoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

void clear_screen() {
	printf("\033[2J\033[1;1H");
}


int main(int argc, char **argv) {
	TestLibs::start_test("PWM class > get_pwm_off_time()");

	PWM pwm(0x40, true); // create PWM object

	// out of bounds test for address register
	try{
		pwm.get_pwm_off_time(-1);
		TestLibs::test_exception_failed("channel low out of bounds");
	}
	catch(const std::exception& e){	}

	try{
		pwm.get_pwm_off_time(17);
		TestLibs::test_exception_failed("channel high out of bounds");
	}
	catch(const std::exception& e){	}


	// set the LED0_OFF_Low register to 0x10 and LED0_OFF_High to 0x05
	TestLibs::i2c_emulator_write_byte_data(TestLibs::PCA9685_LED0_OFF_Low, 0x10);
	TestLibs::i2c_emulator_write_byte_data(TestLibs::PCA9685_LED0_OFF_High, 0x05);

	// set the LED12_OFF_Low register to 0x20 and LED12_OFF_High to 0xCC
	TestLibs::i2c_emulator_write_byte_data(TestLibs::PCA9685_LED0_OFF_Low + 48, 0x20);
	TestLibs::i2c_emulator_write_byte_data(TestLibs::PCA9685_LED0_OFF_High + 48, 0xCC);

	uint16_t a = pwm.get_pwm_off_time(1); // get the register values for LED0_OFF

	uint16_t b = pwm.get_pwm_off_time(13); // get the register values for LED12_OFF
	
	if (a != 0x0510){ // output should be 0x0510
		cout << a << endl;
		TestLibs::test_fail("Unexpected register value for LED0_OFF");
	}

	if (b != 0xCC20){ // output should be 0xCC20
		cout << b << endl;
		TestLibs::test_fail("Unexpected register value for LED12_OFF");
	}

	TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}