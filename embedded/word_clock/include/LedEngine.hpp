#ifndef __LED_ENGINE__
#define __LED_ENGINE__

#include <Adafruit_NeoPixel.h>
#include "types.hpp"
#include <etl/queue.h>
//#include <queue>
#include "TransitionEffect.hpp"


class LedEngine 
{
private:
    unsigned long time_delay;
    unsigned fps;
    Adafruit_NeoPixel strip;

    etl::queue<Frame, 30> frame_buffer;
    Frame last_frame;

    
public:
    LedEngine(unsigned fps, int pin);
    void queue(const Frame& frame, bool clear_buffer, TransitionCallback transition_callback);
    void refresh();
};

#endif /* __LED_ENGINE__ */
