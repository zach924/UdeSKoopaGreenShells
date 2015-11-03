#include "ButtonNextTurn.h"
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

ButtonNextTurn::ButtonNextTurn(int posX, int posY, int width, int height, ButtonState state)
    :Button(posX, posY, width, height, state)
{
}

ButtonNextTurn::~ButtonNextTurn()
{
}

void ButtonNextTurn::LoadTextTexture(SDL_Renderer * rend)
{
    try
    {
        m_textTexture.CreateFromText("Next Turn");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

Texture * ButtonNextTurn::GetTextTexture(SDL_Renderer * rend)
{
    return nullptr;
}

Texture * ButtonNextTurn::GetButtonTexture(SDL_Renderer * rend)
{
    return nullptr;
}

