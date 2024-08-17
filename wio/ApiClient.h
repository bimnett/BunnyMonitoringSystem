#ifndef api_client_h
#define api_client_h

#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFiClient.h>

class ApiClient {
  
public:

    ApiClient(const char* baseUrl, int port);
    bool sendTemperature(float temperature);
    bool sendHumidity(float humidity);

private:

    const char* _baseUrl;
    int _port;
    HTTPClient _http;
    WiFiClient _wifiClient;

    bool sendRequest(const char* endpoint, const char* paramName, float value);
};

#endif