#include "rpcWiFi.h" // WiFi library
#include "secrets.h" // Hidden credentials
#include "utils.h" // Utility methods
#include "mqtt.h" // MQTT methods
#include "environment_sensor.h" // Temperature and Humidity methods


unsigned long previousMillis = 0; // Store previous time that temperature and humidity were read
const long interval = 10000; // Temperature & Humidity reading interval


void setup() {

    initializeTFTScreen();
    connectToWiFi();
    connectToMQTTBroker();
    initializeTempHumiSensor();
    drawDashboard();
}



void loop() {

    // Reconnect to WiFi if disconnected
    if(!WiFi.isConnected()) {

        connectToWiFi();
    }


    // Reconnect to MQTT broker if disconnected
    if(!mqttClient.loop()) {

        connectToMQTTBroker();
    }


    unsigned long currentMillis = millis();

    // Check if the interval has passed
    if (currentMillis - previousMillis >= interval) {
        // Save the last time you read the sensor
        previousMillis = currentMillis;

        // Read temperature and humidity
        readTemperatureAndHumidity();
        publishSensorData();
    }
}


// Connect to WiFi
void connectToWiFi() {

    // Attempt to connect to the WiFi network until a connection is established
    while(!WiFi.isConnected()) {
        displayText("Connecting to WiFi..", TFT_BLACK, BMS_ORANGE);
        WiFi.begin(SSID, WIFI_PASSWORD);
        delay(2000);
    }

    // Display confirmation
    displayText("Wifi Connected!", TFT_BLACK, BMS_ORANGE);
    delay(1500);
}