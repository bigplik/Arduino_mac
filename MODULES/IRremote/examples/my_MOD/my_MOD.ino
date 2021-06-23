#include <IRremote.h>

int RECV_PIN = 11; //define input pin on Arduino

IRrecv irrecv(RECV_PIN);

decode_results results;

int on = 0;

void setup()

{

Serial.begin(9600);

irrecv.enableIRIn(); // Start the receiver
pinMode(13,OUTPUT);

}

void loop() {

if (irrecv.decode(&results)) {

Serial.println(results.value);

irrecv.resume(); // Receive the next value

}

wartosci();
delay(1);

} 

void wartosci() {
  if(results.value == 16580863) { digitalWrite(13, on ? HIGH : LOW); }
  else if(results.value == 16623703) { Serial.println("OK"); }
  on = !on;
}


