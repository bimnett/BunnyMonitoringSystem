#ifndef environment_sensor_h
#define environment_sensor_h

#include <SensirionI2cSht4x.h>
#include <Wire.h>

extern SensirionI2cSht4x tempHumiSensor;
extern float temperature;
extern float humidity;

void initializeTempHumiSensor();
void displayTemperature(uint16_t x, uint16_t y);
void displayHumidity(uint16_t x, uint16_t y);
void readTemperatureAndHumidity();

#endif