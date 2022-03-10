# Kimksy

~~Banksy's Girl with Balloon shredding artwork clone~~ Remote-controllable paper shredder. 

This Banksy inspired art piece was created in collaboration of Kimpisen lukio, Innoverstas, and some students from Lappeenrannan Lyseon lukio.

Our IoT paper shredder exposes a web server for controlling it and it is able to reconfigure its DDNS. An improvement could be made for our use case, to ditch the WiFi connectivity and use some ultra modern IR-technology for the remote control. We were out of supplies.

## Components

* ESP8266 board
* Two continuous rotation servos
* Buzzer

The pins can be configured in `Kimksy/Config.hpp`. Remember also to configure WiFi connection and optionally DDNS.

## DDNS

We have set up our DDNS server using Pipedream workflows. It receives the device's IP address by a GET request and updates it into Cloudflare's DNS record.

Live Kimksy can be accessed at http://kimksy.vety.xyz (works only in the nearby LAN).

[Our DDNS server setup (via Pipedream)](https://pipedream.com/@ahnl/kimksy-ddns-p_13CWypy)

## Troubleshooting

### How to get an IP address
Connect the device to your computer and open serial monitor at baud rate 115200. Press the reset button on the device, and the device will print its IP address once a WiFi connection is established.

