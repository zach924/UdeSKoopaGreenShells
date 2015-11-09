#pragma once
#include "Button.h"
#include <SDL_ttf.h>

class ButtonDiplomacyAction :
    public Button
{
    TTF_Font* m_font;
    std::string m_buttonText;
public:
    ButtonDiplomacyAction(int posX, int posY, int width, int height, std::string buttonText, TTF_Font* font, ButtonState state = ButtonState::Unpressed);
    ~ButtonDiplomacyAction();
    void DoAction();
    void LoadTextTexture(SDL_Renderer* rend);
};

