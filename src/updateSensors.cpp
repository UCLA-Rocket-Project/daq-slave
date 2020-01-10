#include "shared.h"
#include "config.h"
#include <Arduino.h>
#include "errorTypes.h"
#include <SPI.h>
#include <Adafruit_MAX31855.h>

uint16_t pressureTransducers[numPressureTransducers],
	thermoCouples[numThermoCouples],
	loadCells[numLoadcells];

void updatePressureTransducers() {
	for(int i = 0; i < numPressureTransducers; i++) {
		pressureTransducers[i] = analogRead(pressureTransducerPins[i]);
	}
}
void updateLoadcells() {
	for(int i = 0; i < numLoadcells; i++) {
		loadCells[i] = analogRead(loadCellPins[i]);
	}
}
Adafruit_MAX31855 thermocouple(THERMOCOUPLE_CS_PIN);
void muxPins(uint8_t target);
void updateThermoCouples() {
	for(int i = 0; i < numThermoCouples; i++) {
		muxPins(i);
		// claimed that we only required a 0.1 millisecond wait. doubled for safety
		delayMicroseconds(200);
		double reading = thermocouple.readCelsius();
		if(isnan(reading)) {
			flagError(THERMOCOUPLE_NAN);
		}
		thermoCouples[i] = reading;
	}
}

void muxPins(uint8_t target) {
	digitalWrite(THERMOCOUPLE_A0, target & 0x1);
	digitalWrite(THERMOCOUPLE_A1, target & 0x10);
	digitalWrite(THERMOCOUPLE_A2, target & 0x100);
}