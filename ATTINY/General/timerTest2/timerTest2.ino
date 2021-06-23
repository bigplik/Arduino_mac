
boolean led = 0;
byte burn = 0;

ISR(TIM0_OVF_vect) {
   // Toggle Port B pin 4 output state
   burn+=25;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);

  cli();

  //set prescaler 1024
  //bitSet(TCCR0B, CS02);
  //bitSet(TCCR0B, CS00);
  TCCR0A = 0b00000001;
  //set prescaler
  TCCR0B = 0b00000101;
  
  //TCNT0 = 1024;

  //bitSet(TIMSK0, TOIE0);
  TIMSK0 = 0b00000010;
  TIFR0  = 0b00000010;
  SREG = 0b10000000;
  //sei();
}

void loop() {
  // put your main code here, to run repeatedly:
//  if(led) burn = 25;
//  else{ burn = 0;}
  if(burn>255) burn = 0;
  analogWrite(0,burn);
  //digitalWrite(1,0);
}
