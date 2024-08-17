#include "rpcWiFi.h" // WiFi library
#include "secrets.h" // WiFi credentials
#include "utils.h" // Utility methods


WiFiClient wifiClient;


// Connect to WiFi
void connectToWiFi() {

    setTextSettings(BMS_ORANGE, TFT_BLACK, 2);


    // Attempt to connect to the WiFi network until a connection is established
    while(!WiFi.isConnected()) {

        // Display WiFi connection attempt
        displayText("Connecting to WiFi..", TFT_BLACK, BMS_ORANGE);
        Serial.println("Connecting to WiFi...");

        // Attempt WiFi connection
        WiFi.begin(SSID, WIFI_PASSWORD);

        // 2 second cooldown if WiFi connection was unsuccessful
        if(!WiFi.isConnected()) {

          Serial.println("WiFi connection failed.");
          delay(2000);
        }
    }

    // Display confirmation
    displayText("WiFi Connected!", TFT_BLACK, BMS_ORANGE);
    Serial.println("WiFi Connected.");
    delay(1500);
}