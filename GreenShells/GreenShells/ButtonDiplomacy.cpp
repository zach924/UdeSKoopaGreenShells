#include <iostream>
#include <SDL_ttf.h>
#include "ButtonDiplomacy.h"
#include "SelectionManager.h"
#include "DiplomacyPopUp.h"
#include "GameWindow.h"
#include "GameSession.h"
#include "Player.h"
#include "DiplomaticRelation.h"

ButtonDiplomacy::ButtonDiplomacy(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state), m_negociatingTexture()
{
}

ButtonDiplomacy::~ButtonDiplomacy()
{
}

void ButtonDiplomacy::DoAction()
{
    DiplomacyPopUp* popUp = new DiplomacyPopUp();
    GameWindow::GetInstance().AddPopUpWindow(popUp);
}

void ButtonDiplomacy::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("Ressources\\Sprite\\Button\\Diplomacy_text.bmp", rend);
        TTF_Font* tempFont = TTF_OpenFont("Ressources\\Fonts\\roboto\\Roboto-BlackItalic.ttf", 16);
        m_negociatingTexture.CreateFromText("Negotiating", tempFont);
        TTF_CloseFont(tempFont);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

Texture* ButtonDiplomacy::GetButtonTexture(SDL_Renderer* rend)
{
    if (!m_pressedButton.IsLoaded() || !m_unpressedButton.IsLoaded())
    {
        LoadButtonTextures(rend);
    }
        
    if (!GameSession::GetInstance().GetCurrentPlayerCopy()->IsNegociating())
    {
        return Button::GetButtonTexture();
    }
    else
    {
        switch (m_buttonState)
        {
        case ButtonState::Pressed:
            m_pressedButton.SetColor(NEGOCIATING_COLOR);
            return &m_pressedButton;
        case ButtonState::Unpressed:
            m_unpressedButton.SetColor(NEGOCIATING_COLOR);
            return &m_unpressedButton;
        case ButtonState::Disabled:
            m_unpressedButton.SetColor(NEGOCIATING_COLOR);
            return &m_unpressedButton;
            break;
        default:
            break;
        }
    }

    return nullptr;
}

Texture * ButtonDiplomacy::GetTextTexture(SDL_Renderer * rend)
{
    if (!m_textTexture.IsLoaded() || !m_negociatingTexture.IsLoaded())
    {
        LoadTextTexture(rend);
    }

    if (!GameSession::GetInstance().GetCurrentPlayerCopy()->IsNegociating())
    {
        return Button::GetTextTexture();
    }
    else
    {
        return &m_negociatingTexture;
    }
}