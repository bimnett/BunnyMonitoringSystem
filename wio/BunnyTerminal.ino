#include "wifi.h" // WiFi methods
#include "utils.h" // Utility methods
#include "mqtt.h" // MQTT methods
#include "environment_sensor.h" // Temperature and Humidity methods
#include "secrets.h" // API endpoint addresses
#include "ApiClient.h" // HTTP requests to API server


ApiClient apiClient(serverAddress, serverPort); // Client to send HTTP requests


unsigned long previousSensorReadingMillis = 0; // Store previous time that temperature and humidity were read
const long sensorReadInterval = 5000; // Temperature & Humidity reading interval


unsigned long previousSensorDataDBMillis = 360000; // Store previous time that temperature and humidity data were sent to database
const long sensorDataDBSendInterval = 3600000; // 1 hour interval for sending sensor data to database


void setup() {

    Serial.begin(38400);
    initializeTFTScreen();
    connectToWiFi();
    connectToMQTTBroker();
    initializeTempHumiSensor();
    drawDashboard();
}



void loop() {

    // Reconnect to WiFi if disconnected
    if(!WiFi.isConnected()) {

        Serial.println("Reconnecting to WiFi...");
        connectToWiFi();
        drawDashboard();
    }


    // Reconnect to MQTT broker if disconnected
    if(!mqttClient.loop()) {

        Serial.println("Reconnecting to MQTT...");
        connectToMQTTBroker();
        drawDashboard();
    }


    unsigned long currentMillis = millis();

    // Check if sensor reading interval has passed
    if (currentMillis - previousSensorReadingMillis >= sensorReadInterval) {

        // Save timestamp for previous sensor reading
        previousSensorReadingMillis = currentMillis;

        // Read temperature and humidity
        Serial.println("Attempting to read and display env data.");
        readAndDisplayTemperatureAndHumidity();

        // Publish sensor data to MQTT broker
        Serial.println("Publishing env data to mqtt broker...");
        publishSensorData();
    }


    if (currentMillis - previousSensorDataDBMillis >= sensorDataDBSendInterval) {

        // Send temperature to API server, max retries is 5
        for(int i = 1; i <= 5; i++) {

          if(!WiFi.isConnected()) {

            connectToWiFi();
          }

          int exponentialDelay = (String(i) + "000").toInt();

          Serial.println("Attempt " + String(i) + " to send temperature to database..");

          if(apiClient.sendTemperature(temperature)) {

            Serial.println("Temperature sent successfully");
            break;
          }

          Serial.println("Failed to send temperature.");
          delay(5000);
        }
        

        // Send humidity to API server, max retries is 5
        for(int i = 1; i <= 5; i++) {

          if(!WiFi.isConnected()) {

            connectToWiFi();
          }

          int exponentialDelay = (String(i) + "000").toInt();

          Serial.println("Attempt " + String(i) + " to send humidity to database..");

          if(apiClient.sendHumidity(humidity)) {

            Serial.println("Humidity sent successfully");
            break;
          }

          Serial.println("Failed to send humidity.");
          delay(5000 + exponentialDelay);
        }

        // Save current timestamp for latest API server post requests
        previousSensorDataDBMillis = millis();
    }
}