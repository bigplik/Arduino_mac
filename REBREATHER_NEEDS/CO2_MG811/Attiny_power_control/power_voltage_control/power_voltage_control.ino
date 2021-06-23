#include <Flasher.h>
#include <avr/sleep.h>

// Utility macros
#define adc_disable() (ADCSRA &= ~(1<<ADEN)) // disable ADC (before power-off)
#define adc_enable()  (ADCSRA |=  (1<<ADEN)) // re-enable ADC

/*
DIY ATTINY BOARD PINS
  0 - 
  1 - blueLED
  2 - 
  3 - greenLED
  4 - redLED

*/

int power = 1;
float bat;
byte speaker = 0;
byte FET = 1;
int co2_First = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(0,OUTPUT); digitalWrite(0,0);  //speaker
  pinMode(1,OUTPUT); digitalWrite(1,0);  //FET
  pinMode(2,INPUT); //digitalWrite(2,0); //ANALOG IN
  pinMode(3,INPUT);// digitalWrite(3,0); //ANALOG CO2
  pinMode(4,INPUT); //digitalWrite(4,0); 
  
  //flasher settings
  Flasher slowFlash(0,750); Flasher fastFlash(0,250);
  
  //battery readings
  bat = analogRead(A1) *(5.0/1023.0); //BY 2 because 20k resistor divider
  //between 2 cells. 2 cells in series 8.4V MAX.
  if(bat > 3.9) { slowFlash.flash(1);    
    //digitalWrite(speaker,HIGH); delay(3000); digitalWrite(speaker,LOW); 
  power = 1; }
  else if(bat > 3.6 && bat < 3.91){ slowFlash.flash(2); 
  power = 1; }
  else if(bat > 3.29 && bat < 3.61){ slowFlash.flash(3); 
  power = 1; }
  else{ fastFlash.flash(10); power = 0 ; }
  delay(2000);
  
  //power down mode Settings
  //adc_disable(); // ADC uses ~320uA
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  
  //MOSFET POWER CONTROL
  //if power is 'on' then signal for the mosfet gate open it
  //and turn MG811 ON
  //else if power is 'off' mosfet is turend off and MG811 isn't
  //working
  if(power == 1) {digitalWrite(FET,HIGH); 
  delay(300000); //for end should be 5min for heating sensor
  slowFlash.flash(3); delay(1000); slowFlash.flash(3); delay(1000);
  slowFlash.flash(3);
  digitalWrite(speaker,LOW); 
  co2_First = analogRead(A3);
  }
  else{ digitalWrite(speaker,LOW); digitalWrite(FET,LOW);
//        pinMode(0,INPUT); pinMode(1,INPUT); pinMode(2,INPUT);
//        pinMode(3,INPUT); pinMode(4,INPUT); 
          //digitalWrite(4,1);
          delay(5000);
          //digitalWrite(4,0);
        enterSleep();}
}

void enterSleep(void)
{
  //adc_disable();
  sleep_enable();
  sleep_cpu();
}

void loop() {
  // put your main code here, to run repeatedly:
  bat = analogRead(A1)*(5.0/1023.0);
  int co2_Check = analogRead(A3);
  Flasher slowFlash(0,750); Flasher fastFlash(0,250);
  
  if(bat < 3.0){                       
        digitalWrite(FET,LOW);              //turn the FET off
        //digitalWrite(4,HIGH);
        slowFlash.flash(10);
//        pinMode(0,INPUT); pinMode(1,INPUT); pinMode(2,INPUT);
//        pinMode(3,INPUT); pinMode(4,INPUT);
        //digitalWrite(4,LOW);
        enterSleep(); }                  //go sleep
  else{ digitalWrite(FET,HIGH); 
       if(co2_Check < (co2_First*1.3)) slowFlash.flash(1); 
       else if(co2_Check > (co2_First*1.6)) fastFlash.flash(16);
       else{ slowFlash.flash(3); }
      }
  
  delay(60000); //every minute

}
