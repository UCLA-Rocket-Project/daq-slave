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
// prepares coils
void prepCoils(int addr, int num) {
	for(int i = 0; i < num; i++) {
		modbus.addCoil(addr + i, false);
	}
}
// writes registers
void writeIregs(int addr, uint16_t *arr, int num) {
	for(int i = 0; i < num; i++) {
		modbus.Ireg(addr + i, arr[i]);
	}
}

// error handling
void flagError(uint8_t errType) {
	digitalWrite(LED_BUILTIN, HIGH);
	modbus.Coil(errorAddr + errType, true);
	if(errType <= UNKNOWN_CRITICAL_FAIL) {
		Serial.print(F("Critical Error: "));
		Serial.println(errType);
		while(1);
	}
}