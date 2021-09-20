#include "ClockManager.hpp"
#include <vector>
#include <unordered_map>

ClockManager::ClockManager(TextRenderer& text_renderer, NTPClient& ntp_client): text_renderer(text_renderer), ntp_client(ntp_client)
{
}

std::unordered_map<int, Word> hours_map = {
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


void ClockManager::set_color(uint8_t r, uint8_t g, uint8_t b) {
    color = ((uint32_t)g << 16) | ((uint32_t)r <<  8) | b;
}

void ClockManager::refresh()
{
    std::vector<Word> words;
    static std::vector<Word> last_words;

    auto hours = ntp_client.getHours();
    words.push_back(hours_map[hours]);

    auto minutes = ntp_client.getMinutes();

    if(minutes < 5) {
        if(hours == 1)
            words.push_back(Word::HORA);
        else
            words.push_back(Word::HORAS);
    } else if(minutes < 10)
        words.insert(words.end(), {Word::E_1, Word::CINCO_M});
    else if (minutes < 15)
        words.insert(words.end(), {Word::E_1, Word::DEZ_M});
    else if (minutes < 20)
        words.insert(words.end(), {Word::E_1, Word::QUINZE});
    else if (minutes < 25)
        words.insert(words.end(), {Word::E_1, Word::VINTE});
    else if (minutes < 30)
        words.insert(words.end(), {Word::E_1, Word::VINTE, Word::E_3, Word::CINCO_M});
    else if (minutes < 35)
        words.insert(words.end(), {Word::E_1, Word::TRINTA});
    else if (minutes < 40)
        words.insert(words.end(), {Word::E_1, Word::TRINTA, Word::E_2, Word::CINCO_M});
    else if (minutes < 45)
        words.insert(words.end(), {Word::E_1, Word::QUARENTA});
    else if (minutes < 50)
        words.insert(words.end(), {Word::E_1, Word::QUARENTA, Word::E_4, Word::CINCO_M});
    else if (minutes < 55)
        words.insert(words.end(), {Word::E_1, Word::CINQUENTA});
    else 
        words.insert(words.end(), {Word::E_1, Word::CINQUENTA, Word::E_4, Word::CINCO_M});                

    if(words != last_words) {
        text_renderer.queue_text(words, color);   
        last_words = words;
    }
}