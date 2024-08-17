/**********************************************
 *                                            *
 * This file contains utility functions for   *
 * the BunnyTerminal sketch.                  *
 *                                            *
 **********************************************/



#include "utils.h"



TFT_eSPI tft; // Declare TFT object



// Translate 24 bit rgb value to 16 bit
uint16_t color565(uint8_t red, uint8_t green, uint8_t blue) {

    return ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | (blue >> 3);
}



// Set up TFT screen
void initializeTFTScreen() {

    tft.begin();
    tft.setRotation(3);
    setTextSettings(BMS_ORANGE, TFT_BLACK, 2);
}



// Set text settings and background color.
void setTextSettings(uint16_t bgColor, uint16_t textColor, int textSize) {

    tft.setTextSize(textSize);
    tft.fillScreen(bgColor);
    tft.setTextColor(textColor);
    tft.setTextDatum(MC_DATUM);
}


// Draw text on TFT screen
void displayText(char* text, uint16_t textColor, uint16_t bgColor) {

    tft.fillScreen(bgColor);
    tft.setTextColor(textColor);
    tft.drawString(text, tft.width() / 2, tft.height() / 2);
}


// Display dashboard
void drawDashboard() {

    tft.setTextColor(BMS_ORANGE);
    tft.fillScreen(BMS_ORANGE);
    tft.fillRect(0, 0, tft.width(), tft.height() / 3 - 15, TFT_BLACK);

    tft.drawString("Happy Bunny Monitoring!", tft.width() / 2, 35);
    tft.drawLine(tft.width() / 2, 35, tft.width() / 2, tft.height(), TFT_BLACK);
}


// Round floating point numbers
float roundToDecimalPlace(float num, int decimals) {


  if(decimals > 0) {

    float multiplier = pow(10, decimals);
    return round(num * multiplier) / multiplier;
  }

  return round(num);
}