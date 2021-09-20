#ifndef __LED_ENGINE__
#define __LED_ENGINE__

#include <Adafruit_NeoPixel.h>
#include "types.hpp"
#include <queue>
#include "TransitionEffect.hpp"


class LedEngine 
{
private:
    unsigned long time_delay;
    unsigned fps;
    Adafruit_NeoPixel strip;

    std::queue<Frame> frame_buffer;
    Frame last_frame;

    
public:
    LedEngine(unsigned fps, int pin);
    void queue(const Frame& frame);
    void queue(const Frame& frame, TransitionCallback transition_callback);
    void refresh();
};

#endif /* __LED_ENGINE__ */
