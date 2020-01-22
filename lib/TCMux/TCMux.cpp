#include "TCMux.h"
#include <Arduino.h>

TCMux::TCMux(uint8_t pinEn, 
		uint8_t pinA0, 
		uint8_t pinA1,
		uint8_t pinA2,
		uint8_t pinSo,
		uint8_t pinSc,
		uint8_t pinCs) {
			
	this->pinEn = pinEn;
	this->pinA0 = pinA0;
	this->pinA1 = pinA1;
	this->pinA2 = pinA2;
	this->pinSo = pinSo,
	this->pinSc = pinSc;
	this->pinCs = pinCs;
}
uint16_t TCMux::readTC(uint8_t index, uint8_t &err, uint16_t &internalTemp) {
	if(!setup) {
		setupPins();
		setup = true;
	}
	if(readComplete || index != readingIndex) {
		muxPins(index);
		readingIndex = index;
		readComplete = false;
		// store a reading in the Max31855
		// datasheet: https://datasheets.maximintegrated.com/en/ds/MAX31855.pdf
		digitalWrite(pinCs, LOW); // stop last conversion
		delayMicroseconds(1); // data sheet specifies 100ns
		digitalWrite(pinCs, HIGH); //restart conversion		
		readingStartTime = millis();
	}
	// ensure that at least RESPONSE_TIME ms has elapsed between reads
	// alternatively if we already have a valid read, just return the cached value
	if(!ready()) {
		internalTemp = cachedInternal;
		err = STALE_VALUE;
		return cachedReadings[readingIndex];
	}

	digitalWrite(pinCs, LOW);
	delayMicroseconds(1);

	int16_t rawReading = 0;
	int16_t rawInternal = 0;
	uint16_t mask = 0;
	// parse bytes
	for(int8_t i = 31; i >= 0; i--) {
		digitalWrite(pinSc, HIGH);
		delayMicroseconds(1);
		
		/* 
		top 14 bits are thermocouple reading
		bit 31: sign
		bit 30: MSB = 2^10
		bit 18: LSB	= 2^-2
		*/	
		if(i <= 31 && i >= 18) {
			mask = 1 << (i - 18);
			if (digitalRead(pinSo)) {
				if(i == 31) {
					rawReading += 0b11 << 14;
				}
				rawReading += mask;
			}
		}
		// bit 17 reserved
		// bit 16 for sensor fault
		if (i == 16) {
			err = digitalRead(pinSo) * -1;
		}

		/*
		next 12 bits are internal temp of the chip
		bit 15 sign
		bit 14 MSB = 2^6
		bit 4 LSB = 2^-4
		*/
		if (i <= 15 && i >= 4) {
			mask = 1 << (i-4);
			if(digitalRead(pinSo)) {
				if(i == 15) {
					rawInternal += 0b1111 << 12;
				}
				rawInternal += mask;
			}
		}
		// bit 3 reserved
		// bit 2 high if shorted HIGH
		if(i == 2 && digitalRead(pinSo)) {
			err = FAULT_SHORT_HIGH;
		} 
		// bit 1 set if shorted GND
		if(i == 1 && digitalRead(pinSo)) {
			err = FAULT_SHORT_GND;
		} 
		// bit 0 set if open
		if(i == 0 && digitalRead(pinSo)) {
			err = FAULT_SHORT_OPEN;
		} 

		digitalWrite(pinSc, LOW);
		delayMicroseconds(1);
	}
	if(err) {
		return 0;
	}
	internalTemp = rawInternal;
	cachedInternal = rawInternal;
	cachedReadings[readingIndex] = rawReading;
	readComplete = true;
	return rawReading;
}

uint16_t TCMux::readTC(uint8_t index, uint8_t &err) {
	uint16_t meh;
	return readTC(index, err, meh);
}

void TCMux::setupPins() {
	pinMode(pinEn, OUTPUT);     
	pinMode(pinA0, OUTPUT);    
	pinMode(pinA1, OUTPUT);    
	pinMode(pinA2, OUTPUT);    
	pinMode(pinSo, INPUT);    
	pinMode(pinCs, OUTPUT);    
	pinMode(pinSc, OUTPUT);    
	
	digitalWrite(pinEn, HIGH);   // enable on
	digitalWrite(pinA0, LOW); // low, low, low = channel 1
	digitalWrite(pinA1, LOW); 
	digitalWrite(pinA2, LOW); 
	digitalWrite(pinSc, LOW); //put clock in low
}

void TCMux::muxPins(uint8_t index) {
	digitalWrite(pinA0, index & 1);
	digitalWrite(pinA1, (index & 0b10) >> 1);
	digitalWrite(pinA1, (index & 0b100) >> 2);
}

uint8_t TCMux::samplingSensor() {
	return readingIndex;
}

bool TCMux::ready() {
	return readComplete || millis() > readingStartTime + RESPONSE_TIME;
}