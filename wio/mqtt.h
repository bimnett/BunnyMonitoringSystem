#ifndef mqtt_h
#define mqtt_h


#include <PubSubClient.h> // MQTT library


extern PubSubClient mqttClient;


// MQTT method signatures
void connectToMQTTBroker();
void callback(char* topic, byte* payload, unsigned int length);
void publishSensorData();


#endif