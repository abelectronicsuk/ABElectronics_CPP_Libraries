/*
 ================================================
 ABElectronics UK IO Pi 32-Channel Port Expander
 Version 1.1 Created 23/01/2015 - Updated 27/05/2015
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
	*/
  IoPi(char i2caddress);

  /**
	* set IO direction for an individual pin
	* @param pins - 1 to 16
	* @param direction - 1 = input, 0 = output
	*/
  void set_pin_direction(char pin, char direction);

  /**
	* set direction for an IO port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param direction - 1 = input, 0 = output
	*/
  void set_port_direction(char port, char direction);

  /**
	* set the internal 100K pull-up resistors for an individual pin
	* @param pin - 1 to 16
	* @param value - 1 = enabled, 0 = disabled
	*/
  void set_pin_pullup(char pinval, char value);

  /**
	* set the internal 100K pull-up resistors for the selected IO port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - number between 0 and 255 or 0x00 and 0xFF
	*/
  void set_port_pullups(char port, char value);

  /**
	* write to an individual pin 1 - 16
	* @param pin - 1 to 16
	* @param value - 0 = logic level low, 1 = logic level high
	*/
  void write_pin(char pin, char value);

  /**
	* write to all pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - number between 0 and 255 or 0x00 and 0xFF
	*/
  void write_port(char port, char value);

  /**
	* read the value of an individual pin
	* @param pin - 1 to 16
	* @returns - 0 = logic level low, 1 = logic level high
	*/
  int read_pin(char pinval);

  /**
	* read all pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @returns - number between 0 and 255 or 0x00 and 0xFF
	*/
  char read_port(char port);

  /**
	* invert the polarity of the pins on a selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param polarity - 0 = same logic state of the input pin, 1 = inverted logic	state of the input pin
	*/
  void invert_port(char port, char polarity);

  /**
	* invert the polarity of the selected pin
	* @param pin - 1 to 16
	* @param polarity - 0 = same logic state of the input pin, 1 = inverted logic	state of the input pin
	*/
  void invert_pin(char pin, char polarity);

  /**
	* Set the interrupt pins to be mirrored or for separate ports
	* @param value - 1 = The char pins are internally connected, 0 = The char pins are not connected. INTA is associated with PortA and INTB is associated with PortB
	*/
  void mirror_interrupts(char value);

  /**
	* This sets the polarity of the char output pins.
	* @param value - 1 = Active-high, 0 = Active-low.
	*/
  void set_interrupt_polarity(char value);

  /**
	* Sets the type of interrupt for each pin on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - 1 = interrupt is fired when the pin matches the default value, 0 = the interrupt is fired on state change
	*/
  void set_interrupt_type(char port, char value);

  /**
	* These bits set the compare value for pins configured for interrupt-on-change on the selected port.
	* If the associated pin level is the opposite from the register bit, an interrupt occurs.
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - default state for the port
	*/
  void set_interrupt_defaults(char port, char value);

  /**
	* Enable interrupts for the pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - number between 0 and 255 or 0x00 and 0xFF
	*/
  void set_interrupt_on_port(char port, char value);

  /**
	* Enable interrupts for the selected pin
	* @param pin - 1 to 16
	* @param value - 0 = interrupt disabled, 1 = interrupt enabled
	*/
  void set_interrupt_on_pin(char pin, char value);

  /**
	* read the interrupt status for the pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	*/
  char read_interrupt_status(char port);

  /**
	* read the value from the selected port at the time of the last interrupt trigger
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	*/
  char read_interrupt_capture(char port);

  /**
	* set the interrupts A and B to 0
	*/
  void reset_interrupts(void);

  private:

	char config; // config register
  int i2cbus; // I2C bus 
  char i2caddress; // I2C address
  char port_a_dir; // port a direction
  char port_b_dir; // port b direction
  char portaval; // port a value
  char portbval; // port b value
  char porta_pullup; // port a pull-up resistors
  char portb_pullup; // port a pull-up resistors
  char porta_polarity; // input polarity for port a
  char portb_polarity; // input polarity for port b
  char intA; // interrupt control for port a
  char intB; // interrupt control for port a
  unsigned char buf[10];
    // local methods

  /**
	* private method for reading a byte from the I2C port
	*/
  int read_byte_data(char reg);
  
  /**
	* private method for writing a byte to the I2C port
	*/
  void write_byte_data(char reg, char value);

  /**
	* private method for updating a bit within a byte
	*/
  char updatebyte(char byte, char bit, char value);

  /**
	* private method for checking the status of a bit within a byte
	*/
  char checkbit(char byte, char bit);



};
}
