#include <SPI.h>
#include <Ethernet.h>
#include <Modbus.h>
#include <ModbusIP.h>
#include "config.h"
#include "shared.h"
#include "errorTypes.h"

ModbusIP modbus;
void setup() {
	prepPins();
	Serial.begin(115200);
	while(!Serial);

	Serial.println(F("Initializing DAQ Slave"));
	
	// initialize ethernet / networking
	Serial.println(F("Setting up ethernet...."));
	Ethernet.init(ETHERNET_CS_PIN);
	modbus.config(const_cast<uint8_t*>(macAddress)); // cast away constness to suppress warning
	if(Ethernet.hardwareStatus() == EthernetNoHardware) {
		Serial.println(F("Could not detect any hardware"));
		flagError(ETHERNET_HARDWARE_FAIL);
	}
	if(Ethernet.linkStatus() != LinkON) {
		Serial.println(F("Could not create link"));
		flagError(ETHERNET_LINK_FAIL);
	}
	Serial.print(F("Listening on: "));
	Serial.print(Ethernet.localIP());
	Serial.print(':');
	Serial.println(MODBUSIP_PORT);

	// configure modbus
	prepIregs(lastUpdateHighAddr, 2);
	prepIregs(pressureTransducerAddr, numPressureTransducers);
	prepIregs(loadCellAddr, numLoadcells);
	prepIregs(thermoCoupleAddr, numThermoCouples);
	prepCoils(errorAddr, UNKNOWN_FAIL + 1);
}
uint16_t timeWords[2];
void loop() {
	modbus.task();

	// update stuff
	updatePressureTransducers();
	writeIregs(pressureTransducerAddr, pressureTransducers, numPressureTransducers);
	updateLoadcells();
	writeIregs(loadCellAddr, loadCells, numLoadcells);
	updateThermoCouples();
	writeIregs(thermoCoupleAddr, thermoCouples, numThermoCouples);

	// update the last known reading
	uint32_t currentTime = millis();
	// flipped order for big endian
	timeWords[1] = currentTime & 0x0000FFFF;
	timeWords[0] = currentTime & 0xFFFF0000;
	writeIregs(lastUpdateHighAddr, timeWords, 2);
}
