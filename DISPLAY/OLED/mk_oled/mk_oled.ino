    #include <avr/io.h>
    #include <avr/pgmspace.h>
    #include <util/delay.h>
    #include <string.h>
    #include <stdlib.h>
    #include "mk_ssd1306.h"
   
    #define LED_PORT PORTD
    #define LED1_PIN (1<<PD0)
    #define LED1_ON LED_PORT |= LED1_PIN
    #define LED1_OFF LED_PORT &=~LED1_PIN
    #define LED1_TOG LED_PORT ^=LED1_PIN

void setup() {
  // put your setup code here, to run once:
            DDRD |=LED1_PIN;
            LED1_ON;
            _delay_ms(1000);
            //ssd1306_init(SSD1306_SWITCHCAPVCC,REFRESH_MIN);
            //ssd1306_display();
}

void loop() {
  // put your main code here, to run repeatedly:

}
