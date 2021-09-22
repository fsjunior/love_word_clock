#ifndef __TRANSITION_EFFECT__
#define __TRANSITION_EFFECT__

#include "types.hpp"
#include <functional>

using QueueCallback = std::function<void(const Frame& frame)>;

//void transform(Frame &begin, Frame &end, int duration);
using TransitionEffect = std::function<void(const Frame& begin, const Frame& end, unsigned duration_in_frames, QueueCallback queue_callback)>;


void no_transition(const Frame& begin, const Frame& end, unsigned duration_in_frames, QueueCallback queue_callback);

void fade_transition(const Frame& begin, const Frame& end, unsigned duration_in_frames, QueueCallback queue_callback);



#endif /* __TRANSITION_EFFECT__ */