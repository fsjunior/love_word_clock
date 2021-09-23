#ifndef __CONFIG__
#define __CONFIG__

#include "BitFrameRenderer.hpp"
#include <NTPClient.h>

#include <stdint.h>


class Configurator
{
private:
    BitFrameRenderer& bitframe_renderer;
    NTPClient& ntp_client;
    void set_time_offset(const int8_t offset);
    void set_color(const uint8_t r, const uint8_t g, const uint8_t b);
public:
    Configurator(BitFrameRenderer& bitframe_renderer, NTPClient& ntp_client);

    void load_time_offset();
    void store_time_offset(const int8_t offset);
    int8_t get_time_offset();

    void load_color();
    void store_color(const uint8_t r, const uint8_t g, const uint8_t b);
    void get_color(uint8_t& r, uint8_t& g, uint8_t& b);

};

#endif /* __CONFIG__ */
