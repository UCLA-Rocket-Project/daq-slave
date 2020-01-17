#include "shared.h"
#include "config.h"
#include <Arduino.h>
#include <TCMux.h>
#include "errorTypes.h"

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
uint8_t nextTc = 0;
uint8_t err;
TCMux tc;
void updateThermoCouples() {
	thermoCouples[nextTc] = tc.readTC(nextTc, err);
	if(!err) { // only progress when we get a valid value
		nextTc++;
		if(nextTc >= numThermoCouples) {
			nextTc = 0;
		}
	}
}