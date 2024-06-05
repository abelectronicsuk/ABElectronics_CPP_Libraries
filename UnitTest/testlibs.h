/* Function overrides for unit testing */

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

class TestLibs
{
public:
    // MCP23017 register addresses - Used in the IO Pi and Expander Pi libraries

    enum MCP23017
    {
        MCP23017_IODIRA = 0x00,   // IO direction A - 1= input 0 = output
        MCP23017_IODIRB = 0x01,   // IO direction B - 1= input 0 = output
        MCP23017_IPOLA = 0x02,    // Input polarity A
        MCP23017_IPOLB = 0x03,    // Input polarity B
        MCP23017_GPINTENA = 0x04, // Controls the interrupt-on-change on port A
        MCP23017_GPINTENB = 0x05, // Controls the interrupt-on-change on port B
        MCP23017_DEFVALA = 0x06,  // Default value for port A
        MCP23017_DEFVALB = 0x07,  // Default value for port B
        MCP23017_INTCONA = 0x08,  // Interrupt control register for port A
        MCP23017_INTCONB = 0x09,  // Interrupt control register for port B
        MCP23017_IOCON = 0x0A,    // see datasheet for configuration register
        MCP23017_GPPUA = 0x0C,    // pull-up resistors for port A
        MCP23017_GPPUB = 0x0D,    // pull-up resistors for port B
        MCP23017_INTFA = 0x0E,    // Interrupt condition on port A for any enabled pin
        MCP23017_INTFB = 0x0F,    // Interrupt condition on port B for any enabled pin
        MCP23017_INTCAPA = 0x10,  // Captures the GPIO port A value at the time the interrupt occurred
        MCP23017_INTCAPB = 0x11,  // Captures the GPIO port B value at the time the interrupt occurred
        MCP23017_GPIOA = 0x12,    // Data port A
        MCP23017_GPIOB = 0x13,    // Data port B
        MCP23017_OLATA = 0x14,    // Output latches for port A
        MCP23017_OLATB = 0x15     // Output latches for port B
    };

    // PCA9535 Register Addresses - used in the IO Zero 32 library
    enum PCA9535
    {
		PCA9535_INPUTPORT0  = 0x00, // Command byte Input port 0
		PCA9535_INPUTPORT1  = 0x01, // Command byte Input port 1
		PCA9535_OUTPUTPORT0 = 0x02, // Command byte Output port 0
		PCA9535_OUTPUTPORT1 = 0x03, // Command byte Output port 1
		PCA9535_INVERTPORT0 = 0x04, // Command byte Polarity Inversion port 0
		PCA9535_INVERTPORT1 = 0x05, // Command byte Polarity Inversion port 1
		PCA9535_CONFIGPORT0 = 0x06, // Command byte Configuration port 0
		PCA9535_CONFIGPORT1 = 0x07, // Command byte Configuration port 1
    };

    // PCA9685 Register Addresses - used in the Servo Pi library
    enum PCA9685
    {
        PCA9685_Mode1 = 0x00,
        PCA9685_Mode2 = 0x01,
        PCA9685_SubAddress1 = 0x02,
        PCA9685_SubAddress2 = 0x03,
        PCA9685_SubAddress3 = 0x04,
        PCA9685_AllCallAddress = 0x05,
        PCA9685_LED0_ON_Low = 0x06,
        PCA9685_LED0_ON_High = 0x07,
        PCA9685_LED0_OFF_Low = 0x08,
        PCA9685_LED0_OFF_High = 0x09,
        PCA9685_All_LED_ON_Low = 0xFA,
        PCA9685_All_LED_ON_High = 0xFB,
        PCA9685_All_LED_OFF_Low = 0xFC,
        PCA9685_All_LED_OFF_High = 0xFD,
        PCA9685_Prescaler = 0xFE
    };

    // DS1307 Register Addresses - used in RTC Pi and Expander Pi
    enum DS1307{
        DS1307_RTCADDRESS = 0x68,
        DS1307_SECONDS = 0x00,
        DS1307_MINUTES = 0x01,
        DS1307_HOURS = 0x02,
        DS1307_DAYOFWEEK = 0x03,
        DS1307_DAY = 0x04,
        DS1307_MONTH = 0x05,
        DS1307_YEAR = 0x06,
        DS1307_CONTROL = 0x07
    };

    // Test Variables

    enum Direction
    {
        Input = 0,
        Output = 1
    };

    enum State
    {
        On = 1,
        Off = 0
    };

    // I2C functions
    static void i2c_emulator_write_byte_data(uint8_t reg, uint8_t value);
    static void i2c_emulator_write_word_data(uint8_t reg, uint16_t value);
    static uint8_t i2c_emulator_read_byte_data(uint8_t reg);
    static uint16_t i2c_emulator_read_word_data(uint8_t reg);

    static void digitalWrite(uint8_t pin, uint8_t value);
    static void pinMode(uint8_t pin, uint8_t mode);
    static int wiringPiSetup();

    // Test Functions
    static void start_test(const std::string& function_name);
    static void test_outcome();
    static void test_fail(const std::string& message);
    static void test_i2c_register(uint8_t reg, uint8_t value);
    static void test_gpio_state(uint8_t gpio, uint8_t value);
    static void test_gpio_direction(uint8_t gpio, uint8_t value);
    static void test_exception_failed(const std::string& message);
    static uint8_t test_set_bit(uint8_t a, uint8_t bit, bool value);
    static uint16_t test_set_bit(uint16_t a, uint8_t bit, bool value);
    static bool test_get_bit(uint8_t byte, uint8_t bit);
    static bool test_get_bit(uint16_t byte, uint8_t bit);
};
#endif /* TESTLIBS_H_ */