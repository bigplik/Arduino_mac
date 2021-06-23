#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define NUMFLAKES 10
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };



/* invert the display
  OLED.invertDisplay(true);
  delay(1000); 
  OLED.invertDisplay(false);
  
  
// miniature bitmap display
  OLED.clearDisplay();
  OLED.drawBitmap(30, 16,  logo16_glcd_bmp, 16, 16, 1);
  OLED.display();


/* draw a bitmap icon and 'animate' movement
     testdrawbitmap(logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH); */
void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];
 
  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random(OLED.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;
    
    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }

  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      OLED.drawBitmap(icons[f][XPOS], icons[f][YPOS], logo16_glcd_bmp, w, h, WHITE);
    }
    OLED.display();
    delay(200);
    
    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      OLED.drawBitmap(icons[f][XPOS], icons[f][YPOS],  logo16_glcd_bmp, w, h, BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > OLED.height()) {
	icons[f][XPOS] = random(OLED.width());
	icons[f][YPOS] = 0;
	icons[f][DELTAY] = random(5) + 1;
      }
    }
   }
}


/* draw the first ~12 characters in the font
  testdrawchar();
  OLED.display();
  delay(2000);
  OLED.clearDisplay(); */
void testdrawchar(void) {
  OLED.setTextSize(1);
  OLED.setTextColor(WHITE);
  OLED.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    OLED.write(i);
    if ((i > 0) && (i % 21 == 0))
      OLED.println();
  }    
  OLED.display();
}


/* draw mulitple circles
  testdrawcircle();
  OLED.display();
  delay(2000);
  OLED.clearDisplay(); */
void testdrawcircle(void) {
  for (int16_t i=0; i<OLED.height(); i+=2) {
    OLED.drawCircle(OLED.width()/2, OLED.height()/2, i, WHITE);
    OLED.display();
  }
}


  /* draw multiple rectangles
  testfillrect();
  OLED.display();
  delay(2000);
  OLED.clearDisplay(); */
void testfillrect(void) {
  uint8_t color = 1;
  for (int16_t i=0; i<OLED.height()/2; i+=3) {
    // alternate colors
    OLED.fillRect(i, i, OLED.width()-i*2, OLED.height()-i*2, color%2);
    OLED.display();
    color++;
  }
}


/*  testdrawtriangle();
  delay(2000);
  OLED.clearDisplay(); */
void testdrawtriangle(void) {
  for (int16_t i=0; i<min(OLED.width(),OLED.height())/2; i+=5) {
    OLED.drawTriangle(OLED.width()/2, OLED.height()/2-i,
                     OLED.width()/2-i, OLED.height()/2+i,
                     OLED.width()/2+i, OLED.height()/2+i, WHITE);
    OLED.display();
  }
}


/*  testfilltriangle();
  delay(2000);
  OLED.clearDisplay(); */
void testfilltriangle(void) {
  uint8_t color = WHITE;
  for (int16_t i=min(OLED.width(),OLED.height())/2; i>0; i-=5) {
    OLED.fillTriangle(OLED.width()/2, OLED.height()/2-i,
                     OLED.width()/2-i, OLED.height()/2+i,
                     OLED.width()/2+i, OLED.height()/2+i, WHITE);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    OLED.display();
  }
}


/*  testdrawroundrect();
  delay(2000);
  OLED.clearDisplay(); */
void testdrawroundrect(void) {
  for (int16_t i=0; i<OLED.height()/2-2; i+=2) {
    OLED.drawRoundRect(i, i, OLED.width()-2*i, OLED.height()-2*i, OLED.height()/4, WHITE);
    OLED.display();
  }
}


/*  testfillroundrect();
  delay(2000);
  OLED.clearDisplay(); */
void testfillroundrect(void) {
  uint8_t color = WHITE;
  for (int16_t i=0; i<OLED.height()/2-2; i+=2) {
    OLED.fillRoundRect(i, i, OLED.width()-2*i, OLED.height()-2*i, OLED.height()/4, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    OLED.display();
  }
}
   

  /* draw rectangles
  testdrawrect();
  OLED.display();
  delay(2000);
  OLED.clearDisplay(); */
void testdrawrect(void) {
  for (int16_t i=0; i<OLED.height()/2; i+=2) {
    OLED.drawRect(i, i, OLED.width()-2*i, OLED.height()-2*i, WHITE);
    OLED.display();
  }
}


  /* draw many lines
  testdrawline();
  OLED.display();
  delay(2000);
  OLED.clearDisplay(); */
void testdrawline() {  
  for (int16_t i=0; i<OLED.width(); i+=4) {
    OLED.drawLine(0, 0, i, OLED.height()-1, WHITE);
    OLED.display();
  }
  for (int16_t i=0; i<OLED.height(); i+=4) {
    OLED.drawLine(0, 0, OLED.width()-1, i, WHITE);
    OLED.display();
  }
  delay(250);
  
  OLED.clearDisplay();
  for (int16_t i=0; i<OLED.width(); i+=4) {
    OLED.drawLine(0, OLED.height()-1, i, 0, WHITE);
    OLED.display();
  }
  for (int16_t i=OLED.height()-1; i>=0; i-=4) {
    OLED.drawLine(0, OLED.height()-1, OLED.width()-1, i, WHITE);
    OLED.display();
  }
  delay(250);
  
  OLED.clearDisplay();
  for (int16_t i=OLED.width()-1; i>=0; i-=4) {
    OLED.drawLine(OLED.width()-1, OLED.height()-1, i, 0, WHITE);
    OLED.display();
  }
  for (int16_t i=OLED.height()-1; i>=0; i-=4) {
    OLED.drawLine(OLED.width()-1, OLED.height()-1, 0, i, WHITE);
    OLED.display();
  }
  delay(250);

  OLED.clearDisplay();
  for (int16_t i=0; i<OLED.height(); i+=4) {
    OLED.drawLine(OLED.width()-1, 0, 0, i, WHITE);
    OLED.display();
  }
  for (int16_t i=0; i<OLED.width(); i+=4) {
    OLED.drawLine(OLED.width()-1, 0, i, OLED.height()-1, WHITE); 
    OLED.display();
  }
  delay(250);
}

/* draw scrolling text
  testscrolltext();
  delay(2000);
  OLED.clearDisplay(); */
void testscrolltext(void) {
  OLED.setTextSize(2);
  OLED.setTextColor(WHITE);
  OLED.setCursor(10,0);
  OLED.clearDisplay();
  OLED.println("scroll");
  OLED.display();
 
  OLED.startscrollright(0x00, 0x0F);
  delay(2000);
  OLED.stopscroll();
  delay(1000);
  OLED.startscrollleft(0x00, 0x0F);
  delay(2000);
  OLED.stopscroll();
  delay(1000);    
  OLED.startscrolldiagright(0x00, 0x07);
  delay(2000);
  OLED.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  OLED.stopscroll();
}

/*
// The following code will exercise 3 fonts on the OLED for testing:
 #include <SPI.h>
  #include <Wire.h>
  #include ".\Adafruit_GFX.h"
  #include ".\Adafruit_SSD1306.h"

  // software SPI works on Maple Mini ARM 32-bit
  // use these settings for the OLED_Pro smart display...
  // These pin #'s are for Maple Mini/UNO/Nano/Mini328
  #define OLED_DC    6  // D/C
  #define OLED_RESET 5  // RST
  #define OLED_MOSI  4  // SDA
  #define OLED_CLK   3  // SCL
  #define OLED_CS    7  // Not Connected to OLED board
  Adafruit_SSD1306 OLED(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


void setup()   {

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  OLED.begin(SSD1306_SWITCHCAPVCC);

  OLED.display();                // Adafruit Splash
  delay(2000);
  // Y = 15 is the Blank Line between yellow / blue
}


void loop() {
  OLED.clearDisplay();           // Clear the buffer.
  // OLED.setTextSize(1);        // 21 char/line (fills 1st & 2nd lines in yellow) 8 lines Max
  // OLED.setTextSize(2);        // 10 char/line (fills 1st line in yellow)        4 lines Max
  // OLED.setTextSize(3);        //  7 char/line (overflows 1st yellow into Blue)

  OLED.setTextSize(1);
  OLED.setTextColor(WHITE);      // only WHITE and BLACK available
  OLED.setCursor(0,0);
  OLED.print(  "123456789012345678901");
  OLED.println("2....................");
  OLED.setCursor(0,16);          // top-left of Blue Pixels (15 is blank-line separator)
  OLED.println("3");
  OLED.println("4");
  OLED.println("5");
  OLED.println("6");
  OLED.println("7");
  OLED.println("8");
  OLED.setCursor(16,16);
  OLED.setTextSize(2);
  OLED.println("ABCDEFGHI");
  // OLED.setTextColor(BLACK, WHITE); // 'inverted' text
  OLED.setTextSize(3);
  OLED.setCursor(16,35);
  OLED.println(3.1);
  //OLED.setTextSize(2);
  OLED.setTextColor(WHITE);
  //OLED.print("0x"); OLED.println(0xDEADBEEF, HEX);
  OLED.display();
  delay(2000);
}

*/
