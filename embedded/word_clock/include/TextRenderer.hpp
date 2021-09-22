#ifndef __TEXT_RENDERER__
#define __TEXT_RENDERER__

#include "LedEngine.hpp"
#include "types.hpp"
#include <etl/vector.h>

#define MAX_WORDS 6

enum class Word {
    ZERO,
    UM,
    UMA,
    DUAS,
    TRES,
    QUATRO,
    CINCO_H,
    SEIS,
    SETE,
    OITO,
    NOVE,
    DEZ_H,
    ONZE,
    DOZE,
    HORAS,
    HORA,
    E_0, 
    E_1,
    CINCO_M,
    DEZ_M,
    E_4,            
    QUINZE,
    VINTE,
    E_2,
    TRINTA,
    QUARENTA,
    CINQUENTA,
    E_3,        
    AMO,
    HA,
    ANOS,
    MESES,
    DIAS,
    EU,
    TE,
    DOIS,
    TREZE,
    QUATORZE,
    DEZESSEIS,
    DEZESSETE,
    DEZOITO,
    DEZENOVE,
};

class TextRenderer
{
private:
    LedEngine& led_engine;
    uint32_t color;
public:
    TextRenderer(LedEngine& led_engine);

    void set_color(uint8_t r, uint8_t g, uint8_t b);
    void queue_text(etl::vector<Word, MAX_WORDS>& words);
};

#endif /* __TEXT_RENDERER__ */
