/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */

int firstnumber;
int secondnumber;
float voltage;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  
  if(voltage <= 0.99){
    
    firstnumber = 0;
    
  }else if(voltage >= 1.00){
    
    firstnumber = 1;
    
  }
  
  delay(50);
  
  if(firstnumber == 0){
    
    secondnumber = voltage*100;
    
  }else if(firstnumber == 1){
    
    secondnumber = (voltage-1.00)*100;
    
  }
  
  // print out the value you read:
  Serial.println(voltage);
  Serial.println(firstnumber);
  Serial.println(secondnumber);
  delay(1000);
}
