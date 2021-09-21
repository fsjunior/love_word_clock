#ifndef __CLOCK_MANAGER__
#define __CLOCK_MANAGER__

#include "TextRenderer.hpp"

class ClockRenderer
{
private:
    TextRenderer& text_renderer;
    uint32_t color;
public:
    ClockRenderer(TextRenderer& text_renderer);
    void refresh(int hours, int minutes);

    void set_color(uint8_t r, uint8_t g, uint8_t b);
};


#endif /* __CLOCK_MANAGER__ */