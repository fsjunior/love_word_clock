#include "Configurator.hpp"
#include <FS.h>
#include <LittleFS.h>

Configurator::Configurator(BitFrameRenderer& bitframe_renderer, NTPClient& ntp_client): bitframe_renderer(bitframe_renderer), ntp_client(ntp_client)
{

}

void Configurator::load_time_offset()
{
    File f = LittleFS.open("/offset.txt", "r");
    int8_t offset = -3;

    if(f) {    
        f.readBytes((char *)&offset, sizeof(offset));
        f.close();
    }

    set_time_offset(offset);
}


void Configurator::store_time_offset(const int8_t offset)
{
    File f = LittleFS.open("/offset.txt", "w");

    if(f) {    
        f.write((char *)&offset, sizeof(offset));
        f.close();
    }

    set_time_offset(offset);
}

void Configurator::load_color()
{
    File f = LittleFS.open("/default_color.txt", "r");
    uint8_t r = 100;
    uint8_t g = 0;
    uint8_t b = 255;

    if(f) {    
        f.readBytes((char *)&r, sizeof(r));
        f.readBytes((char *)&g, sizeof(g));
        f.readBytes((char *)&b, sizeof(b));
        f.close();
    }

    set_color(r, g, b);
}

void Configurator::store_color(const uint8_t r, const uint8_t g, const uint8_t b)
{
    File f = LittleFS.open("/default_color.txt", "w");

    if(f) {    
        f.write((char *)&r, sizeof(r));
        f.write((char *)&g, sizeof(g));
        f.write((char *)&b, sizeof(b));
        f.close();
    }

    set_color(r, g, b);
}


void Configurator::set_time_offset(const int8_t offset)
{
    ntp_client.setTimeOffset(3600*offset);
}

void Configurator::set_color(const uint8_t r, const uint8_t g, const uint8_t b)
{
    bitframe_renderer.set_default_color(r, g, b);
}


void Configurator::get_color(uint8_t& r, uint8_t& g, uint8_t& b)
{
    File f = LittleFS.open("/default_color.txt", "r");
    r = 100;
    g = 0;
    b = 255;

    if(f) {    
        f.readBytes((char *)&r, sizeof(r));
        f.readBytes((char *)&g, sizeof(g));
        f.readBytes((char *)&b, sizeof(b));
        f.close();
    }
}


int8_t Configurator::get_time_offset()
{
    File f = LittleFS.open("/offset.txt", "r");
    int8_t offset = -3;

    if(f) {    
        f.readBytes((char *)&offset, sizeof(offset));
        f.close();
    }

    return offset;
}