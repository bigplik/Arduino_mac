int counter = 0;
int counter2 = 0;
int pin = 6;

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
  Serial.print("nie dupa");
  Serial.print(counter2);
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(2000);
  
  if(pin == HIGH){
    
    
    
  }

}
