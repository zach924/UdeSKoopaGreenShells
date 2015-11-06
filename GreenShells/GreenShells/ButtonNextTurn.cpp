#include "ButtonNextTurn.h"
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "GameSession.h"
#include "Player.h"

ButtonNextTurn::ButtonNextTurn(int posX, int posY, int width, int height, ButtonState state)
    :Button(posX, posY, width, height, state)
{
}

ButtonNextTurn::~ButtonNextTurn()
{
}

void ButtonNextTurn::DoAction()
{
    GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID())->SetPlayerReadyForNextTurn();
    //SetButtonState(ButtonState::Disabled);
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