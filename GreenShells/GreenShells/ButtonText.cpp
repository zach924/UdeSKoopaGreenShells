#include <iostream>
#include <SDL.h>
#include "ButtonText.h"

ButtonText::ButtonText(int posX, int posY, int width, int height, std::string text, std::function<void()> lambda, TTF_Font* font, ButtonState state)
    :Button(posX, posY, width, height, state),
    m_text(text),
    m_function(lambda),
    m_font(font)
{
}

ButtonText::~ButtonText()
{
}

void ButtonText::DoAction()
{
    m_buttonState = ButtonState::Pressed;
    m_function();
    m_buttonState = ButtonState::Unpressed;
    
}

void ButtonText::LoadTextTexture(SDL_Renderer * rend)
{
    try
    {
        m_textTexture.CreateFromText(m_text, m_font, rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}