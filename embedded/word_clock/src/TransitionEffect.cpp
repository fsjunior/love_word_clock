#include "TransitionEffect.hpp"
#include "HardwareSerial.h"


void dummy_transition(const Frame& begin, const Frame& end, unsigned duration_in_frames, QueueCallback queue_callback)
{
    for(unsigned i = 0; i < duration_in_frames; i++) {
        queue_callback(end);
    }
}


void fade_transition(const Frame& begin, const Frame& end, unsigned duration_in_frames, QueueCallback queue_callback)
{
    for(unsigned i = 0; i < duration_in_frames; i++) {
        Frame frame;
        for(int j = 0; j < SCREEN_WIDTH; j++) 
            for(int k = 0; k < SCREEN_HEIGHT; k++) {
                frame[j][k] = (end[j][k] * (float)i/duration_in_frames) + (begin[j][k] * (float)(duration_in_frames-i)/duration_in_frames);
            }
        queue_callback(frame);
    }
    queue_callback(end);
}