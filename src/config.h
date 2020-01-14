#ifndef DAQ_SLAVE_CONFIG
#define DAQ_SLAVE_CONFIG
#include <Arduino.h>
#include <Ethernet.h>

// modbus properties
const uint8_t deviceId = 69;

const int lastUpdateHighAddr = 	1;
const int lastUpdateLowAddr = lastUpdateHighAddr + 1;
const int pressureTransducerAddr = 1001;
const int loadCellAddr = 2001;
const int thermoCoupleAddr = 3001;
const int errorAddr = 3001;

// DAQ properties
const int numPressureTransducers = 7;
const int numLoadcells = 1;
const int numThermoCouples = 3;

// pin mappings
static constexpr uint8_t pressureTransducerPins[numPressureTransducers] = {A0, A1, A2, A3, A4, A5, A6};
static constexpr uint8_t loadCellPins[numLoadcells] = {A11};
const uint8_t ETHERNET_CS_PIN = 10;
const uint8_t THERMOCOUPLE_CS_PIN = 9;
const uint8_t MUX_ENABLE_PIN = 7;
const uint8_t THERMOCOUPLE_A0 = 4;
const uint8_t THERMOCOUPLE_A1 = 5;
const uint8_t THERMOCOUPLE_A2 = 6;

// network settings
static constexpr uint8_t macAddress[] = { 0x52,0x50,0x2d,0x44,0x41,0x51 };

// static IP stuff (comment out below to use other fields)
//#define USE_DHCP
static constexpr uint8_t staticIp[] = { 10, 10, 10, 1 };
static constexpr uint8_t gatewayIp[] = { 192, 168, 1, 1 };
static constexpr uint8_t dnsIp[] = { 1, 1, 1, 1 };
#define MODBUSIP_PORT 502

#endif