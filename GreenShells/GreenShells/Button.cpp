#include "Button.h"
#include <iostream>

Button::Button(int sectionOffset, int columnIndex, int rowIndex)
	:m_topLimit(sectionOffset + (VERTICAL_OFFSET * rowIndex) + ((rowIndex - 1) * BUTTON_HEIGHT))
    , m_botLimit(sectionOffset + (VERTICAL_OFFSET * rowIndex) +(BUTTON_HEIGHT* rowIndex))
    , m_lefLimit((HORIZONTAL_OFFSET * columnIndex ) + ((columnIndex - 1) * BUTTON_WIDTH))
    , m_rightLimit((HORIZONTAL_OFFSET * columnIndex )+ (BUTTON_WIDTH * columnIndex))
{
	std::cout << "Button at : " << m_topLimit << " " << m_botLimit << " and " << m_lefLimit << " " << m_rightLimit << std::endl;
}

Button::~Button()
{
}

bool Button::IsInside(int xPos, int yPos)
{
	return m_lefLimit < xPos && xPos < m_rightLimit && m_topLimit < yPos && yPos < m_botLimit;
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

Texture * Button::GetTexture()
{
	if (!m_texture.IsLoaded())
	{
		LoadTexture();
	}
	return &m_texture;
}
