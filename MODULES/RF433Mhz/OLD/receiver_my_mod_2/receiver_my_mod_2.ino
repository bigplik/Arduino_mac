#include <VirtualWire.h>
#include <Wire.h>


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
        
        String wil, S2;
	for (i = 0; i < 6; i++)
	{  wil +=char(buf[i]); }
        for (i > 6; i < 14; i++)
        {  S2 +=char(buf[i]); }
        
        String goodPPO2;
        goodPPO2 = "150";
        
        if(wil.compareTo(goodPPO2) >= 200 || wil.compareTo(goodPPO2) <= 200){
          
          Serial.println ("OK");
          Serial.println (goodPPO2);
          
        }else if(wil.compareTo(goodPPO2) > 201){
         
         Serial.println ("HIGH");
         Serial.println (goodPPO2);

        }else{
          
          Serial.println ("LOW");
          
        }
       
        delay(2000);
        
    }
    
            

}