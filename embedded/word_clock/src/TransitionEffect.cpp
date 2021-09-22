#include "TransitionEffect.hpp"


void dummy_transition(const Frame& begin, const Frame& end, unsigned duration_in_frames, QueueCallback queue_callback)
{
    queue_callback(end);
}

#define GET_R(X) ((X >> 8) & 0xFF)
#define SET_R(X) ((uint32_t)(X) << 8)

#define GET_G(X) ((X >> 16) & 0xFF)
#define SET_G(X) ((uint32_t)(X) << 16)

#define GET_B(X) (X & 0xFF)
#define SET_B(X) (uint32_t)(X)


void fade_transition(const Frame& begin, const Frame& end, unsigned duration_in_frames, QueueCallback queue_callback)
{
    for(unsigned i = 0; i < duration_in_frames; i++) {
        Frame frame;
        for(int j = 0; j < SCREEN_WIDTH; j++) 
            for(int k = 0; k < SCREEN_HEIGHT; k++) {
                float begin_percent = (float)(duration_in_frames-i)/duration_in_frames;
                float end_percent = (float)i/duration_in_frames;

                frame[j][k] = SET_R(GET_R(end[j][k]) * end_percent + GET_R(begin[j][k]) * begin_percent)
                            | SET_G(GET_G(end[j][k]) * end_percent + GET_G(begin[j][k]) * begin_percent)
                            | SET_B(GET_B(end[j][k]) * end_percent + GET_B(begin[j][k]) * begin_percent);
            }
        queue_callback(frame);
    }
    queue_callback(end);
}