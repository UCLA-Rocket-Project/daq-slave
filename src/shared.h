#ifndef DAQ_SLAVE_BUFFERS
#define DAQ_SLAVE_BUFFERS
#include <stdint.h>
#include "config.h"

extern uint16_t pressureTransducers[numPressureTransducers],
	thermoCouples[numThermoCouples],
	loadCells[numLoadcells];

void updatePressureTransducers();
void updateThermoCouples();
void updateLoadcells();

#endif