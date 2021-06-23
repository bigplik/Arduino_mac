// biblioteka blinków diodą LED


#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class Flasher
{
	public:
		Flasher(int pin, int duration);
		void flash(int times);
	private:
		int _pin;
		int _d;
};
