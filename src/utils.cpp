#include "shared.h"
#include "errorTypes.h"

// for stuff that is guaranteed to work
void prepPins() {
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(MUX_ENABLE_PIN, OUTPUT);
	pinMode(THERMOCOUPLE_A0, OUTPUT);
	pinMode(THERMOCOUPLE_A1, OUTPUT);
	pinMode(THERMOCOUPLE_A2, OUTPUT);
	digitalWrite(MUX_ENABLE_PIN, HIGH);
}
// prepares registers
void prepIregs(int addr, int num) {
	for(int i = 0; i < num; i++) {
		modbus.addIreg(addr + i, 0xFFFF);
	}
}
// writes registers
void writeIregs(int addr, uint16_t *arr, int num) {
	for(int i = 0; i < num; i++) {
		modbus.Ireg(addr + i, arr[i]);
	}
}

// error handling
uint8_t ERROR_FLAGS = 0;
void flagError(uint8_t errType) {
	digitalWrite(LED_BUILTIN, HIGH);
	ERROR_FLAGS |= 1 << errType;
	if(errType <= UNKNOWN_CRITICAL_FAIL) {
		Serial.print(F("Critical Error: "));
		Serial.println(ERROR_FLAGS, BIN);
		while(1);
	}
}