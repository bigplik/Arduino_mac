int led = 1;
int value = 0;

ISR(TIM0_OVF_vect) {      // interrupt overflow routine
  // preload timer
  value++;
}


void setup() {
  // put your setup code here, to run once:
  pinMode(0,OUTPUT);

  cli();

  //set prescaler 1024
  //bitSet(TCCR0B, CS02);
  //bitSet(TCCR0B, CS00);
  TCCR0A = 0b00000000;
  //set prescaler
  TCCR0B = 0b00000101;
  
  TCNT0 = 1024;

  //bitSet(TIMSK0, TOIE0);
  TIMSK0 = 0b00000010;
  SREG = 0b10000000;
  

}

void loop() {
  // put your main code here, to run repeatedly:
if(value >= 5){
  analog();
  value=0;
}

}

void analog() {
  if(analogRead(A1)<440)analogWrite(1,10);
  else{
    digitalWrite(0,1);
    digitalWrite(1,0);
  }
}

