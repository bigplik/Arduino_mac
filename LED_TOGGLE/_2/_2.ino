// We name pin D0 as led
int led = 11; 

// This routine runs only once upon reset
void setup() 
{
  // Initialize D0 pin as an output
  pinMode(led, OUTPUT);
}

// This routine loops forever 
void loop() 
{
  digitalWrite(led, !digitalRead(led));   // Toggle led
  delay(5000);              
}
