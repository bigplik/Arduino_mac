/******************************************************************
* MS5541 Pressure Sensor calwords readout
* This library read your MS5541 sensor using SPI protocol
* Please respect pin wiring:
* MOSI: pin 11 or pin 7 on sensor
* MISO: pin 12 or pin 8 on sensor
* SCK: pin 13 or pin 1 on sensor
* MCLK: pin 9 or pin 6 on sensor
 
* This library is developed using part of code from another author (called godo on arduino forum), please visit arduino forum for that:
* http://forum.arduino.cc/index.php?topic=67188.0
*
* Author fro original code:
* created August 2011
* by SMStrauch based on application note AN510 from www.intersema.ch (http://www.meas-spec.com/downloads/Using_SPI_Protocol_with_Pressure_Sensor_Modules.pdf), 
* and with help of robtillaart and ulrichard. Thanks!
*

*
*  Lib version history
*    1.0 first lib created. 
*
*This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
<http://www.gnu.org/licenses/>
*  
******************************************************************/

#ifndef MS5541_h
#define MS5541_h

#if ARDUINO > 22
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class MS5541 {
public:
MS5541();

float getPressureMBar();
float getPressureBar();
float getTemperatureC();
float get2ndTemperatureC();
float getTemperatureF();
float get2ndTemperatureF();

void update();

private:
void resetSensor();
void getCalibrationWord();

long C1;
long C2;
long C3;
long C4;
long C5;
long C6;

unsigned int presMSB;
unsigned int presLSB;
unsigned int D1;

unsigned int tempMSB;
unsigned int tempLSB;
unsigned int D2;

long UT1;
long dT;
long dT2;
float TEMP;
float TEMPC;
long OFF;
long SENS;
long P;

unsigned int result1;
unsigned int inbyte1;
unsigned int result2;
byte inbyte2;
unsigned int result3;
byte inbyte3;
unsigned int result4;
byte inbyte4;

};

#endif



