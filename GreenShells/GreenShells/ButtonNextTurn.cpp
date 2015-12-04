#include "ButtonNextTurn.h"
#include <iostream>
#include <assert.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "GameSession.h"
#include "SelectionManager.h"
#include "Player.h"

ButtonNextTurn::ButtonNextTurn(int posX, int posY, int width, int height, ButtonState state)
    :Button(posX, posY, width, height, state)
    , m_waitingTexture()
{
}

ButtonNextTurn::~ButtonNextTurn()
{
}

void ButtonNextTurn::DoAction()
{
    GameSession::GetInstance().GetCurrentPlayerCopy()->SetPlayerReadyForNextTurn();
    SelectionManager::GetInstance().UpdateButtonState();
}

void ButtonNextTurn::LoadTextTexture(SDL_Renderer * rend)
{
    try
    {
        TTF_Font* font = TTF_OpenFont("Resources\\Fonts\\roboto\\Roboto-BlackItalic.ttf", 30);
        m_textTexture.CreateFromText("Next Turn", font);
        m_waitingTexture.CreateFromText("Waiting for players");
        TTF_CloseFont(font);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

Texture* ButtonNextTurn::GetTextTexture(SDL_Renderer * rend)
{
    if (!m_waitingTexture.IsLoaded() || !m_textTexture.IsLoaded())
    {
        LoadTextTexture(rend);
    }

    switch (m_buttonState)
    {
    case ButtonState::Disabled:
        return &m_waitingTexture;
    //Same texture for both
    case ButtonState::Pressed:
    case ButtonState::Unpressed:
        return &m_textTexture;
    default:
        assert(false && "You need to add your new state here");
        return nullptr;
    }
}
