#ifndef __CLOCK_RENDERER__
#define __CLOCK_RENDERER__

#include "BitFrameRenderer.hpp"

class ClockRenderer
{
private:
    BitFrameRenderer& bitframe_renderer;
public:
    ClockRenderer(BitFrameRenderer& bitframe_renderer);
    void refresh(uint8_t hours, uint8_t minutes);
};


#endif /* __CLOCK_RENDERER__ */