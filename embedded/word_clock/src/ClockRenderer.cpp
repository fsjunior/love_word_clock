#include "ClockRenderer.hpp"
#include <array>

ClockRenderer::ClockRenderer(LedEngine &led_engine, NTPClient &ntp_client) : led_engine(led_engine), ntp_client(ntp_client)
{
}