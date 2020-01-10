#ifndef DAQ_SLAVE_CONFIG
#define DAQ_SLAVE_CONFIG
#include <Arduino.h>
#include <Ethernet.h>

// modbus properties
const uint8_t deviceId = 69;

const int lastUpdateLowAddr = 	30001;
const int lastUpdateHighAddr = lastUpdateLowAddr + 1;

const int pressureTransducerAddr = 	31001;
const int loadCellAddr =32001;
const int thermoCoupleAddr = 33001;

// DAQ properties
const int numPressureTransducers = 7;
const int numLoadcells = 1;
const int numThermoCouples = 3;

// pin mappings
static const uint8_t pressureTransducerPins[numPressureTransducers] = {A0, A1, A2, A3, A4, A5, A6};
static const uint8_t loadCellPins[numLoadcells] = {A11};
const uint8_t ETHERNET_CS_PIN = 10;
const uint8_t THERMOCOUPLE_CS_PIN = 9;
const uint8_t MUX_ENABLE_PIN = 7;
const uint8_t THERMOCOUPLE_A0 = 4;
const uint8_t THERMOCOUPLE_A1 = 5;
const uint8_t THERMOCOUPLE_A2 = 6;

// network settings
static uint8_t macAddress[] = { 0xAB, 0xBC, 0xCD, 0xDE, 0xEF, 0x00 };
const uint16_t PORT = 502;
const long MAX_TIMEOUT = 3000;

#endif