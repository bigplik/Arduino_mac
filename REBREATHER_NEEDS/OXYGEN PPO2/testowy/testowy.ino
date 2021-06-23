/*
  Switch statement  with serial input

 Demonstrates the use of a switch statement.  The switch
 statement allows you to choose from among a set of discrete values
 of a variable.  It's like a series of if statements.

 To see this sketch in action, open the Serial monitor and send any character.
 The characters a, b, c, d, and e, will turn on LEDs.  Any other character will turn
 the LEDs off.

 The circuit:
 * 5 LEDs attached to digital pins 2 through 6 through 220-ohm resistors

 created 1 Jul 2009
 by Tom Igoe

This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/SwitchCase2
 */
int firstValue;
int inByte;
float SmV;
float SmVact;
float PPO2;
float calibrationValue;
float factorPPO2;
float adjPPO2;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  
    pinMode(13, OUTPUT);
          for(int j = 0 ; j < 10 ; j++)

{

firstValue += analogRead(A0);                          //sumowanie kolejnych pomiarów
//firstValue2 += analogRead(A6);
//firstValue3 += analogRead(A7);
delay(100);                                               //opóźnienie

}

firstValue /=10;                                                            //liczenie wartości średniej
//firstValue2 /=10;                                                            //i zapamiętanie jej
//firstValue3 /=10;


SmV = (firstValue/4.9); //dane przeliczone do miliVolt dla S1
//S2mV = (firstValue2/4.9); //dla S2
//S3mV = (firstValue3/4.9); //dla S3
}

void loop() {

  SmVact = (analogRead(A0)/4.9);
  //  SmVact2 = (analogRead(A6)/4.9);
  //    SmVact3 = (analogRead(A7)/4.9);
          PPO2 = (SmVact * (0.21/SmV));   
  
   // int sensorValue = analogRead(A0);
  
    int bazowa = Serial.read();
    
    if(Serial.read() == 'a'){
      
      inByte++;
      
    }
    
    if(inByte > 2){
      
      inByte = 1;
      
    }
    

    
    switch (inByte) {
      case 1:
        Serial.println("air calibration");
          for(int j = 0 ; j < 10 ; j++){
            calibrationValue += PPO2;                          //sumowanie kolejnych pomiarów
            delay(1000);                                           //opóźnienie
        }
        calibrationValue /=10;                                                            //liczenie wartości średnie
        factorPPO2 = 0.99 / calibrationValue;
        Serial.println(calibrationValue);
        Serial.println(inByte);
        inByte++;
        break;
      case 2:
        Serial.println("O2 calibration");
        Serial.print("calibration value ");
        Serial.println(calibrationValue);
        Serial.print("factor PPO2 ");
        Serial.println(factorPPO2);
        Serial.print("SmV ");
        Serial.println(SmV);
        Serial.print("SmVact ");
        Serial.println(SmVact);
        Serial.print("PPO2 ");
        Serial.println(PPO2);
        Serial.print("Adjusted PPO2 ");
        Serial.println(adjPPO2);
        Serial.println("----------------");
        Serial.println(inByte);     
        break;
    }
    
    delay(2000);

  adjPPO2 = PPO2 * factorPPO2;
}

