#include <VirtualWire.h>
#include <Wire.h>
#include <stdlib.h>

char inChar;
char inData[5];
int index = 0; //counter variable
int val = 0; //value to come from inData conversion using atoi()
int  LED = 13;   // Pin 13 is connected to a LED on many Arduinos


void setup()
{
    Serial.begin(9600);	// Debugging only
    delay(2000);
    Serial.println("setup");

    vw_setup(2000);	 // Bits per sec
    vw_set_rx_pin(4);
    vw_rx_start();
   
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
	int i;
        
        String wil, S2;
	for (i = 0; i < 6; i++)
	{  wil +=char(buf[i]); }
        for (i > 6; i < 14; i++)
        {  S2 +=char(buf[i]); }
        
        String goodPPO2, highPPO2, lowPPO2, S1, s, S11, S111; //goodPPO2 is 0.70, high
        //is over 1.60 and low is less form 0.40
        
        S1 = s + 150;
        S11 = s + 200;
        S111 = s + 100;
        
       // goodPPO2 = "150";
        highPPO2 = s + 201;
        lowPPO2 = "80";
        
       int value;
       value = (int)inChar;
       
       int m;
       char n = 'A';
       String q;
       m=n;
     
        
        if(wil < S11 && wil > S111){
          
          Serial.println ("OK");
          //Serial.println (goodPPO2);
          Serial.println (wil);
          Serial.println (S1);
                    Serial.println (S11);
                              Serial.println (S111);


          
        }
        else if(wil >= S11 ){
         
         Serial.println ("HIGH");
         //Serial.println (goodPPO2);
        Serial.println (wil);
              Serial.print ("S1: "); 
              Serial.println (S1);
                    Serial.print ("S11: ");
                    Serial.println (S11);
                              Serial.print ("S111: ");
                              Serial.println (S111);
                              Serial.println (m);

        }
        else{
          
         Serial.println ("LOW");
         //Serial.println (goodPPO2);
         Serial.println (wil);
          
        }
        
        delay(2000);
        
    }
    
            

}
