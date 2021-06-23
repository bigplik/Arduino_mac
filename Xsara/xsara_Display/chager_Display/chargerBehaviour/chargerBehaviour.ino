
int ignitionTrigger = 6;
int mosfetPin = 3;
int timeCounter = 0;
int backUpChargeCounter = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ignitionTrigger,INPUT);
  pinMode(mosfetPin,OUTPUT);
  
}

void loop() {
  
  //if ignition is on
  if(digitalRead(ignitionTrigger) == HIGH) {
    //turn on mosfet
    digitalWrite(mosfetPin,1);
    timeCounter = 0;
    backUpChargeCounter = 0;
  }
  //if ignition is off
  else if(digitalRead(ignitionTrigger) == LOW) {

    //charging when counter get 5.5hour
    if(timeCounter >= 19800) {

      //stop charging when back up charge counter get half an hour
      if(backUpChargeCounter >= 1800) {
        digitalWrite(mosfetPin,0);
        timeCounter = 0;
      }

      else{
      //charging
      digitalWrite(mosfetPin,1);
      backUpChargeCounter++;
      delay(1000);
      }
      
    }

    else{
    //turn mosfet off
    digitalWrite(mosfetPin,0);
    timeCounter++; //waiting 5.5hour for back up charging
    backUpChargeCounter = 0;
    delay(1000);
    }
    
  }
}
