#include <TCA6416A.h>

TCA6416A pins;

void setup() {
	pins.begin(0); // Address 0 or 1, depending on your addr-pin

	pins.pin_mode(0, OUTPUT);
	pins.pin_mode(1, INPUT);
}

void loop() {
	pins.pin_write(0, HIGH);
	delay(200);
	pins.pin_write(0, LOW);
	delay(200;

	// If pin 1 (counted from 0) is high, stop the loop
	while (pins.pin_read(1) == HIGH);
}
