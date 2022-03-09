#include <WiFiClient.h>

#include "Config.hpp"
#include "Control.hpp"
#include "Network.hpp"

void setup() {
    // Initializing
    Control::init();
    Serial.begin(115200);

    // Start networking
    Network::connectWiFi();
    Network::Server::begin();
    Network::updateDdns();

    Serial.println("Ready");
}

void loop() {
    // HTTP server loop
    Network::server.handleClient();

    // Servo and sound loop
    Control::loop();
}

