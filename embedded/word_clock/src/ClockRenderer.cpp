#include "ClockRenderer.hpp"
#include <etl/vector.h>
#include <unordered_map>

ClockRenderer::ClockRenderer(BitFrameRenderer& bitframe_renderer): bitframe_renderer(bitframe_renderer)
{

}

const std::unordered_map<int, const BitFrame *> hours_map = {
    {0, &words::zero},
    {1, &words::uma},
    {2, &words::duas},
    {3, &words::tres},
    {4, &words::quatro},
    {5, &words::cinco_h},
    {6, &words::seis},
    {7, &words::sete},
    {8, &words::oito},
    {9, &words::nove},
    {10, &words::dez_h},
    {11, &words::onze},
    {12, &words::doze},
    {13, &words::uma},
    {14, &words::duas},
    {15, &words::tres},
    {16, &words::quatro},
    {17, &words::cinco_h},
    {18, &words::seis},
    {19, &words::sete},
    {20, &words::oito},
    {21, &words::nove},
    {22, &words::dez_h},
    {23, &words::onze},
    {24, &words::zero},
};

void ClockRenderer::refresh(uint8_t hours, uint8_t minutes)
{
    etl::vector<const BitFrame *, MAX_WORDS> words;
    static etl::vector<const BitFrame *, MAX_WORDS> last_words;

    words.push_back(hours_map.at(hours));

    if(minutes < 5) {
        if(hours == 1 || hours == 13)
            words.push_back(&words::hora);
        else
            words.push_back(&words::horas);
    } else {
        if(hours == 4 || hours == 16 || hours == 8 || hours == 20)
            words.push_back(&words::e_1);
        else 
            words.push_back(&words::e_0);       
    }

    if(minutes < 5)
        ;
    else if(minutes < 10)
        words.push_back(&words::cinco_m);
    else if (minutes < 15)
        words.push_back(&words::dez_m);
    else if (minutes < 20)
        words.push_back(&words::quinze);
    else if (minutes < 25)
        words.push_back(&words::vinte);
    else if (minutes < 30) {
        words.push_back(&words::vinte);
        words.push_back(&words::e_3);
        words.push_back(&words::cinco_m);
    } else if (minutes < 35)
        words.push_back(&words::trinta);
    else if (minutes < 40){
        words.push_back(&words::trinta);
        words.push_back(&words::e_2);
        words.push_back(&words::cinco_m);
    } else if (minutes < 45)
        words.push_back(&words::quarenta);
    else if (minutes < 50) {
        words.push_back(&words::quarenta);
        words.push_back(&words::e_4);
        words.push_back(&words::cinco_m);
    } else if (minutes < 55)
        words.push_back(&words::cinquenta);
    else  {
        words.push_back(&words::cinquenta);
        words.push_back(&words::e_4);
        words.push_back(&words::cinco_m);
    }

    if(words != last_words) {
        bitframe_renderer.queue_frame(words);   
        last_words = words;
    }
}

