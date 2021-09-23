#include "LoveRenderer.hpp"
#include <etl/vector.h>
#include <unordered_map>

LoveRenderer::LoveRenderer(BitFrameRenderer& bitframe_renderer): bitframe_renderer(bitframe_renderer)
{

}

const std::unordered_map<int, const BitFrame *> number_map = {
    {1, &words::um},
    {2, &words::dois},
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
    {13, &words::treze},
    {14, &words::quatorze},
    {15, &words::quinze},
    {16, &words::dezesseis},
    {17, &words::dezessete},
    {18, &words::dezoito},
    {19, &words::dezenove},
    {20, &words::vinte},
    {30, &words::trinta},
    {40, &words::quarenta},
    {50, &words::cinquenta},
};

void LoveRenderer::number_to_words(const int number, const BitFrame * singular, const BitFrame * plural)
{
    if(number == 0)
        return;

    if(number < 20)
        queue.push(etl::make_pair<>(number_map.at(number), 0x0));
    else {
        int ten = (number / 10) * 10;
        queue.push(etl::make_pair<>(number_map.at(ten), 0x0));
        int unit = number % ten;
        if(unit > 0) {
            queue.push(etl::make_pair<>(&words::e_0, 0x0));
            queue.push(etl::make_pair<>(number_map.at(unit), 0x0));
        }       
    }
    if(number == 1)
        queue.push(etl::make_pair<>(singular, 0x0));
    else
        queue.push(etl::make_pair<>(plural, 0x0));
}

void LoveRenderer::start(unsigned long epoch)
{
    unsigned long diff = epoch - beggining;
    unsigned long years = diff / 31556926;
    unsigned long months = (diff - 31556926 * years) / 2629743;
    unsigned long days = (diff - 31556926 * years - 2629743 * months) / 86400;

    queue.clear();
    queue.push(etl::make_pair<>(&draws::blank, 0x0));
    queue.push(etl::make_pair<>(&draws::heart, 0x00FF00));
    queue.push(etl::make_pair<>(&draws::heart, 0x0));
    queue.push(etl::make_pair<>(&draws::blank, 0x0));

    queue.push(etl::make_pair<>(&words::eu, 0x0));
    queue.push(etl::make_pair<>(&words::te_1, 0x0));
    queue.push(etl::make_pair<>(&words::amo_2, 0x0));
    queue.push(etl::make_pair<>(&words::ha, 0x0));
    number_to_words(years, &words::ano, &words::anos);
    if(months > 0 && days == 0)
        queue.push(etl::make_pair<>(&words::e_0, 0x0));
    number_to_words(months, &words::mes, &words::meses);
    if(days > 0)
        queue.push(etl::make_pair<>(&words::e_1, 0x0));
    number_to_words(days, &words::dia, &words::dias);
    queue.push(etl::make_pair<>(&draws::blank, 0x0));
}

bool LoveRenderer::refresh()
{
    etl::pair frame = queue.front();    
    bitframe_renderer.queue_frame(frame.first, frame.second);
    queue.pop();
    return !queue.empty();
}

