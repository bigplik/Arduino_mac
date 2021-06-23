#ifndef MK_SSD1306_H_
    #define MK_SSD1306_H_

    //definicje stałych preprocesora

    //definujemy rozdzielczosc LCD/OLED

    #define SSD1306_128_64
    //#define SSD1306_128_32


    //definiujemy czy korzystamy z pinów CS i RST

    #define USE_CS  0
    #define USE_RST 1


    //definujemy piny do których podłączony jest wyswietlacz

    #define SCK (1<<7)  // <-CLK
    #define MOSI (1<<6) // <-SDA
    #define RST (1<<5)  // <-RST
    #define DC (1<<4)   // <-D/C

    #define CS (1<<3)   // <-CS

    //definiujemy port do którego podłączony jest wyswietlacz


    #define SCK_PORT PORTC
    #define SCK_DDR DDRC

    #define MOSI_PORT PORTC
    #define MOSI_DDR DDRC

    #define RST_PORT PORTC
    #define RST_DDR DDRC

    #define DC_PORT PORTC
    #define DC_DDR DDRC

    #define CS_PORT PORTC
    #define CS_DDR DDRC

    //makra upraszczające sterowanie pinami

    #define RST_LO RST_PORT &=~RST
    #define RST_HI RST_PORT |=RST

    #define CS_LO CS_PORT &=~CS
    #define CS_HI CS_PORT |=CS

    #define DC_LO DC_PORT &=~DC
    #define DC_HI DC_PORT |=DC

    #define SCK_LO SCK_PORT &=~SCK
    #define SCK_HI SCK_PORT |=SCK

    #define MOSI_LO MOSI_PORT &=~MOSI
    #define MOSI_HI MOSI_PORT |=MOSI

    //deklaracja zmiennych przechowywujących wysokosc i szerokosc wyswietlacza

    #define SSD1306_WIDTH  128

    #if defined SSD1306_128_64
            #define SSD1306_HEIGHT  64
    #endif

    #if defined SSD1306_128_32
            #define SSD1306_HEIGHT 32
    #endif


    //definicja wartosci odswierzania

    #define REFRESH_MIN 0x80
    #define REFRESH_MID 0xB0
    #define REFRESH_MAX 0xF0

    //definicja komend do obsługi wywietlacza

    #define SSD1306_SETCONTRAST 0x81
    #define SSD1306_DISPLAYALLON_RESUME 0xA4
    #define SSD1306_DISPLAYALLON 0xA5
    #define SSD1306_NORMALDISPLAY 0xA6
    #define SSD1306_INVERTDISPLAY 0xA7
    #define SSD1306_DISPLAY_OFF 0xAE
    #define SSD1306_DISPLAY_ON 0xAF

    #define SSD1306_SETDISPLAYOFFSET 0xD3
    #define SSD1306_SETCOMPINS 0xDA

    #define SSD1306_SETVCOMDETECT 0xDB

    #define SSD1306_SETDISPLAYCLOCKDIV 0xD5
    #define SSD1306_SETPRECHARGE 0xD9

    #define SSD1306_SETMULTIPLEX 0xA8

    #define SSD1306_SETLOWCOLUMN 0x00
    #define SSD1306_SETHIGHCOLUMN 0x10

    #define SSD1306_SETSTARTLINE 0x40

    #define SSD1306_MEMORYMODE 0x20

    #define SSD1306_COMSCANINC 0xC0
    #define SSD1306_COMSCANDEC 0xC8

    #define SSD1306_SEGREMAP 0xA0

    #define SSD1306_CHARGEPUMP 0x8D

    #define SSD1306_EXTERNALVCC 0x1
    #define SSD1306_SWITCHCAPVCC 0x2

    //Scrolling #defines
    #define SSD1306_ACTIVATE_SCROLL 0x2F
    #define SSD1306_DEACTIVATE_SCROLL 0x2E
    #define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
    #define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
    #define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
    #define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
    #define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A


    //definicje zmiennych




    // deklaracje funkcji

    void ssd1306_init( uint8_t vcc,uint8_t refresh);
    void ssd1306_cmd( uint8_t cmd);
    void ssd1306_data( uint8_t dat);
    void ssd1306_display(void);



    #endif /* SSD1306_H_ */


