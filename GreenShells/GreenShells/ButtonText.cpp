#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include "ButtonText.h"

ButtonText::ButtonText(int posX, int posY, int width, int height, std::string text, std::function<void()> lambda, ButtonState state)
    :Button(posX, posY, width, height, state),
    m_text(text),
    m_function(lambda)
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
        TTF_Font* font = TTF_OpenFont("..\\Fonts\\roboto\\Roboto-Light.ttf", 16);
        m_textTexture.CreateFromText(m_text, font, rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}