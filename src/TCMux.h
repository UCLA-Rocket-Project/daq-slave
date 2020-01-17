#ifndef TC_MUX
#define TC_MUX
#include <stdint.h>

class TCMux {
public:
	uint8_t pinEn,
		pinA0,
		pinA1,
		pinA2,
		pinSo,
		pinSc,
		pinCs;

	//ctor should probably have properties
	TCMux(uint8_t pinEn, 
		uint8_t pinA0, 
		uint8_t pinA1,
		uint8_t pinA2,
		uint8_t pinSo,
		uint8_t pinSc,
		uint8_t pinCs);
	TCMux(): TCMux(7, 4, 5, 6, 12, 13, 9) {};

	uint16_t readTC(uint8_t index, uint8_t &err);
	uint16_t readTC(uint8_t index, uint8_t &err, uint16_t &internalTemp);

private:
	void setupPins();
	void muxPins(uint8_t index);
};

const int FAULT_SHORT_HIGH = 3;
const int FAULT_SHORT_GND = 2;
const int FAULT_SHORT_OPEN = 1;
#endif