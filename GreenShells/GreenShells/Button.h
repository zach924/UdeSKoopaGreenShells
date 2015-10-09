#pragma once
#include "Texture.h"

class Button
{
protected:
	// Not static (no curiously recurring template pattern like tile) 
	// because we do not need since only one button of each will exist;
	Texture m_texture;

    static const int VERTICAL_OFFSET = 38;
    static const int HORIZONTAL_OFFSET = 25;
    static const int BUTTON_HEIGHT = 50;
    static const int BUTTON_WIDTH = 90;

private:
	int m_topLimit;
	int m_botLimit;
	int m_rightLimit;
	int m_lefLimit;

	virtual void LoadTexture() = 0;
public:
	Button(int sectionOffset, int columnIndex, int rowIndex);
	~Button();

	bool IsInside(int xPos, int yPos);

	virtual void DoAction() = 0;

	int GetTopY();
	int GetLeftX();

	int GetWidth();
	int GetHeight();

	Texture* GetTexture();
};

