#ifndef __LOVE_RENDERER__
#define __LOVE_RENDERER__

#include "TextRenderer.hpp"

enum class LoveRendererState {
    EU,
    TE,
    AMO,
    HA,
    X_ANOS,
    ANOS,
    X_MESES,
    MESES,
    E,
    X_DIAS,
    DIAS
};

class LoveRenderer
{
private:
    const int beggining = 1411786800;
    LoveRendererState love_renderer_state = LoveRendererState::EU;
    TextRenderer& text_renderer;
    
public:
    LoveRenderer(TextRenderer& text_renderer);
    void refresh(int epoch);  

    bool finished();
    void start();
};


#endif /* __LOVE_RENDERER__ */