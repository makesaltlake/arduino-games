/***************************************************
  This is an example sketch for the Adafruit 1.8" SPI display.
  This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
  as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618
 
  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#define paddle_l 22
#define paddle_r 21
//#define sclk 13
//#define mosi 11
#define cs   10
#define dc   9
#define rst  8  // you can also connect this to the Arduino reset

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);
float p = 3.1415926;

void setup(void) {
  tft.initR(INITR_REDTAB);   // alternative: INITR_GREENTAB
  tft.fillScreen(ST7735_BLACK);
  delay(500);
}

#define PADDLE_MAX 1024
#define WIDTH 126
#define HEIGHT 158

int x, y;

void loop() {
  x = analogRead(paddle_l) * WIDTH / PADDLE_MAX;
  y = analogRead(paddle_r) * HEIGHT / PADDLE_MAX;
  
  tft.drawPixel(WIDTH-x, HEIGHT-y, ST7735_GREEN);
}

