#include "LedEngine.hpp"


LedEngine::LedEngine(unsigned fps, int pin):fps(fps), strip(Adafruit_NeoPixel(144, pin, NEO_RGB + NEO_KHZ800)), last_frame({{0}})
{
	time_delay = (1.0 / (float)fps) * 1000000.0;
	strip.begin();
	strip.setBrightness(50);
	strip.show();
}

void LedEngine::queue(const Frame& frame, TransitionEffect transition_effect)
{
	frame_buffer.clear();
	QueueCallback q = [&](const Frame& frame) -> void {frame_buffer.push(frame);};
	transition_effect(last_frame, frame, fps, q);
	last_frame = frame;	
}


void LedEngine::refresh()
{
	static uint16_t address;
	static unsigned long next_time = micros() + time_delay;

	if (frame_buffer.empty())
		return;

	Frame &frame = frame_buffer.front();

	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			if (i % 2 == 0)
				address = i * 12 + 11 - j;
			else
				address = i * 12 + j;

			strip.setPixelColor(address, frame[i][j]);
		}
	}

	frame_buffer.pop();

	/* Calc sleep time */
	unsigned long actual_time = micros();
	unsigned long diff_time = next_time - actual_time;
	if ((diff_time > 0) && (next_time > actual_time))
		delayMicroseconds(diff_time);

	strip.show();
	next_time = micros() + time_delay;
}


