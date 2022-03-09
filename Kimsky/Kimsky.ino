#include <WiFiClient.h>

#include "Config.hpp"
#include "Servos.hpp"
#include "Network.hpp"

void setup() {
    Servos::attach();
    pinMode(BUZZER_PIN, OUTPUT);
    Serial.begin(115200);

    Network::connectWiFi();
    Network::Server::begin();
    Network::updateDdns();

    Serial.println("Ready");
}

void loop() {
    Network::server.handleClient();
}

