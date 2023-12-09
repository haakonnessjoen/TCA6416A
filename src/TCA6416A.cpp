// TCA6416A module
// Copyright 2019 Håkon Nessjøen
#include <Arduino.h>
#include "TCA6416A.h"

// NB!: Only address 0 or 1
bool TCA6416A::begin(uint8_t addr_bit, TwoWire *theWire) {
	i2caddr = 0x20 | addr_bit;
	TW = theWire;
	TW->begin();

	/// Check if device is connected
	TW->beginTransmission((int)i2caddr);
	if (TW->endTransmission() != 0) {
		return false;
	}

	port_read();
	mode_read();

	return true;
}

void TCA6416A::pin_write(uint8_t pinNum, uint8_t level) {
	uint16_t mask = 1 << pinNum;

	if (level == HIGH) {
		pinState |= mask;
	} else {
		pinState &= ~mask;
	}

	port_write(pinState);
}

void TCA6416A::pin_mode(uint8_t pinNum, int mode) {
	uint16_t mask = 1 << pinNum;

	if (mode == INPUT) {
		pinModes |= mask;
	} else {
		pinModes &= ~mask;
	}

	mode_write(pinModes);
}

int TCA6416A::pin_read(uint8_t pinNum) {
	uint16_t mask = 1 << pinNum;

	port_read();

	if ((pinState & mask) == mask) {
		return 1;
	} else {
		return 0;
	}
}

void TCA6416A::port_write(uint16_t i2cportval) {
	TW->beginTransmission((int)i2caddr);
	TW->write(TCAREG_OUTPUT0);

	TW->write(i2cportval & 0x00FF);
	TW->write(i2cportval >> 8 );

	TW->endTransmission();

	pinState = i2cportval;
}

uint16_t TCA6416A::port_read() {
	uint16_t tempInput;
	TW->beginTransmission((int)i2caddr);
	TW->write(TCAREG_INPUT0);
	TW->endTransmission();

	TW->requestFrom((int)i2caddr, (int)i2cwidth);

	tempInput = TW->read();
	tempInput |= TW->read() << 8;

	pinState = (pinState & ~pinModes) | (tempInput & pinModes);

	return pinState;
}

void TCA6416A::mode_write(uint16_t modes) {
	TW->beginTransmission((int)i2caddr);
	TW->write(TCAREG_CONFIG0);

	TW->write(modes & 0x00FF);
	TW->write(modes >> 8 );

	TW->endTransmission();

	pinModes = modes;
}

uint16_t TCA6416A::mode_read() {
	TW->beginTransmission((int)i2caddr);
	TW->write(TCAREG_CONFIG0);
	TW->endTransmission();

	TW->requestFrom((int)i2caddr, (int)i2cwidth);

	pinModes = TW->read();
	pinModes |= TW->read() << 8;

	return pinModes;
}
