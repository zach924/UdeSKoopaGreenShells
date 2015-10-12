#include "Button.h"
#include <iostream>

Button::Button(int sectionOffset, int columnIndex, int rowIndex, ButtonState state)
	:m_topLimit(sectionOffset + (VERTICAL_OFFSET * rowIndex) + ((rowIndex - 1) * BUTTON_HEIGHT))
    , m_botLimit(sectionOffset + (VERTICAL_OFFSET * rowIndex) +(BUTTON_HEIGHT* rowIndex))
    , m_lefLimit((HORIZONTAL_OFFSET * columnIndex ) + ((columnIndex - 1) * BUTTON_WIDTH))
    , m_rightLimit((HORIZONTAL_OFFSET * columnIndex )+ (BUTTON_WIDTH * columnIndex))
    , m_buttonState(state)
    , m_pressedButton()
    , m_unpressedButton()
{
    std::cout << "Button at : " << m_topLimit << " " << m_botLimit << " and " << m_lefLimit << " " << m_rightLimit << std::endl;
}

Button::~Button()
{
}

void Button::LoadButtonTextures()
{
    try
    {
        m_pressedButton.LoadFromFile("..\\Sprite\\Button\\button_pressed.bmp");
        m_unpressedButton.LoadFromFile("..\\Sprite\\Button\\button_unpressed.bmp");
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

Texture* Button::GetTextTexture()
{
	if (!m_textTexture.IsLoaded())
	{
		LoadTextTexture();
	}
    switch (m_buttonState)
    {
    case ButtonState::Disabled:
        m_textTexture.SetColor(DISABLED_BUTTON_COLOR);
    default:
        break;
    }
	return &m_textTexture;
}

Texture* Button::GetButtonTexture()
{
    if (!m_pressedButton.IsLoaded() || !m_unpressedButton.IsLoaded())
    {
        LoadButtonTextures();
    }
    switch (m_buttonState)
    {
    case ButtonState::Pressed:
        return &m_pressedButton;
    case ButtonState::Unpressed:
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
