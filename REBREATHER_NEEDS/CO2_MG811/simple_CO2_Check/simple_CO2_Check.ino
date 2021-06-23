#include <Flasher.h>
#include <avr/sleep.h>

// Utility macros
#define adc_disable() (ADCSRA &= ~(1<<ADEN)) // disable ADC (before power-off)
#define adc_enable()  (ADCSRA |=  (1<<ADEN)) // re-enable ADC


float bat;
byte  speaker = 0;
byte  FET = 1;
float co2_First = 0;

Flasher slowFlash(0,750); Flasher fastFlash(0,250);

void enterSleep(void)
{
  adc_disable();
  sleep_enable();
  sleep_cpu();
}

void setup() {
  // put your setup code here, to run once:
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  
  pinMode(speaker,OUTPUT); digitalWrite(0,0);  //speaker
  pinMode(FET,OUTPUT); digitalWrite(1,0);  //FET
  
  //voltage divider for 8.4v bat
  //4.7K and 1K
  bat = (analogRead(A1)*(5.0/1023.0)/0.175)/2;
  
  if(bat > 3.9){
    slowFlash.flash(1);
    digitalWrite(FET,LOW); //turn FET on
    delay(300000);         //warming MG-811
    co2_First = analogRead(A3)*(5.0/1023.0);
  }
  else if(bat > 3.6 && bat < 3.91){
    slowFlash.flash(2);
    digitalWrite(FET,LOW); //turn FET on
    delay(300000);         //warming MG-811
    co2_First = analogRead(A3)*(5.0/1023.0);
  }
  else if(bat > 3.29 && bat < 3.61){
    slowFlash.flash(3);
    digitalWrite(FET,LOW); //turn FET on
    delay(300000);         //warming MG-811
    co2_First = analogRead(A3)*(5.0/1023.0);
  }
  else{ 
    digitalWrite(FET,HIGH); //turn FET off
    fastFlash.flash(10);
    enterSleep();
  }
  delay(2000);
  fastFlash.flash(3);    //notice about finish of setup task
}

void loop() {
  // put your main code here, to run repeatedly:
  bat = (analogRead(A1)*(5.0/1023.0)/0.175)/2;
  float co2_Check = analogRead(A3)*(5.0/1023.0);
  
  if(bat < 3.0){
    slowFlash.flash(10);
    digitalWrite(FET,HIGH); //turn FET off (high signal
    //to close MOSFET-P gate)
    enterSleep();          //go sleep
  }      
  else{ 
       if(co2_Check > (co2_First-0.4)) slowFlash.flash(1); 
       else if(co2_Check < (co2_First-0.9)){
             for(int i=0; i<3; i++){
               fastFlash.flash(8);
               delay(1000);
             }
       }
       else{ slowFlash.flash(3); }
  }  
  delay(6000); //every minute
  
}
