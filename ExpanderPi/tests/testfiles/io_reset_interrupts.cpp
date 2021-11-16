/*
 * io_reset_interrupts.cpp
 * 
 * ExpanderPi class > io_reset_interrupts function test program
 * 
 * this test is not needed as reset_interrupts can be tested with the read_interrupt_capture test
 *   
*/

#include <stdio.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_ExpanderPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs test;
	test.start_test("ExpanderPi class > io_reset_interrupts()");

	ExpanderPi bus(false);

	bus.io_reset_interrupts();

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
