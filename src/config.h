#ifndef DAQ_SLAVE_CONFIG
#define DAQ_SLAVE_CONFIG
#include <Arduino.h>

// modbus properties
const int pressureTransducerAddr = 0x30;
const int loadCellAddr = 0x40;
const int thermoCoupleAddr = 0x50;

// DAQ properties
const int numPressureTransducers = 7;
const int numLoadcells = 1;
const int numThermoCouples = 3;

// pin mappings
static const uint8_t pressureTransducerPins[numPressureTransducers] = {A0, A1, A2, A3, A4, A5, A6, A7};
static const uint8_t loadCellPins[numLoadcells] = {A11};

#endif