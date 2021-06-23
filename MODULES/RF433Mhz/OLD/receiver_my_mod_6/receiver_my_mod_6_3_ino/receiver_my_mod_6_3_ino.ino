/*
Connection instructions for RF Revciever
+ 5v
GND
DATA - pin 4
*/

#include <VirtualWire.h>
#include <Wire.h>
#include <stdlib.h>




void setup()
{
    Serial.begin(9600);	// Debugging only
    delay(4000);
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
        
        String wil, tem, cis;
	for (i = 0; i < 6; i++)
	{  wil +=char(buf[i]); }
        for (i > 6; i < 14; i++)
        {  cis +=char(buf[i]); }
        for (i = 15; i < buflen; i++)
        {  tem +=char(buf[i]); }
    
    
     
        
          //Serial.print("S1: ");
          Serial.println (wil);
          Serial.println();
          //Serial.print("S2: "); 
          Serial.println (cis);
          Serial.println();
          //Serial.print("S3: "); 
          //Serial.println (tem);       
                      

          
        }
        
       delay(2000);
        
    

    
            

}
