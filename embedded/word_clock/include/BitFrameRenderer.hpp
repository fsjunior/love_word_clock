#ifndef __BITFRAME_RENDERER__
#define __BITFRAME_RENDERER__

#include "LedEngine.hpp"
#include "types.hpp"
#include <etl/vector.h>

#define MAX_WORDS 6

using BitFrame = etl::multi_array<char, SCREEN_WIDTH, SCREEN_HEIGHT>; // only store if the pixel is activate or not

namespace words {
	extern const BitFrame zero;
	extern const BitFrame um;
	extern const BitFrame uma;
	extern const BitFrame duas;
	extern const BitFrame tres;
	extern const BitFrame quatro;
	extern const BitFrame cinco_h;
	extern const BitFrame cinco_m;
	extern const BitFrame seis;
	extern const BitFrame sete;
	extern const BitFrame oito;
	extern const BitFrame nove;
	extern const BitFrame dez_h;
	extern const BitFrame dez_m;
	extern const BitFrame e_4;	
	extern const BitFrame onze;
	extern const BitFrame doze;
	extern const BitFrame hora;
	extern const BitFrame horas;
  	extern const BitFrame e_0;
	extern const BitFrame e_1;
	extern const BitFrame vinte;
	extern const BitFrame e_2;
	extern const BitFrame trinta;
	extern const BitFrame quarenta;
	extern const BitFrame cinquenta;
	extern const BitFrame e_3;
	extern const BitFrame amo_1;
	extern const BitFrame amo_2;
	extern const BitFrame ha;
	extern const BitFrame ano;
	extern const BitFrame anos;
	extern const BitFrame mes;
	extern const BitFrame meses;
	extern const BitFrame dia;
	extern const BitFrame dias;
	extern const BitFrame eu;
	extern const BitFrame te_1;
	extern const BitFrame te_2;
	extern const BitFrame dois;
	extern const BitFrame treze;
	extern const BitFrame quatorze;
	extern const BitFrame quinze;
	extern const BitFrame dezesseis;
	extern const BitFrame dezessete;
	extern const BitFrame dezoito;
	extern const BitFrame dezenove;
};

namespace draws {
	extern const BitFrame blank;
	extern const BitFrame heart;
}

class BitFrameRenderer
{
private:
    LedEngine& led_engine;
    uint32_t color;
public:
    BitFrameRenderer(LedEngine& led_engine);

    void set_color(uint8_t r, uint8_t g, uint8_t b);
    void queue_frame(etl::vector<const BitFrame *, MAX_WORDS>& words, uint32_t color = 0);
    void queue_frame(const BitFrame * word, uint32_t color = 0);
};

#endif /* __BITFRAME_RENDERER__ */
