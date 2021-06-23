//BY PJW

#include <DataCoder.h>
#include <VirtualWire.h>
#include <idDHT11.h>
#include "LowPower.h"

int idDHT11pin = 2; //Digital pin for comunications
int idDHT11intNumber = 0; //interrupt number (must be the one that use the previus defined pin (see table above)

//declaration
void dht11_wrapper(); // must be declared before the lib initialization

// Lib instantiate
idDHT11 DHT11(idDHT11pin,idDHT11intNumber,dht11_wrapper);

const int transmit_pin = 12;
const int led_pin = 13;
const int baudRate = 1000;

void setup()
{
  pinMode(led_pin,OUTPUT);
  pinMode(10,OUTPUT);
  SetupRFDataTxnLink(transmit_pin, baudRate);

}

void dht11_wrapper() {
  DHT11.isrCallback();
}

void loop()
{
  delay(50);
  digitalWrite(10,HIGH);
  delay(50);
  
  int result = DHT11.acquireAndWait();
  
  float outArray[RF_DATA_ARRAY_SIZE];//the number fo elements that 
  //will be transmitted. I use four elements. 
  //RF_DATA_ARRAY_SIZE can be changed if need be inside DataCoder.h
  
 for(int a=0;a<2;a++){
  outArray[0] = DHT11.getHumidity();
  outArray[1] = DHT11.getCelsius();
  outArray[2] = DHT11.getDewPointSlow();
  outArray[3] = analogRead(A2)*(5.0/1023.0);
  
  union RFData outDataSeq;
 
  EncodeRFData(outArray, outDataSeq); 
  
  TransmitRFData(outDataSeq);  
  
  digitalWrite(led_pin, HIGH);
  
  delay(100);
  
  digitalWrite(led_pin,LOW);
  
  delay(500);
  digitalWrite(10,LOW);
  delay(50);
}
  
    for(int i=0;i<75;i++){
  LowPower.idle(SLEEP_4S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
                SPI_OFF, USART0_OFF, TWI_OFF);
  }
  
}


