#ifndef __TRANSITION_EFFECT__
#define __TRANSITION_EFFECT__

#include "types.hpp"
#include <functional>

typedef std::function<void(const Frame& frame)> QueueCallback;

//void transform(Frame &begin, Frame &end, int duration);
typedef std::function<void(const Frame& begin, const Frame& end, unsigned duration_in_frames, QueueCallback queue_callback)> TransitionCallback;


void no_transition(const Frame& begin, const Frame& end, unsigned duration_in_frames, QueueCallback queue_callback);

void fade_transition(const Frame& begin, const Frame& end, unsigned duration_in_frames, QueueCallback queue_callback);



#endif /* __TRANSITION_EFFECT__ */