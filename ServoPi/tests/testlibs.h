/*
Function overrides for unit testing
*/

#ifndef TESTLIBS_H_
#define TESTLIBS_H_

#define REDSTART "\033[1;31m"
#define REDEND "\033[0m"

#define GREENSTART "\033[1;32m"
#define GREENEND "\033[0m"

#define YELLOWSTART "\033[1;33m"
#define YELLOWEND "\033[0m"

#define WHITESTART "\033[1;37m"
#define WHITEEND "\033[0m"

// PCA9685 Register Addresses
enum PCA9685{
    Mode1=0x00,
    Mode2=0x01,
    SubAddress1=0x02,
    SubAddress2=0x03,
    SubAddress3=0x04,
    AllCallAddress=0x05,
    LED0_ON_Low=0x06,
    LED0_ON_High=0x07,
    LED0_OFF_Low=0x08,
    LED0_OFF_High=0x09,
    All_LED_ON_Low=0xFA,
    All_LED_ON_High=0xFB,
    All_LED_OFF_Low=0xFC,
    All_LED_OFF_High=0xFD,
    Prescaler=0xFE
};

// Test Variables

enum Direction{
    Input=0,
    Output=1
};

enum State{
    On=1,
    Off=0
};

// I2C functions

extern uint8_t registers[256];

void i2c_emulator_write_byte_data(uint8_t reg, uint8_t value);
uint8_t i2c_emulator_read_byte_data(uint8_t reg);


// Wiring Pi functions
#define OUTPUT 1
#define INPUT 0

void digitalWrite(uint8_t pin, uint8_t value);
void pinMode(uint8_t pin, uint8_t mode);
int wiringPiSetup();

// Test Functions
void start_test(std::string functionname);
void test_outcome();
void test_fail(std::string message);
void test_i2c_register(uint8_t reg, uint8_t value);
void test_gpio_state(uint8_t gpio, uint8_t value);
void test_gpio_direction(uint8_t gpio, uint8_t value);
void test_exception_failed(std::string message);

#endif /* TESTLIBS_H_ */