#ifndef DAQ_SLAVE_BUFFERS
#define DAQ_SLAVE_BUFFERS
#include <stdint.h>
#include "config.h"

extern uint16_t pressureTransducers[numPressureTransducers],
	thermoCouples[numThermoCouples],
	loadCells[numLoadcells];

void prep();
void updatePressureTransducers();
void updateThermoCouples();
void updateLoadcells();

extern uint8_t ERROR_FLAGS;
void flagError(uint8_t errType = 7);

#endif