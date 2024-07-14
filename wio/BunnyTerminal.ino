#include "rpcWiFi.h" // WiFi library
#include "secrets.h" // Hidden credentials
#include "utils.h" // Utility methods
#include "mqtt.h" // MQTT methods
#include "environment_sensor.h" // Temperature and Humidity methods


unsigned long previousMillis = 0; // Store previous time that temperature and humidity were read
const long interval = 1000; // Temperature & Humidity reading interval


void setup() {

    initializeTFTScreen();
    connectToWiFi();
    connectToMQTTBroker();
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
    }
}



void connectToWiFi() {

    // Attempt to connect to the WiFi network until a connection is established
    while(!WiFi.isConnected()) {
        displayText("Connecting to WiFi..", color565(243, 166, 18), color565(116, 1, 8));
        WiFi.begin(SSID, WIFI_PASSWORD);
        delay(2000);
    }

    // Display confirmation
    displayText("Connected!", color565(243, 166, 18), color565(116, 1, 8));
    delay(1500);
}