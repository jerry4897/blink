#include "Arduino.h"
#include "blink.h"

blink::blink(int pin_num)
{
	pinMode(pin_num, OUTPUT);
	pin = pin_num;
}
void blink::on(int deg) {
	digitalWrite(pin, HIGH);
	delay(deg);
}

void blink::off(int deg) {
	digitalWrite(pin, LOW);
	delay(deg);
}
