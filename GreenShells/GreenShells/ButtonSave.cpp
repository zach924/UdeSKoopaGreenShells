#include <iostream>
#include <string>
#include "ButtonSave.h"
#include "GameSession.h"
#include "Player.h"



ButtonSave::ButtonSave(int posX, int posY, int width, int height, ButtonState state)
    :Button(posX, posY, width, height, state)
{
}


ButtonSave::~ButtonSave()
{
}

void ButtonSave::DoAction()
{
    std::string fileName = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID())->GetPlayerName();
    fileName += "_";
    fileName += std::to_string(GameSession::GetInstance().GetWorldState()->GetCurrentTurn());
    GameSession::GetInstance().Save(fileName);
}

void ButtonSave::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.CreateFromText("Save", nullptr, rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}
