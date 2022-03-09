#include <WiFiClient.h>

#include "Config.hpp"
#include "Servos.hpp"
#include "Network.hpp"

void setup() {
    // Initializing
    Servos::attach();
    pinMode(BUZZER_PIN, OUTPUT);
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
}

