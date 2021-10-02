/*
Function overrides for unit testing
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <errno.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>
#include "testlibs.h"

using namespace std;

// Test Variables

int failcount = 0;

// I2C functions

uint8_t registers[256] {0};
uint8_t gpio_state[256] {0};
uint8_t gpio_direction[256] {0};

void TestLibs::i2c_emulator_write_byte_data(uint8_t reg, uint8_t value){ 
    registers[reg] = value;
}

void TestLibs::i2c_emulator_write_word_data(uint8_t reg, uint16_t value){ 
    registers[reg] = (uint8_t)(value&(0xff)); // lower 8 bits
	registers[reg + 1] = (uint8_t)(value>>8) & 0xff; // upper 8 bits
}

uint8_t TestLibs::i2c_emulator_read_byte_data(uint8_t reg){
    return registers[reg];
}

uint16_t TestLibs::i2c_emulator_read_word_data(uint8_t reg){
    uint16_t value = (registers[reg + 1] << 8) + registers[reg];
    return value;
}

// Wiring Pi Functions

void TestLibs::digitalWrite(uint8_t pin, uint8_t value){
    gpio_state[pin] = value;
}

void TestLibs::pinMode(uint8_t pin, uint8_t mode){
    gpio_direction[pin] = mode;
}

int TestLibs::wiringPiSetup(){
    return 1;
}


// Test Functions

void TestLibs::start_test(std::string functionname){
    failcount = 0;
    cout << YELLOWSTART << "TESTING: " << YELLOWEND << functionname << endl;
}

void TestLibs::test_outcome(){
    if (failcount == 0){ cout << GREENSTART << "TEST PASSED" << GREENEND << endl;}
    else{ cout << REDSTART << "TEST FAILED" << REDEND << endl;}

	cout << "============================================================" << endl;
}

void TestLibs::test_fail(std::string message){
    cout << message << endl;
    failcount += 1;
}

void TestLibs::test_i2c_register(uint8_t reg, uint8_t value){
    // tests if an i2c register has the correct value
    if (registers[reg] != value){
		cout << REDSTART << static_cast<unsigned>(reg) << " Register Set: FAILED" << REDEND << endl;
		failcount += 1;
	}
}

void TestLibs::test_gpio_state(uint8_t gpio, uint8_t value){
    // tests if the wiring pi digitalWrite set the correct pin and state
    if (gpio_state[gpio] != value){
        if (value == State::Off){ cout << REDSTART << "GPIO " << static_cast<unsigned>(gpio) << " Unexpected State OFF: FAILED" << REDEND << endl; }
        else if (value == State::On){ cout << REDSTART << "GPIO " << static_cast<unsigned>(gpio) << " Unexpected State ON: FAILED" << REDEND << endl; }
        else { cout << REDSTART << "GPIO " << static_cast<unsigned>(gpio) << " Unexpected State UNKNOWN: FAILED" << REDEND << endl; }
		failcount += 1;
	}
}

void TestLibs::test_gpio_direction(uint8_t gpio, uint8_t value){
    // tests if the wiring pi pinMode function set the correct pin and direction
    if (gpio_direction[gpio] != value){
		if (value == Direction::Output){ cout << REDSTART << "GPIO " << static_cast<unsigned>(gpio) << " Unexpected Direction OUTPUT: FAILED" << REDEND << endl; }
        else if (value == Direction::Input){ cout << REDSTART << "GPIO " << static_cast<unsigned>(gpio) << " Unexpected Direction INPUT: FAILED" << REDEND << endl; }
        else { cout << REDSTART << "GPIO " << static_cast<unsigned>(gpio) << " Unexpected Direction UNKNOWN: FAILED" << REDEND << endl; }
		failcount += 1;
	}
}

void TestLibs::test_exception_failed(std::string message){
    // This function is called inside a try catch if an exception failed to be called.
    cout << "Execption Handling on " << message << " : FAILED" << endl; 
    failcount += 1;
}

uint8_t TestLibs::test_set_bit(uint8_t a, uint8_t bit, bool value)
{
	// update the value of a bit within an 8-bit variable
	if (value == true) return (a |= 1 << bit);
	else return (a &= ~(1 << bit));
}

uint16_t TestLibs::test_set_bit(uint16_t a, uint8_t bit, bool value)
{
	// update the value of a bit within a 16-bit variable
	if (value == true) return (a |= 1 << bit);
	else return (a &= ~(1 << bit));
}

bool TestLibs::test_get_bit(uint8_t byte, uint8_t bit)
{
	// checking the status of a bit within an 8-bit variable
	if (byte & (1 << bit)) return (true);
	else return (false);
}

bool TestLibs::test_get_bit(uint16_t byte, uint8_t bit)
{
	// checking the status of a bit within an 16-bit variable
	if (byte & (1 << bit)) return (true);
	else return (false);
}