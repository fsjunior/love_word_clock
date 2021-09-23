#include "LedEngine.hpp"
#include "BitFrameRenderer.hpp"
#include "ClockRenderer.hpp"
#include "LoveRenderer.hpp"
#include "RESTServer.hpp"
#include "Configurator.hpp"

#include <Ticker.h>
#include <ESP8266mDNS.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESPAsyncWiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <LittleFS.h>


//#define DEBUG

#define FPS 15

/* Server and autoconnect */
AsyncWebServer server(80);
DNSServer dns;

/* NTP and Timezone stuff */
WiFiUDP ntpUDP;
NTPClient ntp_client(ntpUDP, "br.pool.ntp.org", 3600*-3, 60000);


/* Led stuff */
#define PIN D2
LedEngine led_engine(FPS, D2);
BitFrameRenderer bitframe_renderer(led_engine);
ClockRenderer clock_renderer(bitframe_renderer);
LoveRenderer love_renderer(bitframe_renderer);

bool love_mode = false;

void clock_manager() {
  static uint8_t hours = 0;
  static uint8_t minutes = 0;

  hours = ntp_client.getHours();
  minutes = ntp_client.getMinutes();

  if(!love_mode && random(3600) == 0) {
    love_mode = true;
    love_renderer.start(ntp_client.getEpochTime());
  }
  
  if(love_mode)
    love_mode = love_renderer.refresh();
  else
    clock_renderer.refresh(hours, minutes);  
}

Ticker ticker(clock_manager, 1000, 0, MILLIS);


/* Config */
Configurator configurator(bitframe_renderer, ntp_client);
RESTServer rest_server(server, configurator);

void setup() 
{
#ifdef DEBUG
  Serial.begin(115200);
#endif  

  AsyncWiFiManager wifiManager(&server, &dns);
  wifiManager.autoConnect("AutoConnectAP");

  MDNS.begin("love");

  LittleFS.begin();
  configurator.load_time_offset();

  rest_server.begin();

  ntp_client.begin();
  ntp_client.update();  

  randomSeed(ntp_client.getEpochTime());

  if(random(10) == 0) {
    love_renderer.start(ntp_client.getEpochTime());
    love_mode = true;
  }

  configurator.load_color();

  ticker.start();  
}


void loop() {
  MDNS.update();  
  ticker.update();
  led_engine.refresh();
// #ifdef DEBUG  
//   Serial.print("Loop ");
//   Serial.println(ESP.getFreeHeap());
// #endif
}

