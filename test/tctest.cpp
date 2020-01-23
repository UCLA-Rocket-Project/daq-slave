#define TC_DBG
#include <Arduino.h>
#include <unity.h>
#include <TCMux.h>

TCMux mux;
void setup() {
	UNITY_BEGIN();
	Serial.begin(115200);
	Serial.println("If you're here, then you must have failed");
}
void loop() {
	uint8_t err;
	unsigned int i = mux.readTC(0, err);
	switch(err) {
	case 0:
		Serial.print(F("C: "));
		Serial.println(mux.toCentigrade(i));
		break;
	case FAULT_SHORT_GND:
		Serial.println(F("FAULT: SHORT TO GND"));
		break;
	case FAULT_SHORT_HIGH:
		Serial.println(F("FAULT: SHORT TO HIGH"));
		break;
	case FAULT_SHORT_OPEN:
		Serial.println(F("FAULT: SHORT OPEN"));
		break;
	case STALE_VALUE:
		break;
	default:
		Serial.print(F("WTF! HOW DID I GET ERR CODE: "));
		Serial.print(err);
	}
}