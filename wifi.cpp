#include "rpcWiFi.h" // WiFi library
#include "secrets.h" // WiFi credentials
#include "utils.h" // Utility methods


WiFiClient wifiClient;


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