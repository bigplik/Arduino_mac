// OneWire DS18B20 Temperature Switch on ATtiny85
//
// Check temperature every second.
// Fan turned on when hot, off when cool.
//
 
// fan switch temperatures in Fahrenheit
#define HOT 80.0
#define COOL 79.0
 
#include <OneWire.h> 
 
// pins
#define ONEWIRE_BUSS 3
#define STATUS_LED  4
#define FAN 2

int fresh; 
 
OneWire TemperatureSensor(ONEWIRE_BUSS);  // Dallas one wire data buss pin, a 4.7K resistor pullup is needed
 
void blink(void){
    digitalWrite(STATUS_LED,HIGH);
    delay (250);
    digitalWrite(STATUS_LED,LOW);
    delay (175);
}
 
void setup(void) {
    pinMode(STATUS_LED, OUTPUT);
    pinMode(FAN, OUTPUT);
    blink();
    blink();
}
 
void loop(void) {
    byte i;
    byte data[12];
    int16_t raw;
    float celsius, fahrenheit;
 
    TemperatureSensor.reset();       // reset one wire buss
    TemperatureSensor.skip();        // select only device
    TemperatureSensor.write(0x44);   // start conversion
 
    delay(1000);                     // wait for the conversion
 
    TemperatureSensor.reset();
    TemperatureSensor.skip();
    TemperatureSensor.write(0xBE);   // Read Scratchpad
    for ( i = 0; i < 9; i++) {       // 9 bytes
      data[i] = TemperatureSensor.read();
    }
 
    // Convert the data to actual temperature
    //raw = (data[1] << 8) | data[0];
    fresh = (data[1]*256) + data[0];
    //celsius = (float)raw / 16.0;
    //fahrenheit = celsius * 1.8 + 32.0;

 
    // Turn Fan on/off depending on temperature
    if(fresh > 1200){ //485=30C
      digitalWrite(4,HIGH);  // on
    }
 
    else{
      digitalWrite(4,LOW);   // off
    }
 
    //digitalWrite(STATUS_LED,digitalRead(FAN));  // copy fan state to status led
 

 
}
