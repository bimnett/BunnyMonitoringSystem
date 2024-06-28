#ifndef utils_h
#define utils_h


#include <stdint.h> // Integer type library
#include "TFT_eSPI.h" // TFT screen library


// Utility method signatures
uint16_t color565(uint8_t red, uint8_t green, uint8_t blue);
void setTextSettings(uint16_t bgColor, uint16_t textColor, int textSize);
void displayText(char* text, uint16_t textColor, uint16_t bgColor);
void initializeTFTScreen();


#endif