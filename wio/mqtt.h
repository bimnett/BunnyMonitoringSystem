#ifndef mqtt_h
#define mqtt_h


#include <PubSubClient.h> // MQTT library
#include "rpcWiFiClient.h" // WiFi library


extern PubSubClient mqttClient;
extern WiFiClient wifiClient;


// MQTT method signatures
void connectToMQTTBroker();
void callback(char* topic, byte* payload, unsigned int length);


#endif