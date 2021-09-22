#include "LoveRenderer.hpp"
#include <etl/vector.h>
#include <unordered_map>

LoveRenderer::LoveRenderer(TextRenderer& text_renderer): text_renderer(text_renderer)
{

}

const std::unordered_map<int, Word> number_map = {
    {1, Word::UM},
    {2, Word::DOIS},
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
    {13, Word::TREZE},
    {14, Word::QUATORZE},
    {15, Word::QUINZE},
    {16, Word::DEZESSEIS},
    {17, Word::DEZESSETE},
    {18, Word::DEZOITO},
    {19, Word::DEZENOVE},
    {20, Word::VINTE},
    {30, Word::TRINTA},
    {40, Word::QUARENTA},
    {50, Word::CINQUENTA},
};

void number_to_words(int number, etl::vector<Word, MAX_WORDS>& words)
{
    if(number < 20)
        words.push_back(number_map.at(number));
    else {
        int ten = (number / 10) * 10;
        words.push_back(number_map.at(ten));
        int unit = number % ten;
        if(unit > 0) {
            words.push_back(Word::E_0);
            words.push_back(number_map.at(unit));
        }       
    }
}

void LoveRenderer::refresh(int epoch)
{
    etl::vector<Word, MAX_WORDS> words;
    int diff = epoch - beggining;
    int years = diff / 31556926;
    int months = (diff - 31556926 * years) / 2629743;
    int days = (diff - 31556926 * years - 2629743 * months) / 86400;


    switch(love_renderer_state) {
        case LoveRendererState::EU:
            words.push_back(Word::EU);
            love_renderer_state = LoveRendererState::TE;
        break;
        case LoveRendererState::TE:
            words.push_back(Word::TE);
            love_renderer_state = LoveRendererState::AMO;
        break;
        case LoveRendererState::AMO:
            words.push_back(Word::AMO);
            love_renderer_state = LoveRendererState::HA;
        break;
        case LoveRendererState::HA:
            words.push_back(Word::HA);
            love_renderer_state = LoveRendererState::X_ANOS;
        break;
        case LoveRendererState::X_ANOS:
            //words.push_back(Word::SETE);
            number_to_words(years, words);
            love_renderer_state = LoveRendererState::ANOS;
        break;
        case LoveRendererState::ANOS:
            words.push_back(Word::ANOS);
            love_renderer_state = LoveRendererState::X_MESES;
        break;
        case LoveRendererState::X_MESES:
            number_to_words(months, words);
            love_renderer_state = LoveRendererState::MESES;
        break;
        case LoveRendererState::MESES:
            words.push_back(Word::MESES);
            love_renderer_state = LoveRendererState::E;
        break;
        case LoveRendererState::E:
            words.push_back(Word::E_0);
            love_renderer_state = LoveRendererState::X_DIAS;
        break;
        case LoveRendererState::X_DIAS:
            number_to_words(days, words);
            love_renderer_state = LoveRendererState::DIAS;
        break;
        case LoveRendererState::DIAS:
            words.push_back(Word::DIAS);
        break;        
    }
    text_renderer.queue_text(words);
}

void LoveRenderer::start()
{
    love_renderer_state = LoveRendererState::EU;
}

bool LoveRenderer::finished()
{
    return love_renderer_state == LoveRendererState::DIAS;
}
