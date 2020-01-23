#ifndef TC_MUX
#define TC_MUX
#include <stdint.h>

#ifdef TC_DBG
#define DBG_LOGLN(x) Serial.println(x)
#define DBG_LOG(x) Serial.print(x)
const uint16_t RESPONSE_TIME = 5000;
#else
#define DBG_LOGLN(x) {}
#define DBG_LOG(x) {}
const uint16_t RESPONSE_TIME = 70;
#endif


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

	int16_t readTC(uint8_t index, uint8_t &err);
	int16_t readTC(uint8_t index, uint8_t &err, int16_t &internalTemp);
	bool ready();
	uint8_t samplingSensor();
	float toCentigrade(int16_t reading);
	float toFreedomUnits(int16_t reading);

private:
	unsigned long readingStartTime = 0;
	int16_t cachedReadings[8];
	int16_t cachedInternal;
	int8_t readingIndex = -1;
	bool readComplete = false;
	bool setup = false;
	void setupPins();
	void muxPins(uint8_t index);
};

const uint8_t STALE_VALUE = 4;
const uint8_t FAULT_SHORT_HIGH = 3;
const uint8_t FAULT_SHORT_GND = 2;
const uint8_t FAULT_SHORT_OPEN = 1;
#endif