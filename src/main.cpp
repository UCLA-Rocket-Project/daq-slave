#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoModbus.h>
#include "config.h"
#include "shared.h"

ModbusTCPServer modbus;
long lastUpdate = 0;
void setup() {
	Serial.begin(115200);
	while(!Serial);

	Serial.println(F("Initializing DAQ Slave"));

	// TODO: initialize ethernet
	modbus.configureInputRegisters(pressureTransducerAddr, numPressureTransducers);
	modbus.configureInputRegisters(loadCellAddr, numLoadcells);
	modbus.configureInputRegisters(thermoCoupleAddr, numThermoCouples);

	lastUpdate = millis();
}

void loop() {
	modbus.poll();

	// update stuff
	updatePressureTransducers();
	modbus.writeInputRegisters(pressureTransducerAddr, pressureTransducers, numPressureTransducers);
	
	updateLoadcells();
	modbus.writeInputRegisters(loadCellAddr, loadCells, numLoadcells);

	updateThermoCouples();
	modbus.writeInputRegisters(thermoCoupleAddr, thermoCouples, numThermoCouples);

	// print out update HZ
	Serial.println(1000 / (millis() - lastUpdate));
	lastUpdate = millis();
}