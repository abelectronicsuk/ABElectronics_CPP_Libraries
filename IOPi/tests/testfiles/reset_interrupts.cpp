/*
 * reset_interrupts.cpp
 * 
 * IOPi class > reset_interrupts function test program
 * 
 * this test is not needed as reset_interrupts can be tested with the read_interrupt_capture test
 *   
*/

#include <stdio.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include "../../../UnitTest/testlibs.cpp"
#include "../../ABE_IoPi.h"

using namespace ABElectronics_CPP_Libraries;
using namespace std;

int main(int argc, char **argv)
{
	TestLibs test;
	test.start_test("IOPi class > reset_interrupts()");

	IoPi bus(0x20, false);

	bus.reset_interrupts();

    test.test_outcome();

	(void)argc;
	(void)argv;
	return (0);
}
