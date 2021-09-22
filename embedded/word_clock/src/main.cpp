#include "LedEngine.hpp"
#include "TextRenderer.hpp"
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
TextRenderer text_renderer(led_engine);
ClockRenderer clock_renderer(text_renderer);
LoveRenderer love_renderer(text_renderer);

void clock_manager() {

  static uint8_t hours = 0;
  static uint8_t minutes = 0;

  minutes+=5;

  if(minutes == 60) {
    minutes = 0;
    hours++;
  }
  if(hours == 24)
    hours = 0;
  
  clock_renderer.refresh(hours, minutes);
  //love_renderer.refresh(ntp_client.getEpochTime());
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

  text_renderer.set_color(100, 0, 255);

  love_renderer.start();

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

