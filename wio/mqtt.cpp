#include "mqtt.h"
#include "utils.h" // Utility methods



void connectToMQTTBroker() {

    displayText("Connecting to MQTT..", color565(243, 166, 18), color565(116, 1, 8));


    // Configure PubSub client with property setters
    mqttClient.setClient(wifiClient);
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    mqttClient.connect(MQTT_CLIENT_ID); 
    mqttClient.setCallback(callback);
        
    
    if(!mqttClient.connected()) {

        displayText("MQTT connection failed.", color565(243, 166, 18), color565(116, 1, 8));
    }

    else {

        displayText("MQTT connected!", color565(243, 166, 18), color565(116, 1, 8));
    }

    delay(2000);
}



// MQTT callback function; is called when a message is received. 
void callback(char* topic, byte* payload, unsigned int length) {

    char message[length];

    // Transform byte payload to a char array message 
    for(int i = 0; i < length; i++) {
        message[i] = payload[i];
    }

    // Display message
    displayText(message, color565(243, 166, 18), color565(116, 1, 8));
}