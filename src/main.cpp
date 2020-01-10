#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoModbus.h>
#include "config.h"
#include "shared.h"
#include "errorTypes.h"

EthernetServer server(PORT);
ModbusTCPServer modbus;

void setup() {
	prep();
	Serial.begin(115200);
	while(!Serial);

	Serial.println(F("Initializing DAQ Slave"));
	
	// initialize ethernet / networking
	Serial.println(F("Setting up ethernet...."));
	Ethernet.init(ETHERNET_CS_PIN);
	Ethernet.begin(macAddress);
	if(Ethernet.hardwareStatus() == EthernetNoHardware) {
		Serial.println(F("Could not detect any hardware"));
		flagError(ETHERNET_HARDWARE_FAIL);
	}
	if(Ethernet.linkStatus() != LinkON) {
		Serial.println(F("Could not create link"));
		flagError(ETHERNET_LINK_FAIL);
	}
	server.begin();
	Serial.print(F("Listening on: "));
	Serial.print(Ethernet.localIP());
	Serial.print(':');
	Serial.println(PORT);

	// initialize Modbus
	if(!modbus.begin()) {
		Serial.println(F("Could not start modbus server"));
		flagError(MODBUS_SETUP_FAIL);
	}
	modbus.configureInputRegisters(lastUpdateLowAddr, 2);
	modbus.configureInputRegisters(pressureTransducerAddr, numPressureTransducers);
	modbus.configureInputRegisters(loadCellAddr, numLoadcells);
	modbus.configureInputRegisters(thermoCoupleAddr, numThermoCouples);
}
uint16_t timeWords[2];
void loop() {
	EthernetClient client = server.available();
	if(client) {
		modbus.accept(client);
		long connectTime = millis();
		while(client.connected()) {
			modbus.poll();
			if(millis() > connectTime + MAX_TIMEOUT) {
				Serial.println(F("Connection timeout, force closing"));
				flagError(CONNECTION_TIMEOUT);
				client.stop();
				break;
			}
		}
	}

	// update stuff
	updatePressureTransducers();
	modbus.writeInputRegisters(pressureTransducerAddr, pressureTransducers, numPressureTransducers);
	updateLoadcells();
	modbus.writeInputRegisters(loadCellAddr, loadCells, numLoadcells);
	updateThermoCouples();
	modbus.writeInputRegisters(thermoCoupleAddr, thermoCouples, numThermoCouples);

	// update the last known reading
	uint32_t currentTime = millis();
	timeWords[0] = currentTime & 0x000000FF;
	timeWords[1] = currentTime & 0x0000FF00;
}
// for stuff that is guaranteed to work
void prep() {
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(MUX_ENABLE_PIN, OUTPUT);
	pinMode(THERMOCOUPLE_A0, OUTPUT);
	pinMode(THERMOCOUPLE_A1, OUTPUT);
	pinMode(THERMOCOUPLE_A2, OUTPUT);
	digitalWrite(MUX_ENABLE_PIN, HIGH);
}