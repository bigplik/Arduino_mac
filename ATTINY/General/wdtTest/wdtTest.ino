//here to make this WDT work on Attiny13A
//I did comment //#define ENABLE_MILLIS in core_settings.h
//of microcore library,
//to work with other chips, uncomment this and anable millis()

#define LOW_BATTERY analogRead(A1)<500

boolean led = true;

ISR(WDT_vect) {
   // Toggle Port B pin 4 output state
   if(LOW_BATTERY){
    led = 0;
    WDTCR |= (0<<WDTIE);
    cli();
   }
   else{
    led=20;
   }
}

void setup() {

  // put your setup code here, to run once:
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
//    DDRB = 1<<DDB0;
//    DDRB = 1<<DDB1;

   // prescale timer to 0.5s
   WDTCR |= (1<<WDP3);//(1<<WDP2) | (1<<WDP1) | (1<<WDP0);// | (1<<WDP0);
   //WDP3 WDP2 WDP1 WDP0

   // Enable watchdog timer interrupts
   WDTCR |= (1<<WDTIE);

   sei(); // Enable global interrupts 
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(1,led);
}
