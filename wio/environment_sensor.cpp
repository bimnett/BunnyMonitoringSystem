#include "environment_sensor.h"
#include "utils.h" // Utility methods


// Initialize sensor object
SensirionI2cSht4x tempHumiSensor;


// Store current environment data
float temperature = 0.0;
float humidity = 0.0;


// Store previous sensor readings for value comparisons
int previousTemp;
int previousHumi;


// Setup environment sensor
void initializeTempHumiSensor() {

    Wire.begin();
    tempHumiSensor.begin(Wire, SHT40_I2C_ADDR_44);
    tempHumiSensor.softReset();
}


// Read and display current environment readings
void readTemperatureAndHumidity() {

    previousTemp = int(temperature);
    previousHumi = int(humidity);


    tempHumiSensor.measureHighPrecision(temperature, humidity);


    // Update display only if current temperature/humidity value differs from previous
    if(int(temperature) != previousTemp) {

        displayTemperature();
    }

    if(int(humidity) != previousHumi) {

        displayHumidity();
    }
}


// Display current temperature reading on the Wio terminal's screen
void displayTemperature() {

    // Clear previous reading
    tft.setTextColor(BMS_ORANGE);
    tft.setTextSize(5);
    tft.drawString(String((int)previousTemp) + "C", tft.width() / 3 - 30, tft.height() / 3 + 80);

    // Draw new temperature value
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(3);
    tft.drawString("Temp", tft.width() / 3 - 30, tft.height() / 3 + 15);
    tft.setTextSize(5);
    tft.drawString(String((int)temperature) + "C", tft.width() / 3 - 30, tft.height() / 3 + 80);
}


// Display current humidity level on the Wio terminal's screen
void displayHumidity() {

    // Clear previous reading
    tft.setTextColor(BMS_ORANGE);
    tft.setTextSize(5);
    tft.drawString(String((int)previousHumi) + "%", tft.width() / 3 * 2 + 30, tft.height() / 3 + 80);

    // Draw new humidity value
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(3);
    tft.drawString("Humi", tft.width() / 3 * 2 + 30, tft.height() / 3 + 15);
    tft.setTextSize(5);
    tft.drawString(String((int)humidity) + "%", tft.width() / 3 * 2 + 30, tft.height() / 3 + 80);
}