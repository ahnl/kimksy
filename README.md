# Kimksy

~~Banksy's Girl with Balloon shredding artwork clone~~ Remote-controllable paper shredder. 

This Banksy inspired art piece was created in collaboration of Kimpisen lukio, Innoverstas, and some students from Lappeenrannan Lyseon lukio.

Our IoT paper shredder exposes a web server for controlling it and it is able to reconfigure its DDNS. An improvement could be made for our use case, to ditch the WiFi connectivity and use some ultra modern IR-technology for the remote control. We were out of supplies.

## Components

* ESP8266 board
* Two continuous rotation servos
* Buzzer

The pins can be configured in `Kimksy/Config.hpp`. Remember also to configure WiFi connection and optionally DDNS.
