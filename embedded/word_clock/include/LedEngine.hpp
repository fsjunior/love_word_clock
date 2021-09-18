#ifndef __LED_ENGINE__
#define __LED_ENGINE__

#include <Adafruit_NeoPixel.h>
#include "types.hpp"
#include <queue>



class LedEngine 
{
private:
    unsigned long time_delay;
    Adafruit_NeoPixel strip;

    std::queue<Frame> frame_buffer;

    
public:
    LedEngine(int fps, int pin);
    void queue(const Frame& frame);
    void refresh();
};

#endif /* __LED_ENGINE__ */
