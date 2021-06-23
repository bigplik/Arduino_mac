#include <LCD5110_Graph.h>
#include <Wire.h>
//#include <Adafruit_MLX90614.h>

LCD5110 lcd(2,3,4,6,5); //Use this line with the shield

// LCD5110 lcd(8,9,10,12,11); //Use this line with a standalone Nokia 5110 display

char TEMPERATURE = 'C';

extern uint8_t SmallFont[];
extern uint8_t BigNumbers[];
extern uint8_t uic[];
extern uint8_t uif[];
extern uint8_t splash[];

//Adafruit_MLX90614 mlx = Adafruit_MLX90614();

long readVcc() { 
  long result; 
  // Read 1.1V reference against AVcc 
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1); delay(2); 
  // Wait for Vref to settle 
  ADCSRA |= _BV(ADSC); 
  // Convert 
  while (bit_is_set(ADCSRA,ADSC)); 
  result = ADCL; 
  result |= ADCH<<8; 
  result = 1126400L / result; 
  // Back-calculate AVcc in mV 
  return result; 
  }

void setup()
{
  Serial.begin(9600);
  lcd.InitLCD(60);
  //mlx.begin();
  lcd.drawBitmap(0, 0, splash, 84, 48);
  lcd.update();
  delay(3000);
}

void loop()
{
  lcd.clrScr();
  lcd.setFont(BigNumbers);
  
  lcd.print(readVcc(),15,19);
  lcd.update();
  
  delay(1000);
} 

