/*
 * reset.cpp
 * 
 * I2CSwitch class > reset function test program
 *   
*/

#include <stdio.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_I2CSwitch.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
    TestLibs test;
	test.start_test("I2CSwitch class > reset()");
	
    I2CSwitch i2cswitch(0x70);  // new I2CSwitch object

    test.digitalWrite(2, 0);

    i2cswitch.reset();

    test.test_gpio_state(2, true);

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
