#pragma once

#include "ESP8266WiFi.h"
#include <ESP8266HTTPClient.h>
#include "ESP8266WebServer.h"

#include "Config.hpp"
#include "Control.hpp"

namespace Network {
    ESP8266WebServer server(80);

    void connectWiFi() {
        WiFi.begin(WIFI_SSID); 
        while (WiFi.status() != WL_CONNECTED) { 
            delay(500);
            Serial.println("Waiting to connect…");
        }
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP()); 
    }

    namespace Server {
        void handleApiHalt() {
            server.send(200, "text/plain", "Halttista :D");
            Control::halt();
        }

        void handleApiShred() {
            server.send(200, "text/plain", "Abrakadabra");
            Control::shred();
        }

        void handleRootPath() {   
            server.send(200, "text/html", "<meta name='viewport' content='width=device-width, initial-scale=1.0'><meta charset='utf-8'><style>button{-webkit-appearance: none;flex:1;font-size: 3rem;background:#663333;font-weight:bold;cursor:pointer;color:beige;font-family: sans-serif;}button:hover{background-color:#996600;}body{display:flex;flex-direction: column;max-width: 800px;margin: 0 auto;}</style>"
                        "<button data-action='shred'>Silppuroi!</button>"
                        "<button data-action='halt'>Hätä seis</button>"
                        "<button data-action='reverse'>Revöörs</button>"
                        "<script>document.addEventListener(\"click\", (e) => {if(e.target.dataset.action){fetch(\"/api/\"+e.target.dataset.action)}})</script>");
        }

        void begin() {
            server.on("/", handleRootPath);
            server.on("/api/shred", handleApiShred);
            server.on("/api/halt", handleApiHalt);
            server.begin(); 
        }
    }

    // Sends a GET request DDNS_ENDPOINT/?q=MYIP to update DDNS configurations
    void updateDdns() {
        String myip = WiFi.localIP().toString();

        WiFiClient client;
        HTTPClient http;

        if (http.begin(client, DDNS_ENDPOINT + myip)) { 
            int httpCode = http.GET();
            if (httpCode > 0) {
                if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
                    String payload = http.getString();
                    Serial.println(payload);
                }
            } else {
                Serial.printf("[DDNS] GET failed, error: %s\n", http.errorToString(httpCode).c_str());
            }
            http.end();
        } else {
            Serial.printf("[DDNS] Unable to connect\n");
        }
    }
}