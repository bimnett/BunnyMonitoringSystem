#include "rpcWiFi.h" // WiFi library
#include "secrets.h" // Hidden credentials
#include "utils.h" // Utility methods



void setup() {

    initializeTFTScreen();
    connectToWiFi();
}



void loop() {

    // Reconnect to WiFi if it disconnects
    if(!WiFi.isConnected()) {

        connectToWiFi();
    }
}



void connectToWiFi() {

    // Attempt to connect to the WiFi network until a connection is established
    while(!WiFi.isConnected()) {
        displayText("Connecting to WiFi..", color565(243, 166, 18), color565(116, 1, 8));
        WiFi.begin(SSID, WIFI_PASSWORD);
        delay(2000);
    }

    // Display confirmation
    displayText("Connected!", color565(243, 166, 18), color565(116, 1, 8));
}