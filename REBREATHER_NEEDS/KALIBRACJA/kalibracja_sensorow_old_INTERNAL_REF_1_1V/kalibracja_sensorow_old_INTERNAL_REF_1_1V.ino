int firstValue1 = 0;
float M=41.70;
float WK1;
float PPO2;
float m1;
float SmV;

void setup(){
  
  Serial.begin(9600);
  
  //  analogReference(INTERNAL);


   for(int j = 0 ; j < 10 ; j++)

{

firstValue1 += analogRead(A0);                          //sumowanie kolejnych pomiarów
//firstValue2 += analogRead(A1);
//firstValue3 += analogRead(A2);
delay(100);                                               //opóźnienie

}

firstValue1 /=10;                                                            //liczenie wartości średniej
//firstValue2 /=10;                                                            //i zapamiętanie jej
//firstValue3 /=10;


SmV = (firstValue1/5.0); //dane przeliczone do miliVolt dla S1
//S2mV = (firstValue2/4.95); //dla S2
//S3mV = (firstValue3/4.95); //dla S3
    //wartość M, współczynnik nachylenia dla prostej idealnej
                //dla sensora o 13mV
m1=(SmV/0.21);   //m dla sensora 1
//m2=(S2mV/0.21);   //dla 2
//m3=(S3mV/0.21);
WK1 = M/m1;
//WK2 = M/m2;
//WK3 = M/m3;


  
}

void loop(){
  
    //float sensor = analogRead(A5) * (5.0/1023.0);
 
  //analogReference(INTERNAL);
  
  float sensorValue = analogRead(A0)* (1.1/1023.0);
  //int sensorValue2 = analogRead(A1);
  //int sensorValue3 = analogRead(A2);
  
  //analogReference(DEFAULT);
  float SmVact = (analogRead(A0)/4.92);
  
//PPO2 = (sensorValue * (4.9 / 1023.0));
//PPO2 = (SmVact * 2.09)/100;                   //znaleźć mnożnik!!!!!!
PPO2 = (SmVact * (0.21/SmV));
//PPO22 = (sensorValue2 * (5.0 / 1023.0)*WK2);
//PPO23 = (sensorValue3 * (5.0 / 1023.0)*WK3);
 Serial.print("first value: ");
 Serial.println(firstValue1);
 Serial.print("analog A0: ");
 Serial.println(sensorValue);
 Serial.print("m1: ");
 Serial.println(m1);
 Serial.print("first SmV: ");
 Serial.println(SmV);
 Serial.print("M: ");
 Serial.println(M);
 Serial.print("WK: ");
 Serial.println(WK1);
 Serial.print("PPO2: ");
 Serial.println(PPO2);
 
 Serial.print("SmV actual: ");
 Serial.println(SmVact);
 Serial.println("   ");
  delay(2000);
  
}
