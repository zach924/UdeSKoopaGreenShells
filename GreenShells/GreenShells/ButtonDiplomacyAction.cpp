#include "ButtonDiplomacyAction.h"
#include <assert.h>
#include <iostream>

ButtonDiplomacyAction::ButtonDiplomacyAction(int posX, int posY, int width, int height, std::string buttonText, TTF_Font* font, ButtonState state)
    : Button(posX, posY, width, height, state)
    , m_buttonText(buttonText)
    , m_font(font)
{
}

ButtonDiplomacyAction::~ButtonDiplomacyAction()
{
    m_font = nullptr;
}

void ButtonDiplomacyAction::DoAction()
{
    assert(false && "Should only be used in the diplomacy window");
}

void ButtonDiplomacyAction::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.CreateFromText(m_buttonText, m_font, rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}