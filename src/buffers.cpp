#include "shared.h"
#include "config.h"
#include <Arduino.h>
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
void updateThermoCouples() {
	// grab the arduino shield stuff
}