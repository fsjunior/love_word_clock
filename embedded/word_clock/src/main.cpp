#include "LedEngine.hpp"
#include "TextRenderer.hpp"
#include "ClockManager.hpp"
#include "Ticker.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFiManager.h>


/* NTP and Timezone stuff */
WiFiUDP ntpUDP;
NTPClient ntp_client(ntpUDP, "br.pool.ntp.org", 3600*-3, 60000);



/* Led stuff */
#define PIN D2
LedEngine led_engine(10, D2);
TextRenderer text_renderer(led_engine);
ClockManager clock_manager(text_renderer, ntp_client);
Ticker ticker([](){clock_manager.refresh();}, 1000, 0, MILLIS);


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

  //text_renderer.queue_text({Word::ZERO, Word::HORAS, Word::E, Word::QUARENTA}, Color(255, 0, 0));

  ntp_client.begin();
  ntp_client.update();  

  clock_manager.set_color(0, 0, 255);
}


void loop() {
  //ticker.update();
  clock_manager.refresh();
  led_engine.refresh();
  //Serial.println(ntp_client.getHours());
}

