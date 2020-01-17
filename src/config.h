#ifndef DAQ_SLAVE_CONFIG
#define DAQ_SLAVE_CONFIG
#include <Arduino.h>

// DAQ properties
const int numPressureTransducers = 2;
const int numLoadcells = 1;
const int numThermoCouples = 3;
const int updateMs = 20;

// modbus properties
const uint8_t deviceId = 15;

const int lastUpdateHighAddr = 	1;
const int lastUpdateLowAddr = lastUpdateHighAddr + 1;
const int pressureTransducerAddr = 1001;
const int thermoCoupleAddr = 1021;
const int loadCellAddr = 1031;
const int errorAddr = 3001;


// pin mappings
static constexpr uint8_t pressureTransducerPins[numPressureTransducers] = {A0, A1};
static constexpr uint8_t loadCellPins[numLoadcells] = {A5};
const uint8_t TX_PIN = 10;
const uint8_t THERMOCOUPLE_CS_PIN = 9;
const uint8_t MUX_ENABLE_PIN = 7;
const uint8_t THERMOCOUPLE_A0 = 4;
const uint8_t THERMOCOUPLE_A1 = 5;
const uint8_t THERMOCOUPLE_A2 = 6;
const uint8_t TC_MOSI = 11;
const uint8_t TC_MISO = 12;
const uint8_t TC_SCK = 13;

// network settings
static constexpr uint8_t macAddress[6] = { 0xFE, 0xED, 0xDE, 0xAD, 0xBE, 0xEF  };

#endif