
#define resetSignal 4

#define F_CPU 8000000  // This is used by delay.h library

#include <stdlib.h>
#include <avr/io.h>        // Adds useful constants
#include <util/delay.h>    // Adds delay_ms and delay_us functions
  
#include <avr/sleep.h>
#include <avr/interrupt.h>

// Routines to set and claer bits (used in the sleep code)
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// *********** Define I/O Pins **********************
// LED output pins:
const int redled = 0;         // Red LED attached to here (0, IC pin 5)
const int greenled = 1;       // Green LED/buzzer/Switch attached to here (1, IC pin 6)
// MOSFET Driver output
byte counter = 0;
int PPO2 = 0;

// Variables for the Sleep/power down modes:
volatile boolean f_wdt = 1;

// the setup routine runs once when you press reset:
void setup()  { 
  pinMode(resetSignal,OUTPUT);
  digitalWrite(resetSignal,LOW);
  _delay_ms(500);
  // Set up FAST PWM 
  TCCR0A = 2<<COM0A0 | 2<<COM0B0 | 3<<WGM00;  // Set control register A for Timer 0
  TCCR0B = 0<<WGM02 | 1<<CS00;  // Set control register B for Timer 0
  TCCR1 = 0<<PWM1A | 0<<COM1A0 | 1<<CS10;  // Set control register for Timer 1
  GTCCR = 1<<PWM1B | 2<<COM1B0;  // General control register for Timer 1
  
  // Set up IO pins
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);        // First want to read the switch
  pinMode(3,INPUT);

  
  for(int a=0; a<10; a++){
    digitalWrite(1,digitalRead(1)^1);
    _delay_ms(200);
  }   
  for(int b=0; b<10; b++){
    digitalWrite(0,digitalRead(0)^1);
    _delay_ms(200);
  }  
// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
  setup_watchdog(8); // approximately ? seconds sleep
  
} 

// the loop routine runs over and over again forever:
void loop()  { 
  
  digitalWrite(resetSignal,LOW);
  PPO2 = analogRead(3); //analogy to values of PPO2
  if(counter < 10){
      if(PPO2 < 512){ //if low PPO2 go to the "small" loop
        
          counter++;
          //small loop
          if (f_wdt==1) {  // wait for timed out watchdog / flag is set when a watchdog timeout occurs
            f_wdt=0;       // reset flag
            
            digitalWrite(redled, HIGH);      // YELLOW ON 
            _delay_ms(500);  // Switch the LED on for 0.5 Seconds
            digitalWrite(redled, LOW);  // YELLOW OFF 
            pinMode(greenled,INPUT);
            
            system_sleep();  // Send the unit to sleep
            
            // Set the ports to be output again 
            pinMode(redled, OUTPUT);
            pinMode(greenled, OUTPUT);        // First want to read the switch
          }
       }
       else if(PPO2 > 512){ 
            // in analogy, device would read PPO2 and work with no sleep_mode
            //here as PPO2 range is over 0.25 [diving_modes]
            counter = 0;
            digitalWrite(greenled,HIGH); digitalWrite(redled,LOW); 
       }
  }
  else {
  // if counter will be higher then 10 (let say 10 times loop checked
  // if PPO2 was higher than 0.25 then go to power_down (reset)
      
      if(PPO2 > 512){
        digitalWrite(greenled,HIGH);
        digitalWrite(redled,HIGH);
        _delay_ms(10000); //flush now rebreather by air diluent
        digitalWrite(resetSignal,HIGH);  //RESET DEVICE
        //after reset devie will start again calibration process
      }
      else{
          //sleep and check if PPO2 is higher than 0.25
          //if so do the reset else stay on sleep still
          if (f_wdt==1) {  // wait for timed out watchdog / flag is set when a watchdog timeout occurs
          f_wdt=0; 
          // reset flag
          digitalWrite(greenled,LOW);  // Green LED OFF 
          digitalWrite(redled,LOW);
          pinMode(greenled,INPUT);
          pinMode(greenled,INPUT);
          system_sleep2();
          pinMode(greenled,OUTPUT);
          pinMode(greenled,OUTPUT);
          }
      }
   }

}


// set system into the sleep state 
// system wakes up when wtchdog is timed out
void system_sleep() {
  
  cbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter OFF

  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();
  sleep_mode();                        // System actually sleeps here
  sleep_disable();                     // System continues execution here when watchdog timed out 
  
  sbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter ON
  
}

void system_sleep2() {
  
  counter = 20;
  cbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter OFF

  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();
  sleep_mode();                        // System actually sleeps here
  sleep_disable();                     // System continues execution here when watchdog timed out 
  
  sbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter ON
  
}

// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
void setup_watchdog(int ii) {

  byte bb;
  int ww;
  if (ii > 9 ) ii=9;
  bb=ii & 7;
  if (ii > 7) bb|= (1<<5);
  bb|= (1<<WDCE);
  ww=bb;

  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCR = bb;
  WDTCR |= _BV(WDIE);
}
  
// Watchdog Interrupt Service / is executed when watchdog timed out
ISR(WDT_vect) {
  f_wdt=1;  // set global flag
}
