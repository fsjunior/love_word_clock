#ifndef __CLOCK_RENDERER__
#define __CLOCK_RENDERER__

#include "TextRenderer.hpp"

class ClockRenderer
{
private:
    TextRenderer& text_renderer;
public:
    ClockRenderer(TextRenderer& text_renderer);
    void refresh(uint8_t hours, uint8_t minutes);
};


#endif /* __CLOCK_RENDERER__ */