#include "Button.h"
#include <iostream>

Button::Button(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :m_topLimit(sectionOffset + (buttonVOffset * rowIndex) + ((rowIndex - 1) * STANDARD_BUTTON_HEIGHT))
    , m_botLimit(sectionOffset + (buttonVOffset * rowIndex) + (STANDARD_BUTTON_HEIGHT* rowIndex))
    , m_lefLimit((buttonHOffset * columnIndex) + ((columnIndex - 1) * STANDARD_BUTTON_WIDTH))
    , m_rightLimit((buttonHOffset * columnIndex) + (STANDARD_BUTTON_WIDTH * columnIndex))
    , m_buttonState(state)
    , m_pressedButton()
    , m_unpressedButton()
{
    std::cout << "Button at : " << m_topLimit << " " << m_botLimit << " and " << m_lefLimit << " " << m_rightLimit << std::endl;
}

Button::Button(int posX, int posY, int width, int height, ButtonState state)
    : m_topLimit(posY)
    , m_botLimit(posY + height)
    , m_lefLimit(posX)
    , m_rightLimit(posX + width)
    , m_buttonState(state)
{
}

Button::~Button()
{
}

void Button::LoadButtonTextures(SDL_Renderer* rend)
{
    try
    {
        m_pressedButton.LoadFromFile("..\\Sprite\\Button\\button_pressed.bmp", rend);
        m_unpressedButton.LoadFromFile("..\\Sprite\\Button\\button_unpressed.bmp", rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool Button::IsInside(int xPos, int yPos)
{
    return m_lefLimit < xPos && xPos < m_rightLimit && m_topLimit < yPos && yPos < m_botLimit;
}

bool Button::IsUnpressed()
{
    return m_buttonState == ButtonState::Unpressed;
}

void Button::SetButtonState(ButtonState state)
{
    m_buttonState = state;
}

int Button::GetTopY()
{
    return m_topLimit;
}

int Button::GetLeftX()
{
    return m_lefLimit;
}

int Button::GetWidth()
{
    return m_rightLimit - m_lefLimit;
}

int Button::GetHeight()
{
    return m_botLimit - m_topLimit;
}

Texture* Button::GetTextTexture(SDL_Renderer* rend)
{
    if (!m_textTexture.IsLoaded())
    {
        LoadTextTexture(rend);
    }
    switch (m_buttonState)
    {
    case ButtonState::Disabled:
        m_textTexture.SetColor(DISABLED_BUTTON_COLOR);
    default:
        m_textTexture.SetColor(DEFAULT_BUTTON_COLOR);
        break;
    }
    return &m_textTexture;
}

Texture* Button::GetButtonTexture(SDL_Renderer* rend)
{
    if (!m_pressedButton.IsLoaded() || !m_unpressedButton.IsLoaded())
    {
        LoadButtonTextures(rend);
    }
    switch (m_buttonState)
    {
    case ButtonState::Pressed:
        m_pressedButton.SetColor(DEFAULT_BUTTON_COLOR);
        return &m_pressedButton;
    case ButtonState::Unpressed:
        m_unpressedButton.SetColor(DEFAULT_BUTTON_COLOR);
        return &m_unpressedButton;
    case ButtonState::Disabled:
        m_unpressedButton.SetColor(DISABLED_BUTTON_COLOR);
        return &m_unpressedButton;
        break;
    default:
        break;
    }
    return nullptr;
}