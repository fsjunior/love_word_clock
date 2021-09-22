#include "ClockRenderer.hpp"
#include <etl/vector.h>
#include <unordered_map>

ClockRenderer::ClockRenderer(TextRenderer& text_renderer): text_renderer(text_renderer)
{

}

const std::unordered_map<int, Word> hours_map = {
    {0, Word::ZERO},
    {1, Word::UMA},
    {2, Word::DUAS},
    {3, Word::TRES},
    {4, Word::QUATRO},
    {5, Word::CINCO_H},
    {6, Word::SEIS},
    {7, Word::SETE},
    {8, Word::OITO},
    {9, Word::NOVE},
    {10, Word::DEZ_H},
    {11, Word::ONZE},
    {12, Word::DOZE},
    {13, Word::UMA},
    {14, Word::DUAS},
    {15, Word::TRES},
    {16, Word::QUATRO},
    {17, Word::CINCO_H},
    {18, Word::SEIS},
    {19, Word::SETE},
    {20, Word::OITO},
    {21, Word::NOVE},
    {22, Word::DEZ_H},
    {23, Word::ONZE},
    {24, Word::ZERO},
};

void ClockRenderer::refresh(uint8_t hours, uint8_t minutes)
{
    etl::vector<Word, MAX_WORDS> words;
    static etl::vector<Word, MAX_WORDS> last_words;

    words.push_back(hours_map.at(hours));

    if(minutes < 5) {
        if(hours == 1 || hours == 13)
            words.push_back(Word::HORA);
        else
            words.push_back(Word::HORAS);
    } else {
        if(hours == 4 || hours == 16 || hours == 8 || hours == 20)
            words.push_back(Word::E_1);
        else 
            words.push_back(Word::E_0);       
    }

    if(minutes < 5)
        ;
    else if(minutes < 10)
        words.push_back(Word::CINCO_M);
    else if (minutes < 15)
        words.push_back(Word::DEZ_M);
    else if (minutes < 20)
        words.push_back(Word::QUINZE);
    else if (minutes < 25)
        words.push_back(Word::VINTE);
    else if (minutes < 30) {
        words.push_back(Word::VINTE);
        words.push_back(Word::E_3);
        words.push_back(Word::CINCO_M);
    } else if (minutes < 35)
        words.push_back(Word::TRINTA);
    else if (minutes < 40){
        words.push_back(Word::TRINTA);
        words.push_back(Word::E_2);
        words.push_back(Word::CINCO_M);
    } else if (minutes < 45)
        words.push_back(Word::QUARENTA);
    else if (minutes < 50) {
        words.push_back(Word::QUARENTA);
        words.push_back(Word::E_4);
        words.push_back(Word::CINCO_M);
    } else if (minutes < 55)
        words.push_back(Word::CINQUENTA);
    else  {
        words.push_back(Word::CINQUENTA);
        words.push_back(Word::E_4);
        words.push_back(Word::CINCO_M);
    }

    if(words != last_words) {
        text_renderer.queue_text(words);   
        last_words = words;
    }
}

