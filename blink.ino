#include "blink.h"

blink Blink(D4);

void setup() {
  Serial.begin(115200);
  Serial.println("\nBlink Version 1.0 SukHwan Kim");
}

void loop() {
  Blink.on(1000);
  Blink.off(500);
}
