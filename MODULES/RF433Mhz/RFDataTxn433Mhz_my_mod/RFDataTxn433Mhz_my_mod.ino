#include <DataCoder.h>
#include <VirtualWire.h>

const int transmit_pin = 12;
const int led_pin = 13;
const int baudRate = 1000;
//float voltage = 0.00;

void setup()
{ 
  Serial.begin(9600);
  pinMode(led_pin,OUTPUT);
  
  SetupRFDataTxnLink(transmit_pin, baudRate);

}

void loop()
{
  
 /* 
 for(int j = 0 ; j < 11 ; j++){

voltage += analogRead(A0);                          //sumowanie kolejnych pomiarów
delay(1000); 
 }//opóźnienie
voltage /=10;
*/
int sensor = analogRead(A0);
  float voltage = sensor*(5.0/1023.0);
  Serial.print(voltage);
  
  
  int sensor2 = analogRead(A1);
  float voltage2 = sensor2*(5.0/1023.0);
  Serial.print(voltage);
  
  
  int sensor3 = analogRead(A2);
  float voltage3 = sensor3*(5.0/1023.0);
  Serial.print(voltage);
  delay(500);
  
  float outArray[RF_DATA_ARRAY_SIZE];//the number fo elements that 
  //will be transmitted. I use four elements. 
  //RF_DATA_ARRAY_SIZE can be changed if need be inside DataCoder.h
  
  outArray[0] = voltage*1;
  outArray[1] = voltage2;
  outArray[2] = voltage3;
  outArray[3] = 10.31;
  
  union RFData outDataSeq;
 
  EncodeRFData(outArray, outDataSeq); 
  
  TransmitRFData(outDataSeq);  
  
  digitalWrite(led_pin, HIGH);
  
  delay(100);
  
  digitalWrite(led_pin,LOW);
  
  delay(500);
  
  
  
}


