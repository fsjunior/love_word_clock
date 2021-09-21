#include "LedEngine.hpp"
#include "TextRenderer.hpp"
#include "ClockRenderer.hpp"
#include "Ticker.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFiManager.h>

#define DEBUG

/* NTP and Timezone stuff */
WiFiUDP ntpUDP;
NTPClient ntp_client(ntpUDP, "br.pool.ntp.org", 3600*-3, 60000);



/* Led stuff */
#define PIN D2
LedEngine led_engine(15, D2);
TextRenderer text_renderer(led_engine);
ClockRenderer clock_manager(text_renderer);

void refresh_clockmanager() {

  static uint8_t hours = 0;
  static uint8_t minutes = 0;

  minutes+=5;

  if(minutes == 60) {
    minutes = 0;
    hours++;
  }
  if(hours == 24)
    hours = 0;
  
  clock_manager.refresh(hours, minutes);
}

Ticker ticker(refresh_clockmanager, 1000, 0, MILLIS);


void setup() 
{
#ifdef DEBUG
  Serial.begin(115200);
#endif  

  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");

  ntp_client.begin();
  ntp_client.update();  

  clock_manager.set_color(100, 0, 255);
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

