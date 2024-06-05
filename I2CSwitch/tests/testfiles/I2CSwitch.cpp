/*
 * I2CSwitch.cpp
 * 
 * I2CSwitch class > I2CSwitch function test program
 *   
*/

#include <stdexcept>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_I2CSwitch.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("I2CSwitch class > I2CSwitch()");
	
    // out of bounds test
	try{
		I2CSwitch i2cswitch1(0x6F);
		TestLibs::test_exception_failed("low out of bounds");
	}
	catch(const std::exception& e){	}

    try{
		I2CSwitch i2cswitch2(0x78);
		TestLibs::test_exception_failed("high out of bounds");
	}
	catch(const std::exception& e){	}

    I2CSwitch i2cswitch3(0x70);  // new I2CSwitch object

    TestLibs::test_gpio_state(2, true);

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
