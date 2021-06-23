#include <avr/io.h>
    #include <avr/pgmspace.h>
    #include <util/delay.h>
    #include <string.h>
    #include <stdlib.h>

    #include "mk_ssd1306.h"

    uint8_t ssd1306_buf[1024] = {
    };

    //funkcja wysyłająca dane przez SPI
    static void SPIwrite( uint8_t dat ) {

            uint8_t i;
            for(i=0x80;i;i>>=1){
                    SCK_LO;
                    if(dat & i) MOSI_HI;
                    else MOSI_LO;
                    SCK_HI;
            }

    }

    //funkcja wysyłająca komendy do wyswietlacza
    void ssd1306_cmd( uint8_t cmd){

    #if USE_CS == 1
            CS_HI;
    #endif

            DC_LO;

    #if USE_CS == 1
            CS_LO;
    #endif

            SPIwrite ( cmd );

    #if USE_CS == 1
            CS_HI;
    #endif
    }

    //funkcja wysyła dane do wyswietalcza
    void ssd1306_data( uint8_t dat){

    #if USE_CS == 1
            CS_HI;
    #endif

            DC_HI;

    #if USE_CS == 1
            CS_LO;
    #endif

            SPIwrite ( dat );

    #if USE_CS == 1
            CS_HI;
    #endif
    }

    //funkcja do przesyłania bufora
    void ssd1306_display(void){

            ssd1306_cmd(SSD1306_SETLOWCOLUMN | 0x0);
            ssd1306_cmd(SSD1306_SETHIGHCOLUMN | 0x0);
            ssd1306_cmd(SSD1306_SETSTARTLINE | 0x0);

    #if USE_CS == 1
                            CS_HI;
    #endif
                            DC_HI;
    #if USE_CS == 1
                            CS_LO;
    #endif

                    for(uint16_t i=0; i<(SSD1306_WIDTH*SSD1306_HEIGHT/8);i++){
                            SPIwrite(0xFF);
                    }

    #if USE_CS == 1
                    CS_HI;
    #endif
    }


    //inicjalizacja SPI
    void ssd1306_InitSpi(void){

            MOSI_DDR |= MOSI;

            SCK_DDR |= SCK;
            SCK_PORT |= SCK;

    #if USE_RST == 1
            RST_DDR |=RST;
            RST_PORT |= RST;
    #endif

            DC_DDR |= DC;

    #if USE_CS == 1
            CS_DDR |= CS;
            CS_PORT |=CS;
    #endif

    }

    //funkcja inicjalizująca wyswietlacz
    void ssd1306_init( uint8_t vcc,uint8_t refresh ){

            ssd1306_InitSpi();

    #if USE_RST == 1
            RST_HI;
            _delay_ms(25);
            RST_LO;
            _delay_ms(25);
            RST_HI;
    #else
            CS_HI;
            _delay_ms(25);
            CS_LO;
            _delay_ms(25);
            CS_HI;
    #endif

            ssd1306_cmd( SSD1306_DISPLAY_OFF );
            ssd1306_cmd( SSD1306_SETDISPLAYCLOCKDIV );
            ssd1306_cmd( refresh );

            ssd1306_cmd(SSD1306_SETDISPLAYOFFSET);
            ssd1306_cmd(0x0);
            ssd1306_cmd(SSD1306_SETSTARTLINE | 0x0);
            ssd1306_cmd(SSD1306_CHARGEPUMP);

            if (vcc == SSD1306_EXTERNALVCC) ssd1306_cmd(0x10);
            else ssd1306_cmd(0x14);

            ssd1306_cmd(SSD1306_MEMORYMODE);
            ssd1306_cmd(0x00);
            ssd1306_cmd(SSD1306_SEGREMAP | 0x1);
            ssd1306_cmd(SSD1306_COMSCANDEC);

            ssd1306_cmd(SSD1306_SETCONTRAST);

            if (vcc == SSD1306_EXTERNALVCC) ssd1306_cmd(0x9F);
            else ssd1306_cmd(0xCF);

            ssd1306_cmd(SSD1306_SETPRECHARGE);

            //ssd1306 - 128 x32

    #if defined SSD1306_128_32
            ssd1306_cmd(SSD1306_SETMULTIPLEX);
            ssd1306_cmd(0x1F);

            ssd1306_cmd(SSD1306_SETCOMPINS);
            ssd1306_cmd(0x02);
    #endif

            //ssd1306 128x64

    #if defined SSD1306_128_64
            ssd1306_cmd(SSD1306_SETMULTIPLEX);
            ssd1306_cmd(0x3F);

            ssd1306_cmd(SSD1306_SETCOMPINS);
            ssd1306_cmd(0x12);
    #endif
            ssd1306_cmd( SSD1306_SETVCOMDETECT);
            ssd1306_cmd(0x40);

            ssd1306_cmd(SSD1306_DISPLAYALLON_RESUME);
            ssd1306_cmd(SSD1306_NORMALDISPLAY);

            ssd1306_cmd(SSD1306_DISPLAY_ON);

    }


