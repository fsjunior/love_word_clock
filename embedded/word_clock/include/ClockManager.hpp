#ifndef __CLOCK_MANAGER__
#define __CLOCK_MANAGER__

#include "TextRenderer.hpp"
#include <NTPClient.h>

class ClockManager
{
private:
    TextRenderer& text_renderer;
    NTPClient& ntp_client;
    uint32_t color;
public:
    ClockManager(TextRenderer& text_renderer, NTPClient& ntp_client);
    void refresh();

    void set_color(uint8_t r, uint8_t g, uint8_t b);
};


#endif /* __CLOCK_MANAGER__ */