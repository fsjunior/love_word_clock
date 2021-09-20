#ifndef __CLOCK_RENDERER__
#define __CLOCK_RENDERER__

#include "LedEngine.hpp"
#include "types.hpp"
#include <vector>

enum class Word {
    ZERO,
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
public:
    TextRenderer(LedEngine& led_engine);
    void queue_text(std::vector<Word>& words, uint32_t color);
};

#endif /* __CLOCK_RENDERER__ */
