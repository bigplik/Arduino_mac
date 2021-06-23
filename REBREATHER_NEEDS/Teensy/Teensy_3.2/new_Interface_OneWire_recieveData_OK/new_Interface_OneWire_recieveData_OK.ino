#include <DataCoder.h>
#include <VirtualWire.h>
#include <SimpleTimer.h>
#include <SPI.h>
#include "MS55xx.h"
MS55xx PressSensor;
float airPressure;
float waterPressure;

const int transmit_pin = 2;
const int led_pin = 13;
const int baudRate = 1000;

float mVsens1 = 10.2;

float temp = 0;
float hum = 0;
float bat = 0;

SimpleTimer timer;

void sendData(){
  PressSensor.update();
  temp=PressSensor.get2ndTemperatureC();
  bat = analogRead(A0)*(3.3/1023.0);
  
  float outArray[RF_DATA_ARRAY_SIZE];//the number fo elements that 
  //will be transmitted. I use four elements. 
  //RF_DATA_ARRAY_SIZE can be changed if need be inside DataCoder.h
  
  outArray[0] = mVsens1;
  outArray[1] = temp;
  outArray[2] = hum;
  outArray[3] = bat;
  
  union RFData outDataSeq;
  EncodeRFData(outArray, outDataSeq); 
  TransmitRFData(outDataSeq);  
  mVsens1++;
  hum++;
}

void setup()
{  
    SetupRFDataTxnLink(transmit_pin, baudRate);
  
    PressSensor.setPressureSensorType('MS5535');
    //start arduino before diving
    //otherwise a 1.0 bar is used as surface pressure
    PressSensor.update();
    airPressure = PressSensor.getPressureBar();
    if (airPressure > 1.2) {
      airPressure = 1.0;
    }
    timer.setInterval(10000L, sendData);
}

void loop()
{
  timer.run();
}


