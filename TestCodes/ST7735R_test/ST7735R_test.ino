/*
This code is used to test the ST7735R TFT LCD
the function is to display text incrementing in size
in continous loop
*/

// Adafruit graphical library
#include <Adafruit_GFX.h>
// Adafruit hardware library
#include <Adafruit_ST7735.h>
// SPI library
#include <SPI.h>


/* Reset is set to -1 so that when the controller is reset
so is the display*/
#define TFT_RST -1
#define TFT_DC 8
#define TFT_CS 10

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Variable to store the string displayed
String txt = "Hello World!";
// Variable to increment the text size and manipulate the rotation
int txtSize = 1;
void setup() {
// display initialization with a white background
tft.initR(INITR_BLACKTAB);
// writing the complete display to white
tft.fillScreen(ST7735_WHITE);
// initializing the rotation of the display in this case landscape
tft.setRotation(0);

}

void loop() {
  
  if(txtSize == 3){txtSize = 1;}
    
  outputTxt(txt,txtSize);
  
  // delaying 10,000 milli seconds which accumulates to 10 seconds
  delay(10000);
  
  txtSize ++;
  tft.fillScreen(ST7735_WHITE);
  tft.setRotation(txtSize);

}

void outputTxt(String txt,int txtSize){
  tft.setCursor(64,64);
  tft.setTextColor(ST7735_BLACK);
  tft.setTextWrap(true);
  tft.setTextSize(txtSize);
  tft.print(txt);
  }
