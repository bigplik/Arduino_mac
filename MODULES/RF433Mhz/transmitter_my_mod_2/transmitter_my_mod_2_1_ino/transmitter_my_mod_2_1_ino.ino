#include <Wire.h>
#include <VirtualWire.h>
String calosc, wilg, S2, temp, wilg1, S22;
char Msg[27];

int firstnumber;
int secondnumber;
float voltage;

void setup()
{
   vw_setup(2000);
  
  wilg = String("W: ");
  S2 = String ("S2: ");
  temp = String ("S3: " );
  Serial.begin(9600);
  delay(5000);
  Serial.println("Stacja Meteo by ElektroMaras"); 
  
  Wire.begin();

}

void loop()
{
  
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
 
 
  if(voltage <= 0.99){firstnumber = 0;}
  else if(voltage >= 1.00){firstnumber = 1;}
 // else if(voltage >= 2.00){firstnumber = 2;}
  delay(50);
  if(firstnumber == 0){secondnumber = voltage*100;}
  else if(firstnumber == 1){secondnumber = (voltage-1.00)*100;}
 // else if(firstnumber == 2){secondnumber = 0;}
  
  int a = firstnumber;
String wilg1 = wilg + a;
Serial.println (wilg1);

    int b = secondnumber;
String S22 = S2 + b;
Serial.println(S22);

String calosc = wilg1 + S22;
   Serial.println(calosc);

   
    calosc.toCharArray(Msg,(calosc.length()+1));
    for (int i = 0; i <= calosc.length(); i++) {
    //Serial.print(Msg[i]);
   
   
    vw_send((uint8_t *)Msg, strlen(Msg));
    vw_wait_tx(); 
    
    //Serial.println("poszlo");         
  }
    Serial.println(); // Start a new line.
    delay(1000);
}
