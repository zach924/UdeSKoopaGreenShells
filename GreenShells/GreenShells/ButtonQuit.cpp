#include <iostream>
#include "ButtonQuit.h"
#include "GameWindow.h"

ButtonQuit::ButtonQuit(int posX, int posY, int width, int height, ButtonState state)
    :Button(posX, posY, width, height, state)
{
}


ButtonQuit::~ButtonQuit()
{
}

void ButtonQuit::DoAction()
{
    GameWindow::GetInstance().RequestQuit();
}

void ButtonQuit::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.CreateFromText("Quit", nullptr, rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}
