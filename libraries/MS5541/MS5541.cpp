#include <SPI.h>
#include "MS5541.h"

MS5541::MS5541() {
	SPI.begin();
  	SPI.setBitOrder(MSBFIRST);
  	SPI.setClockDivider(SPI_CLOCK_DIV32); //divide 16 MHz to communicate on 500 kHz
  	pinMode(9, OUTPUT);
  	getCalibrationWord();
}

void MS5541::resetSensor() {
	SPI.setDataMode(SPI_MODE0); 
	SPI.transfer(0x15);
	SPI.transfer(0x55);
	SPI.transfer(0x40);
}

void MS5541::update() {
	TCCR1B = (TCCR1B & 0xF8) | 1 ; //generates the MCKL signal
	analogWrite(9, 128); 

	//Pressure:
	resetSensor();
	SPI.transfer(0x0F); //send first byte of command to get pressure value
	SPI.transfer(0x40); //send second byte of command to get pressure value
	delay(35); //wait for conversion end
	SPI.setDataMode(SPI_MODE1); //change mode in order to listen
	presMSB = SPI.transfer(0x00); //send dummy byte to read first byte of value
	presMSB = presMSB << 8; //shift first byte
	presLSB = SPI.transfer(0x00); //send dummy byte to read second byte of value
	D1 = presMSB | presLSB; //combine first and second byte of value
 
	//Temperature
	resetSensor();
	SPI.transfer(0x0F); //send first byte of command to get temperature value
	SPI.transfer(0x20); //send second byte of command to get temperature value
	delay(35); //wait for conversion end
	SPI.setDataMode(SPI_MODE1); //change mode in order to listen
	tempMSB = SPI.transfer(0x00); //send dummy byte to read first byte of value
	tempMSB = tempMSB << 8; //shift first byte
	tempLSB = SPI.transfer(0x00); //send dummy byte to read second byte of value
	D2 = tempMSB | tempLSB; //combine first and second byte of value

	//calculate temp according to datasheet
	dT = D2 - UT1;
	if (dT < 0) {
		dT2 = dT - (dT/128*dT/128)/2;
	}
	else {
		dT2 = dT - (dT/128*dT/128)/8;
	}

	TEMP = (200 + dT*(C6+100)/pow(2,11))/10;
	TEMPC = (200 + dT2*(C6+100)/pow(2,11))/10;

	//calculate pressure according to datasheet
	OFF = C2 + ((C4-250)*dT)/pow(2,12) + 10000;
	SENS = C1/2 + ((C3+200)*dT)/pow(2,13) + 3000;
	P = (SENS * (D1-OFF))/pow(2,11) + 1000;
}

float MS5541::getPressureMBar() {
	return P;
}

float MS5541::getPressureBar() {
	return P/1000.0;
}


float MS5541::getTemperatureC() {
	return TEMP;
}

float MS5541::get2ndTemperatureC() {
	return TEMPC;
}

float MS5541::getTemperatureF() {
	return (TEMP*1.8)+32.0;
}

float MS5541::get2ndTemperatureF() {
	return (TEMPC*1.8)+32.0;
}

void MS5541::getCalibrationWord() {
	TCCR1B = (TCCR1B & 0xF8) | 1 ; //generates the MCKL signal
	analogWrite(9, 128) ; 
	
	resetSensor();
	SPI.transfer(0x1D); //send first byte of command to get calibration word 1
	SPI.transfer(0x50); //send second byte of command to get calibration word 1
	SPI.setDataMode(SPI_MODE1); //change mode in order to listen
	result1 = SPI.transfer(0x00); //send dummy byte to read first byte of word
	result1 = result1 << 8; //shift returned byte 
	inbyte1 = SPI.transfer(0x00); //send dummy byte to read second byte of word
	result1 =  result1 | inbyte1; //combine first and second byte of word	

	resetSensor();
	SPI.transfer(0x1D);
	SPI.transfer(0x60);
	SPI.setDataMode(SPI_MODE1); 
	result2 = SPI.transfer(0x00);
	result2 = result2 <<8;
	inbyte2 = SPI.transfer(0x00);
	result2 = result2 | inbyte2;

	resetSensor();
	SPI.transfer(0x1D);
	SPI.transfer(0x90); 
	SPI.setDataMode(SPI_MODE1); 
	result3 = SPI.transfer(0x00);
	result3 = result3 <<8;
	inbyte3 = SPI.transfer(0x00);
	result3 = result3 | inbyte3;

	resetSensor();
	SPI.transfer(0x1D);
	SPI.transfer(0xA0);
	SPI.setDataMode(SPI_MODE1); 
	result4 = SPI.transfer(0x00);
	result4 = result4 <<8;
	inbyte4 = SPI.transfer(0x00);
	result4 = result4 | inbyte4;

	C1 = result1 >> 3 & 0x1FFF;
	C2 = ((result1 & 0x07) << 10) | ((result2 >> 6) & 0x03FF);
	C3 = (result3 >> 6) & 0x03FF;
	C4 = (result4 >> 7) & 0x07FF;
	C5 = ((result2 & 0x003F) << 6) | (result3 & 0x003F);
	C6 = result4 & 0x007F;
	UT1 = 8*C5 + 10000;
}