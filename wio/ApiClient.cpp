#include "ApiClient.h"


ApiClient::ApiClient(const char* baseUrl, int port) : _baseUrl(baseUrl), _port(port) {}


bool ApiClient::sendTemperature(float temperature) {
    return sendRequest("/api/environment/temperature/history", "temperature", temperature);
}


bool ApiClient::sendHumidity(float humidity) {
    return sendRequest("/api/environment/humidity/history", "humidity", humidity);
}


bool ApiClient::sendRequest(const char* endpoint, const char* paramName, float value) {

    // Create full url for API endpoint
    String url = String(_baseUrl) + ":" + String(_port) + endpoint;
    
    // Start HTTP request and specify header info
    _http.begin(_wifiClient, url);
    _http.addHeader("Content-Type", "application/json");

    // Create payload body to send to database
    String payload = "{\"" + String(paramName) + "\":" + String(value, 2) + "}";
    
    int httpResponseCode = _http.POST(payload);
    
    bool success = (httpResponseCode > 0 && httpResponseCode < 300);
    
    _http.end();
    
    return success;
}