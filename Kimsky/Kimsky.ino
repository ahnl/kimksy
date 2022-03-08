#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"

#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <Servo.h>

#define SERVO_A_PIN D1
#define SERVO_A_STOP 1450

#define SERVO_B_PIN D2
#define SERVO_B_STOP 1400
#define BUZZER_PIN D3

#define WIFI_SSID "Mediakeskus"

ESP8266WebServer server(80);

Servo servoA;
Servo servoB; 
        
void setup() {
  pinMode(BUZZER_PIN, OUTPUT);

  servoA.attach(SERVO_A_PIN);
  servoB.attach(SERVO_B_PIN);

            servoA.writeMicroseconds(SERVO_A_STOP);
            servoB.writeMicroseconds(SERVO_B_STOP);

  Serial.begin(115200);

  // WiFi connection
  WiFi.begin(WIFI_SSID); 
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.println("Waiting to connect…");
  }
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); 

  // HTTP server
  server.on("/", handleRootPath);
  server.on("/api/full", handleApiOn);
  server.on("/api/halt", handleApiHalt);
  server.begin(); 

  Serial.println("Server listening");

  ddnsUpdate(WiFi.localIP().toString());
}

bool halt = false;

void handleApiHalt() {
  server.send(200, "text/plain", "Halttista :D");
  
  servoA.detach();
  servoB.detach();
  halt = true;
  tone(BUZZER_PIN, 500, 1700);
  delay(1700);
  noTone(BUZZER_PIN);
  halt = false;

  servoA.attach(SERVO_A_PIN);
  servoB.attach(SERVO_B_PIN);
  servoA.write(SERVO_A_STOP);
  servoB.write(SERVO_B_STOP);
}

void handleApiOn() {
  server.send(200, "text/plain", "Abrakadabra");

  servoA.write(0);
  servoB.write(3000);

  for (int i = 0; i <= 18; i++) {

    tone(BUZZER_PIN, 500, 450);
    delay(900);
    if (halt == true) {
      break;
    }
  }


  servoA.write(SERVO_A_STOP);
  servoB.write(SERVO_B_STOP);


  Serial.println("NYT RULLATAAAN!!!");
}

void ddnsUpdate(String myip) {
  WiFiClient client;

  HTTPClient http;

  Serial.print("[HTTP] begin...\n");
  if (http.begin(client, "http://c7b0c18f326ed206a0d833c658e9140c.m.pipedream.net/?myip=" + myip)) {  // HTTP

    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.printf("[HTTP} Unable to connect\n");
  }
}
void loop() {

  server.handleClient();         //Handling of incoming requests

}



void handleRootPath() {            //Handler for the rooth path

  server.send(200, "text/html", "<meta name='viewport' content='width=device-width, initial-scale=1.0'><meta charset='utf-8'><style>button{-webkit-appearance: none;flex:1;font-size: 3rem;background:#663333;font-weight:bold;cursor:pointer;color:beige;font-family: sans-serif;}button:hover{background-color:#996600;}body{display:flex;flex-direction: column;max-width: 800px;margin: 0 auto;}</style>"
              "<button data-action='full'>Silppuroi!</button>"
              "<button data-action='halt'>Hätä seis</button>"
              "<button data-action='reverse'>Revöörs</button>"
              "<script>document.addEventListener(\"click\", (e) => {if(e.target.dataset.action){fetch(\"/api/\"+e.target.dataset.action)}})</script>");

}
