#include <Modbus.h>
#include <ModbusSerial.h>
#include "config.h"
#include "shared.h"
#include "errorTypes.h"

ModbusSerial modbus;
void setup() {
	prepPins();
	modbus.config(&Serial, 115200, SERIAL_8N1, TX_PIN);
	modbus.setSlaveId(deviceId);
	
	prepIregs(lastUpdateHighAddr, 2);
	prepIregs(pressureTransducerAddr, numPressureTransducers);
	prepIregs(loadCellAddr, numLoadcells);
	prepIregs(thermoCoupleAddr, numThermoCouples);
	prepCoils(errorAddr, UNKNOWN_FAIL + 1);
}
uint16_t timeWords[2];
uint32_t lastUpdate = 0;
void loop() {
	// update the last known reading
	uint32_t currentTime = millis();
	// flipped order for big endian
	timeWords[1] = currentTime & 0x0000FFFF;
	timeWords[0] = currentTime & 0xFFFF0000;

	if(currentTime > lastUpdate + updateMs) {
		// update stuff
		updatePressureTransducers();
		writeIregs(pressureTransducerAddr, pressureTransducers, numPressureTransducers);
		updateLoadcells();
		writeIregs(loadCellAddr, loadCells, numLoadcells);
		updateThermoCouples();
		writeIregs(thermoCoupleAddr, thermoCouples, numThermoCouples);

		writeIregs(lastUpdateHighAddr, timeWords, 2);
		lastUpdate = currentTime;
	}
	modbus.task();
}
