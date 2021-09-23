#ifndef __LOVE_RENDERER__
#define __LOVE_RENDERER__

#include "BitFrameRenderer.hpp"
#include <etl/queue.h>
#include <etl/utility.h>


#define LOVE_QUEUE_SIZE 20

class LoveRenderer
{
private:    
    const unsigned long beggining = 1411786800;
    etl::queue<etl::pair<const BitFrame *, uint32_t>, LOVE_QUEUE_SIZE> queue;
    BitFrameRenderer& bitframe_renderer;
    
    void number_to_words(const int number, const BitFrame * singular, const BitFrame * plural);
public:
    LoveRenderer(BitFrameRenderer& bitframe_renderer);
    bool refresh();  

    void start(unsigned long epoch);
};


#endif /* __LOVE_RENDERER__ */