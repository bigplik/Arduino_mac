#include <Flasher.h>
#include <avr/sleep.h>


// Utility macros
#define adc_disable() (ADCSRA &= ~(1<<ADEN)) // disable ADC (before power-off)
#define adc_enable()  (ADCSRA |=  (1<<ADEN)) // re-enable ADC

int power = 1;
float bat;
byte speaker = 0;
byte FET = 1;
int co2_First = 0;
int workMode = 0;
float firstValue = 0;
float batread = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(speaker,OUTPUT); //digitalWrite(0,0);  //speaker
  digitalWrite(speaker,LOW);
  pinMode(FET,OUTPUT); //digitalWrite(1,0);  //FET
  digitalWrite(FET,HIGH); //FET off
  //pinMode(2,INPUT); //digitalWrite(2,0); //ANALOG IN
  //pinMode(3,INPUT);// digitalWrite(3,0); //ANALOG CO2
  //pinMode(4,INPUT); //digitalWrite(4,0);
  delay(500);
  //flasher settings
  Flasher slowFlash(0,750); Flasher fastFlash(0,250);
  delay(500);  
}

void enterSleep(void)
{
  adc_disable();
  sleep_enable();
  sleep_cpu();
}

void loop() {
  // put your main code here, to run repeatedly:
  bat = (analogRead(A1)*(5.0/1023.0)/0.175)/2;
  float co2_Check = analogRead(A3)/(5.0/1023.0);
  Flasher slowFlash(0,750); Flasher fastFlash(0,250);
  
  switch (workMode) {
    case 0:
      delay(200);
      if(bat > 3.9) { slowFlash.flash(1);    
        //digitalWrite(speaker,HIGH); delay(3000); digitalWrite(speaker,LOW); 
      digitalWrite(FET,LOW); delay(300000); //warming MG-811 for 5min
      co2_First = analogRead(A3)*(5.0/1023.0);
      workMode = 1;
      }
      else if(bat > 3.6 && bat < 3.91){ slowFlash.flash(2); 
      digitalWrite(FET,LOW); delay(300000); //warming MG-811 for 5min
      co2_First = analogRead(A3)*(5.0/1023.0);
      workMode = 1;
      }
      else if(bat > 3.29 && bat < 3.61){ slowFlash.flash(3); 
      digitalWrite(FET,LOW); delay(300000); //warming MG-811 for 5min
      co2_First = analogRead(A3)*(5.0/1023.0);
      workMode = 1;
      }
      else{ slowFlash.flash(10); 
      digitalWrite(FET,HIGH); //FET off, switch to sleep mode
      workMode = 2;
      }
      delay(2000);
      //digitalWrite(2,LOW);
      //workMode = 1;
      break;
    case 1:
      if(bat < 3.0){                       
          digitalWrite(FET,HIGH);              //turn the FET off
          //digitalWrite(4,HIGH);
          slowFlash.flash(10);
  //        pinMode(0,INPUT); pinMode(1,INPUT); pinMode(2,INPUT);
  //        pinMode(3,INPUT); pinMode(4,INPUT);
          //digitalWrite(4,LOW);
          workMode++;  }                  //go sleep
      else{ digitalWrite(FET,LOW); 
           if(co2_Check > (co2_First-0.4)) slowFlash.flash(1); 
           else if(co2_Check < (co2_First-0.8)){
             for(int i=0; i<3; i++){
               fastFlash.flash(8);
               delay(1000);
             }
           }
           else{ slowFlash.flash(3); }
          }
      
      delay(6000); //every minute
      break;
    case 2:
      enterSleep();
      break;
  }
}


