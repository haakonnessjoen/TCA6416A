// TCA6416A module
// Copyright 2019 Håkon Nessjøen
#ifndef TCA6416A_H
#define TCA6416A_H

#include "Wire.h"

#define TCAREG_INPUT0 0x00
#define TCAREG_INPUT1 0x01
#define TCAREG_OUTPUT0 0x02
#define TCAREG_OUTPUT1 0x03
#define TCAREG_POLARITY0 0x04
#define TCAREG_POLARITY1 0x05
#define TCAREG_CONFIG0 0x06
#define TCAREG_CONFIG1 0x07

/*
 TODO: If I understood the manual correctly, the command only needs to be sent to change active register
 so for performance I want to store the last used register, and if you are for example reading multiple times,
 you would not need to resend the command the second time to read two more bytes. And the same way about writing.
 The registers are paired, so each byte writes to register (REGISTER | (i % 2)) indefinitely.
 */

class TCA6416A {
public:
	void begin(uint8_t address);
	void pin_mode(uint8_t pinNum, int mode);
	void pin_write(uint8_t pinNum, uint8_t level);
	int  pin_read(uint8_t pinNum);
	void port_write(uint16_t i2cportval);
	uint16_t port_read();
	void mode_write(uint16_t i2cportval);
	uint16_t mode_read();

private:
	TwoWire TW;
    uint8_t i2caddr;
    uint8_t i2cwidth;
	uint16_t pinState;
	uint16_t pinModes;
};

#endif // TCA6416A_H
