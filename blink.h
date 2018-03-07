#include "Arduino.h"

class blink
{
	public:
		blink(int str);
		void on(int deg);
		void off(int deg);
	private:
		int pin;
};

