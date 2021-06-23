#ifndef Expander_h
#define Expander_h
/**
 * Class definition for the Expander board.
 */
class Expander {
public:
	/**
	 * Constructor for the class
	 */
	Expander();

	/**
	 * Set the address and pins to be used for SDA and CLK in the Two Wire (I2C) protocol.
	 */
	void begin(uint8_t address, uint8_t sda, uint8_t clk);

	/**
	 * Set the bit (range 0-7) of the GPIOs to the supplied value.
	 */
	void setBit(uint8_t bit, bool value);

	/**
	 * Write the value of the byte as the output of the GPIOs.
	 */
	void setByte(uint8_t value);

	/**
	 * Get the value of the byte of the GPIOs as input.
	 */
	uint8_t getByte();

	/**
	 * Get the value of the bit of the GPIO as input.
	 */
	bool getBit(uint8_t bit);
        

        //extra from PCF8574 library
	/**
	 * Set the direction of a pin (OUTPUT, INPUT or INPUT_PULLUP)
	 * 
	 * @param pin The pin to set
	 * @param mode The new mode of the pin
	 * @remarks INPUT_PULLUP does physicaly the same thing as INPUT (no software pull-	up resistors available) but is REQUIRED if you use external pull-up resistor
	 */
	void pinMode(uint8_t pin, uint8_t mode);

	/**
	 * Set the state of a pin (HIGH or LOW)
	 * 
	 * @param pin The pin to set
	 * @param value The new state of the pin
	 * @remarks Software pull-up resistors are not available on the PCF8574
	 */
	void digitalWrite(uint8_t pin, uint8_t value);

	/**
	 * Read the state of a pin
	 * 
	 * @param pin The pin to read back
	 * @return
	 */
	uint8_t digitalRead(uint8_t pin);

	/**
	 * Set the state of all pins in one go
	 * 
	 * @param value The new value of all pins (1 bit = 1 pin, '1' = HIGH, '0' = LOW)
	 */
	void write(uint8_t value);

	/**
	 * Read the state of all pins in one go
	 * 
	 * @return The current value of all pins (1 bit = 1 pin, '1' = HIGH, '0' = LOW)
	 */
	uint8_t read();

	/**
	 * Exactly like write(0x00), set all pins to LOW
	 */
	void clear();

	/**
	 * Exactly like write(0xFF), set all pins to HIGH
	 */
	void set();

	/**
	 * Toggle the state of a pin
	 */
	void toggle(uint8_t pin);

	/**
	 * Mark a pin as "pulled up"
	 * 
	 * @warning DO NOTHING - FOR RETRO COMPATIBILITY PURPOSE ONLY
	 * @deprecated
	 * @param pin Pin the mark as "pulled up"
	 */
	void pullUp(uint8_t pin);

	/**
	 * Mark a pin as "pulled down"
	 * 
	 * @warning DO NOTHING - FOR RETRO COMPATIBILITY PURPOSE ONLY
	 * @deprecated
	 * @param pin Pin the mark as "pulled down"
	 */
	void pullDown(uint8_t pin);

	/**
	 * Make a pin blink N times for T duration
	 * 
	 * @warning Blocking function, not recommended for new code
	 * @deprecated
	 * @param pin The pin to blink
	 * @param count The number of ON/OFF couples to execute
	 * @param duration The duration of the whole blink action in milliseconds
	 */
	void blink(uint8_t pin, uint16_t count, uint32_t duration);

	/** 
	 * Read GPIO states and store them in _PIN variable
	 *
	 * @remarks Before reading current GPIO states, current _PIN variable value is 		moved to _oldPIN variable
	 */
	void readGPIO();

	/** 
	 * Write value of _PORT variable to the GPIO
	 * 
	 * @remarks Only pin marked as OUTPUT are set, for INPUT pins their value are 		unchanged
	 * @warning To work properly (and avoid any states conflicts) readGPIO() MUST be 	called before call this function !
	 */
	void updateGPIO();


private:
	int m_address;
	uint8_t m_currentOutput;
};
#endif
// Nothing after here
