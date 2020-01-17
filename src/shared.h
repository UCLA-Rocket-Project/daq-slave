#ifndef DAQ_SLAVE_BUFFERS
#define DAQ_SLAVE_BUFFERS
#include <stdint.h>
#include "config.h"
#include <ModbusSerial.h>

extern ModbusSerial modbus;

extern uint16_t pressureTransducers[numPressureTransducers],
	thermoCouples[numThermoCouples],
	loadCells[numLoadcells];


void prepPins();
void prepIregs(int addr, int num);
void prepCoils(int addr, int num);
void writeIregs(int addr, uint16_t *arr, int num);

void updatePressureTransducers();
void updateThermoCouples();
void updateLoadcells();

void flagError(uint8_t errType = 7);

#endif