#include "Button.h"
#include <iostream>

Button::Button(int topLimit, int botLimit, int leftLimit, int rightLimit)
	:m_topLimit(topLimit), m_botLimit(botLimit),
	m_lefLimit(leftLimit), m_rightLimit(rightLimit)
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
	return m_rightLimit;
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
