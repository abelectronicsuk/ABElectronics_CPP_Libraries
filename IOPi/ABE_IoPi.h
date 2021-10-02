/*
 ================================================
 ABElectronics UK IO Pi 32-Channel Port Expander
 Version 1.1.0 Updated 01/07/2020
 ================================================


 Each MCP23017 chip is split into two 8-bit ports.  port 0 controls
 pins 1 to 8 while port 1 controls pins 9 to 16.
 When writing to or reading from a port the least significant bit represents
 the lowest numbered pin on the selected port.


 Required package{
 apt-get install libi2c-dev
 */

namespace ABElectronics_CPP_Libraries
{
    class IoPi
    {

    public:
        // public methods

        /**
	* initialise the MCP32017 IO chip with default values: ports are inputs, pull-up resistors are disabled and ports are not inverted
	* @param address - I2C address for the target device
	* @param initialise - true = direction set as inputs, pull-ups disabled, ports not inverted.
                          false = device state unaltered. Defaults to true
	*/
        IoPi(uint8_t i2caddress, bool initialise = true);

        /**
	* set IO direction for an individual pin
	* @param pins - 1 to 16
	* @param direction - 1 = input, 0 = output
	*/
        void set_pin_direction(uint8_t pin, uint8_t direction);

        /**
	* get IO direction for an individual pin
	* @param pins - 1 to 16
	*/
        uint8_t get_pin_direction(uint8_t pin);

        /**
	* set direction for an IO port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param direction - 0 to 255 (0xFF).  For each bit 1 = input, 0 = output
	*/
        void set_port_direction(uint8_t port, uint8_t direction);

        /**
	* get direction for an IO port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	*/
        uint8_t get_port_direction(uint8_t port);

        /**
	* set direction for the IO bus
	* @param direction - 0 to 65535 (0xFFFF).  For each bit 1 = input, 0 = output
	*/
        void set_bus_direction(uint16_t direction);

        /**
	* get direction for the IO bus
	*/
        uint16_t get_bus_direction();

        /**
	* set the internal 100K pull-up resistors for an individual pin
	* @param pin - 1 to 16
	* @param value - 1 = enabled, 0 = disabled
	*/
        void set_pin_pullup(uint8_t pin, uint8_t value);

        /**
	* get the internal 100K pull-up resistors for an individual pin
	* @param pin - 1 to 16
	*/
        uint8_t get_pin_pullup(uint8_t pin);

        /**
	* set the internal 100K pull-up resistors for the selected IO port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - 0 to 255 (0xFF). For each bit 1 = enabled, 0 = disabled
	*/
        void set_port_pullups(uint8_t port, uint8_t value);

        /**
	* get the internal 100K pull-up resistors for the selected IO port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	*/
        uint8_t get_port_pullups(uint8_t port);

        /**
	* set internal 100K pull-up resistors for the IO bus
	* @param value - 0 to 65535 (0xFFFF).  For each bit 1 = enabled, 0 = disabled
	*/
        void set_bus_pullups(uint16_t value);

        /**
	* get internal 100K pull-up resistors for the IO bus
	*/
        uint16_t get_bus_pullups();

        /**
	* write to an individual pin 1 - 16
	* @param pin - 1 to 16
	* @param value - 0 = logic low, 1 = logic high
	*/
        void write_pin(uint8_t pin, uint8_t value);

        /**
	* write to all pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - 0 to 255 (0xFF)
	*/
        void write_port(uint8_t port, uint8_t value);

        /**
	* write to all pins on the selected bus
	* @param value - 0 to 65535 (0xFFFF). For each bit 1 = logic high, 0 = logic low
	*/
        void write_bus(uint16_t value);

        /**
	* read the value of an individual pin
	* @param pin - 1 to 16
	* @returns - 0 = logic low, 1 = logic high
	*/
        uint8_t read_pin(uint8_t pin);

        /**
	* read all pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @returns - 0 to 255 (0xFF). For each bit 1 = logic high, 0 = logic low
	*/
        uint8_t read_port(uint8_t port);

        /**
	* read all pins on the selected bus
	* @returns - 0 to 65535 (0xFFFF). For each bit 1 = logic high, 0 = logic low
	*/
        uint16_t read_bus();

        /**
	* invert the polarity of the selected pin
	* @param pin - 1 to 16
	* @param polarity - 0 = non-inverted, 1 = inverted
	*/
        void invert_pin(uint8_t pin, uint8_t polarity);

        /**
	* get the polarity of the selected pin
	* @param pin - 1 to 16
	*/
        uint8_t get_pin_polarity(uint8_t pin);

        /**
	* invert the polarity of the pins on a selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param polarity - 0 to 255 (0xFF). For each bit 0 = non-inverted, 1 = inverted
	*/
        void invert_port(uint8_t port, uint8_t polarity);

        /**
	* get the polarity of the selected pin
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	*/
        uint8_t get_port_polarity(uint8_t port);

        /**
	* invert the polarity of the pins on a selected bus
	* @param polarity - 0 to 65535 (0xFFFF). For each bit 0 = non-inverted, 1 = inverted
	*/
        void invert_bus(uint16_t polarity);

        /**
	* get the polarity of the bus
	*/
        uint16_t get_bus_polarity();

        /**
	* Set the interrupt pins to be mirrored or for separate ports
	* @param value - 1 = The interrupt pins are internally connected, 0 = The interrupt pins are not connected. INTA is associated with PortA and INTB is associated with PortB
	*/
        void mirror_interrupts(uint8_t value);

        /**
	* Set the polarity of the interrupt output pins.
	* @param value - 1 = Active-high, 0 = Active-low.
	*/
        void set_interrupt_polarity(uint8_t value);

        /**
	* Get the polarity of the interrupt output pins.
	*/
        uint8_t get_interrupt_polarity();

        /**
	* Set the type of interrupt for each pin on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - 0 to 255 (0xFF). For each bit 1 = interrupt is fired when the pin matches the default value, 0 = the interrupt is fired on state change
	*/
        void set_interrupt_type(uint8_t port, uint8_t value);

        /**
	* Get the type of interrupt for each pin on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	*/
        uint8_t get_interrupt_type(uint8_t port);

        /**
	* These bits set the compare value for pins configured for interrupt-on-change on the selected port.
	* If the associated pin level is the opposite from the register bit, an interrupt occurs.
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - default state for the port. 0 to 255 (0xFF).
	*/
        void set_interrupt_defaults(uint8_t port, uint8_t value);

        /**
	* Get the compare value for pins configured for interrupt-on-change on the selected port.
	* If the associated pin level is the opposite from the register bit, an interrupt occurs.
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	*/
        uint8_t get_interrupt_defaults(uint8_t port);

        /**
	* Enable interrupts for the selected pin
	* @param pin - 1 to 16
	* @param value - 0 = interrupt disabled, 1 = interrupt enabled
	*/
        void set_interrupt_on_pin(uint8_t pin, uint8_t value);

        /**
	* Get the interrupt enable status for the selected pin
	* @param pin - 1 to 16
	*/
        uint8_t get_interrupt_on_pin(uint8_t pin);

        /**
	* Enable interrupts for the pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - 0 to 255 (0xFF). For each bit 0 = interrupt disabled, 1 = interrupt enabled
	*/
        void set_interrupt_on_port(uint8_t port, uint8_t value);

        /**
	* Get the interrupt enable status for the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	*/
        uint8_t get_interrupt_on_port(uint8_t port);

        /**
	* Enable interrupts for the pins on the selected bus
	* @param value - 0 to 65535 (0xFFFF). For each bit 0 = interrupt disabled, 1 = interrupt enabled
	*/
        void set_interrupt_on_bus(uint16_t value);

        /**
	* Get the interrupt enable status for the selected bus
	*/
        uint16_t get_interrupt_on_bus();

        /**
	* read the interrupt status for the pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @returns - 0 to 255 (0xFF). For each bit 1 = interrupt triggered, 0 = interrupt not triggered
	*/
        uint8_t read_interrupt_status(uint8_t port);

        /**
	* read the value from the selected port at the time of the last interrupt trigger
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @returns - 0 to 255 (0xFF). For each bit 1 = interrupt triggered, 0 = interrupt not triggered
	*/
        uint8_t read_interrupt_capture(uint8_t port);

        /**
	* Reset the interrupts A and B to 0
	*/
        void reset_interrupts(void);

    private:
        const char* fileName = "/dev/i2c-1"; // change to /dev/i2c-0 if you are using a Raspberry Pi revision 0002 or 0003 model B
        
        // MCP23017 register addresses
        enum MCP23017
        {
            IODIRA = 0x00,   // IO direction A - 1= input 0 = output
            IODIRB = 0x01,   // IO direction B - 1= input 0 = output
            IPOLA = 0x02,    // Input polarity A
            IPOLB = 0x03,    // Input polarity B
            GPINTENA = 0x04, // Controls the interrupt-onchange on port A
            GPINTENB = 0x05, // Controls the interrupt-onchange on port B
            DEFVALA = 0x06,  // Default value for port A
            DEFVALB = 0x07,  // Default value for port B
            INTCONA = 0x08,  // Interrupt control register for port A
            INTCONB = 0x09,  // Interrupt control register for port B
            IOCON = 0x0A,    // see datasheet for configuration register
            GPPUA = 0x0C,    // pull-up resistors for port A
            GPPUB = 0x0D,    // pull-up resistors for port B
            INTFA = 0x0E,    // Interrupt condition on port A for any enabled pin
            INTFB = 0x0F,    // Interrupt condition on port B for any enabled pin
            INTCAPA = 0x10,  // Captures the GPIO port A value at the time the interrupt occurred
            INTCAPB = 0x11,  // Captures the GPIO port B value at the time the interrupt occurred
            GPIOA = 0x12,    // Data port A
            GPIOB = 0x13,    // Data port B
            OLATA = 0x14,    // Output latches for port A
            OLATB = 0x15     // Output latches for port B
        };

        //uint8_t config; // config register
        int i2cbus;         // I2C bus
        uint8_t i2caddress; // I2C address
        /**/
        uint8_t port_a_dir;     // port a direction
        uint8_t port_b_dir;     // port b direction
        uint8_t portaval;       // port a value
        uint8_t portbval;       // port b value
        uint8_t porta_pullup;   // port a pull-up resistors
        uint8_t portb_pullup;   // port a pull-up resistors
        uint8_t porta_polarity; // input polarity for port a
        uint8_t portb_polarity; // input polarity for port b
        uint8_t intA;           // interrupt control for port a
        uint8_t intB;           // interrupt control for port a

        uint8_t buf[3];
        // local methods

        /**
	    * private method for reading a byte from the I2C port
	    */
        uint8_t read_byte_data(uint8_t reg);

        /**
	    * private method for reading a word from the I2C port
	    */
        uint16_t read_word_data(uint8_t reg);

        /**
	    * private method for writing a byte to the I2C port
	    */
        void write_byte_data(uint8_t reg, uint8_t value);

        /**
	    * private method for writing a word to the I2C port
	    */
        void write_word_data(uint8_t reg, uint16_t value);

        /**
	    * private method for updating a bit within a byte
	    */
        uint8_t updatebyte(uint8_t byte, uint8_t bit, uint8_t value);

        /**
	    * private method for checking the status of a bit within a byte
	    */
        uint8_t checkbit(uint8_t byte, uint8_t bit);

        /**
	    * private method for setting the value of a single bit within the device registers
	    */
        void set_pin(uint8_t pin, uint8_t value, uint8_t a_register, uint8_t b_register);

        /**
	    * private method for getting the value of a single bit within the device registers
	    */
        uint8_t get_pin(uint8_t pin, uint8_t a_register, uint8_t b_register);

        /**
	    * private method for setting the value of a device register
	    */
        void set_port(uint8_t port, uint8_t value, uint8_t a_register, uint8_t b_register);

        /**
	    * private method for getting the value of a device register
	    */
        uint8_t get_port(uint8_t port, uint8_t a_register, uint8_t b_register);

        /**
	    * private method for writing a 16-bit value to two consecutive device registers
	    */
        void set_bus(uint16_t value, uint8_t a_register);
    };
}
