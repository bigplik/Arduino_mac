/*Attiny_85Pins

    0 >>>>>>>>>>>> SDA    / PWM
    1 >>>>>>>>>>>> ANALOG / PWM
    2 >>>>>>>>>>>> SCL
    3 >>>>>>>>>>>> ANALOG / RX
    4 >>>>>>>>>>>> ANALOG / TX
    5 >>>>>>>>>>>> RESET  
    (check possiblity to use RESET as A0, when voltage is
    far enough above 0V)
    
                 __________
         A0 RES _|        |_ VCC
         D3 A3  _| ATTINY |_ SCL SCK  D2 A1
         D4 A2  _|   85   |_ MISO     D1 PWM
         GND    _|        |_ SDA MOSI D0 PWM
                 |________|

                 __________
         RES 5  _|        |_ VCC
          A3 4  _| ATTINY |_ 2 A1
          A2 3  _|   85   |_ 1 PWM
           GND  _|        |_ 0 PWM
                 |________|
    

    
*/
