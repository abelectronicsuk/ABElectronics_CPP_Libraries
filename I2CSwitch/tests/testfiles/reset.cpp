/*
 * reset.cpp
 * 
 * I2CSwitch class > reset function test program
 *   
*/

#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_I2CSwitch.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs::start_test("I2CSwitch class > reset()");
	
    I2CSwitch i2c_switch(0x70);  // new I2CSwitch object

    TestLibs::digitalWrite(2, 0);

    i2c_switch.reset();

    TestLibs::test_gpio_state(2, true);

    TestLibs::test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
