
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
    setTextSettings(color565(116, 1, 8), color565(243, 166, 18), 2);
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