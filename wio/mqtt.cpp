#include "mqtt.h"
#include "utils.h" // Utility methods
#include "wifi.h" // WiFi client
#include "secrets.h" // Credential variables
#include "environment_sensor.h" // Environment collection methods


// Declare MQTT object
PubSubClient mqttClient;


// Setup MQTT connection to broker 
void connectToMQTTBroker() {

    setTextSettings(BMS_ORANGE, TFT_BLACK, 2);


    // Configure PubSub client with property setters
    mqttClient.setClient(wifiClient);
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    mqttClient.setCallback(callback);
        
    while(!mqttClient.connected()) {

      // Ensure WiFi connection is established before attempting mqtt connection
      if(!WiFi.isConnected()) {

        Serial.println("WiFi connection lost.");
        connectToWiFi();
      }

      mqttClient.disconnect();

      // Display mqtt connection attempt
      displayText("Connecting to MQTT..", TFT_BLACK, BMS_ORANGE);
      Serial.println("Connecting to MQTT..");
      delay(2000);

      // Attempt mqtt connection
      mqttClient.connect(MQTT_CLIENT_ID); 

      // Display unsuccessful mqtt connection if not connected, and delay before next attempt
      if(!mqttClient.connected()) {

        displayText("MQTT connection failed.", TFT_BLACK, BMS_ORANGE);
        Serial.println("MQTT connection failed.");
        delay(5000);
      }
    }
    
    // Display successful mqtt connection
    displayText("MQTT connected!", TFT_BLACK, BMS_ORANGE);
    Serial.println("MQTT connected!");
    delay(1500);
}


// Publish sensor data to MQTT broker
void publishSensorData() {

    char tempStr[10];
    char humStr[10];
    
    // Convert temp/humi from float to char arrays
    dtostrf(temperature, 4, 1, tempStr);
    dtostrf(humidity, 4, 1, humStr);
    
    mqttClient.publish("bms/environment/temperature", tempStr);
    mqttClient.publish("bms/environment/humidity", humStr);
}


// MQTT callback function; called when a message is received. 
void callback(char* topic, byte* payload, unsigned int length) {

}