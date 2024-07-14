#include "environment_sensor.h"
#include "utils.h"


// Initialize sensor object
SensirionI2cSht4x tempHumiSensor;


float temperature = 0.0;
float humidity = 0.0;


// Store previous sensor readings for value comparisons
int previousTemp;
int previousHumi;


void initializeTempHumiSensor() {

    Wire.begin();
    tempHumiSensor.begin(Wire, SHT40_I2C_ADDR_44);
    tempHumiSensor.softReset();
}


void readTemperatureAndHumidity() {

    previousTemp = int(temperature);
    previousHumi = int(humidity);


    tempHumiSensor.measureHighPrecision(temperature, humidity);


    // Update display only if current temperature/humidity value differs from previous
    if(int(temperature) != previousTemp) {

        displayTemperature((tft.width() / 3 * 2) + 40, 25);
    }

    if(int(humidity) != previousHumi) {

        displayHumidity((tft.width() / 3 * 2) + 40, 55);
    }
}


void displayTemperature(uint16_t x, uint16_t y) {

    // Clear previous reading
    tft.setTextColor(TFT_BLACK);
    tft.drawString("Temp: " + String((int)previousTemp) + "C", x, y);

    // Draw new temperature value
    tft.setTextColor(BMS_ORANGE);
    tft.drawString("Temp: " + String((int)temperature) + "C", x, y);
}


void displayHumidity(uint16_t x, uint16_t y) {

    // Clear previous reading
    tft.setTextColor(TFT_BLACK);
    tft.drawString("Temp: " + String((int)previousHumi) + "C", x, y);

    // Draw new humidity value
    tft.setTextColor(BMS_ORANGE);
    tft.drawString("Humi: " + String((int)humidity) + "%", x, y);
}