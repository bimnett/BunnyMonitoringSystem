#include "mqtt.h"
#include "utils.h" // Utility methods
#include "wifi.h" // WiFi client
#include "secrets.h" // Credential variables
#include "environment_sensor.h" // Environment collection methods


// Declare MQTT object
PubSubClient mqttClient;


// Setup MQTT connection to broker 
void connectToMQTTBroker() {

    // Display mqtt connection attempt
    displayText("Connecting to MQTT..", TFT_BLACK, BMS_ORANGE);


    // Configure PubSub client with property setters
    mqttClient.setClient(wifiClient);
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    mqttClient.connect(MQTT_CLIENT_ID); 
    mqttClient.setCallback(callback);
        
    
    // Display successful mqtt connection 
    if(!mqttClient.connected()) {

        displayText("MQTT connection failed.", TFT_BLACK, BMS_ORANGE);
    }

    // Display unsuccessful mqtt connection 
    else {

        displayText("MQTT connected!", TFT_BLACK, BMS_ORANGE);
    }

    delay(2000);
}


// Publish sensor data to MQTT broker
void publishSensorData() {

    char tempStr[10];
    char humStr[10];
    
    dtostrf(temperature, 4, 2, tempStr);
    dtostrf(humidity, 4, 2, humStr);
    
    mqttClient.publish("bms/environment/temperature", tempStr);
    mqttClient.publish("bms/environment/humidity", humStr);
}


// MQTT callback function; is called when a message is received. 
void callback(char* topic, byte* payload, unsigned int length) {

    char message[length];

    // Transform byte payload to a char array message 
    for(int i = 0; i < length; i++) {
        message[i] = payload[i];
    }

    // Display message
    displayText(message, TFT_BLACK, BMS_ORANGE);
}