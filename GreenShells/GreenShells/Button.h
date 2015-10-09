#pragma once
#include "Texture.h"

class Button
{
protected:
	// Not static (no curiously recurring template pattern like tile) 
	// because we do not need since only one button of each will exist;
	Texture m_texture;

private:
	int m_topLimit;
	int m_botLimit;
	int m_rightLimit;
	int m_lefLimit;

	virtual void LoadTexture() = 0;
public:
	Button(int topLimit, int botLimit, int leftLimit, int rightLimit);
	~Button();

	bool IsInside(int xPos, int yPos);

	virtual void DoAction() = 0;

	int GetTopY();
	int GetLeftX();

	int GetWidth();
	int GetHeight();

	Texture* GetTexture();
};

