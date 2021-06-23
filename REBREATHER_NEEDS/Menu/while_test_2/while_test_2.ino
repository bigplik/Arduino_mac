int counter = 0;
int counter2 = 0;
int pin = 2;
int buttonState = 0;

void setup() {
  
  Serial.begin(9600);
  pinMode(pin, INPUT);
  // put your setup code here, to run once:
  
  while(counter >= 0 & counter <10){
    Serial.print("dupa");
    Serial.println(counter);
    counter ++;
    delay(1000);

  }
  
  pinMode(13, OUTPUT);
  
}

void loop() {
  
  buttonState = digitalRead(pin);
    

    if(buttonState == HIGH){
    counter2 = counter2 +1;
    }
    
    
  
  /*
  if(millis()>3000){
  delay(2000);
  if(buttonState == HIGH){
    
    counter2 = counter2 +10;
    
  }
  

}
  */ 
  
  Serial.print("nie dupa");
  Serial.println(counter2);
  delay(500);

  


}
