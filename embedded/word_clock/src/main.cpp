#include "LedEngine.hpp"
#include "BitFrameRenderer.hpp"
#include "ClockRenderer.hpp"
#include "LoveRenderer.hpp"
#include "Ticker.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFiManager.h>

#define DEBUG

#define FPS 15

/* NTP and Timezone stuff */
WiFiUDP ntpUDP;
NTPClient ntp_client(ntpUDP, "br.pool.ntp.org", 3600*-3, 60000);



/* Led stuff */
#define PIN D2
LedEngine led_engine(FPS, D2);
BitFrameRenderer bitframe_renderer(led_engine);
ClockRenderer clock_renderer(bitframe_renderer);
LoveRenderer love_renderer(bitframe_renderer);

void clock_manager() {
  static bool love_mode = true;
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


void setup() 
{
#ifdef DEBUG
  Serial.begin(115200);
#endif  

  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");

  ntp_client.begin();
  ntp_client.update();  

  bitframe_renderer.set_color(100, 0, 255);
  love_renderer.start(ntp_client.getEpochTime());

  randomSeed(ntp_client.getEpochTime());
  ticker.start();  
}


void loop() {
  ticker.update();
  led_engine.refresh();
#ifdef DEBUG  
  Serial.print("Loop ");
  Serial.println(ESP.getFreeHeap());
#endif
}

