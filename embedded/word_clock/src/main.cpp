#include "LedEngine.hpp"

#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFiManager.h>


/* NTP and Timezone stuff */
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "br.pool.ntp.org", 3600*-3, 60000);



/* Led stuff */
#define PIN D2
LedEngine led_engine(2, D2);


static uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)g << 16) | ((uint32_t)r <<  8) | b;
}

void wipe(uint32_t color) {
  Frame frame;
    for(int i = 0; i < SCREEN_WIDTH; i++) {
      for(int j = 0; j < SCREEN_HEIGHT; j++) {
          frame[i][j] = color;
      }
    }
    led_engine.queue(frame);
}

void setup() 
{
  Serial.begin(115200);

  WiFiManager wifiManager;
  //wifiManager.resetSettings();
  wifiManager.autoConnect("AutoConnectAP");

  timeClient.begin();
  timeClient.update();  
}


void loop() {
  led_engine.refresh();
  Serial.println(timeClient.getHours());
}

