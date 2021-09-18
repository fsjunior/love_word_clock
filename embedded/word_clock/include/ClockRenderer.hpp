#ifndef __CLOCK_RENDERER__
#define __CLOCK_RENDERER__

#include "LedEngine.hpp"
#include <NTPClient.h>
#include "types.hpp"

class ClockRenderer
{
private:
    LedEngine& led_engine;
    NTPClient& ntp_client;

    
public:
    ClockRenderer(LedEngine& led_engine, NTPClient& ntp_client);
    void refresh();
};

#endif /* __CLOCK_RENDERER__ */
