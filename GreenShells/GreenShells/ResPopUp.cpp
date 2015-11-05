#include "ResPopUp.h"

#include "GameWindow.h"



ResPopUp::ResPopUp(const char* windowName, int width, int height)
	:PopUpWindow(windowName, width, height)
{
	int y = 10;
	m_800_600 = new ButtonResSelect(0, 1, 1, 50, y, ButtonState::Unpressed);

	y += 75;
	m_1280_720 = new ButtonResSelect(0, 1, 1, 50, y, ButtonState::Unpressed);

	y += 75;
	m_1600_900 = new ButtonResSelect(0, 1, 1, 50, y, ButtonState::Unpressed);

	y += 75;
	m_1600_1024 = new ButtonResSelect(0, 1, 1, 50, y, ButtonState::Unpressed);

	y += 75;
	m_1920_1080 = new ButtonResSelect(0, 1, 1, 50, y, ButtonState::Unpressed);

	y += 75;
	m_1920_1080_FullScreen = new ButtonResSelect(0, 1, 1, 50, y, ButtonState::Unpressed);

}


ResPopUp::~ResPopUp()
{
}

void ResPopUp::ShowWindow(SDL_Renderer * rend)
{
	SDL_RenderClear(m_rend);
	RenderButton(m_800_600, rend);
	RenderButton(m_1280_720, rend);
	RenderButton(m_1600_900, rend);
	RenderButton(m_1600_1024, rend);
	RenderButton(m_1920_1080, rend);
	RenderButton(m_1920_1080_FullScreen, rend);	
	SDL_RenderPresent(m_rend);
}

void ResPopUp::RenderButton(ButtonResSelect * butt, SDL_Renderer * rend)
{
	int x = butt->GetLeftX();
	int y = butt->GetTopY();
	int width = butt->GetWidth();
	int height = butt->GetHeight();
	SDL_Rect renderQuad = { x, y, width, height };

	Texture* buttonTexture = butt->GetButtonTexture(m_rend);
	Texture * textTexture = butt->GetTextTexture(m_rend);

	SDL_RenderCopy(m_rend, buttonTexture->GetTexture(), NULL, &renderQuad);
	SDL_RenderCopy(m_rend, textTexture->GetTexture(), NULL, &renderQuad);
}

bool ResPopUp::handleEvent(SDL_Event & e)
{
	if (m_800_600->IsUnpressed() && m_800_600->IsInside(e.button.x, e.button.y))
	{
		GameWindow::GetInstance().ChangeResolution(RES_800_600);
		return true;
	}
	if (m_1280_720->IsUnpressed() && m_1280_720->IsInside(e.button.x, e.button.y))
	{
		return true;
	}
	if (m_1600_900->IsUnpressed() && m_1600_900->IsInside(e.button.x, e.button.y))
	{
		return true;
	}
	if (m_1600_1024->IsUnpressed() && m_1600_1024->IsInside(e.button.x, e.button.y))
	{
		return true;
	}
	if (m_1920_1080->IsUnpressed() && m_1920_1080->IsInside(e.button.x, e.button.y))
	{
		return true;
	}
	if (m_1920_1080_FullScreen->IsUnpressed() && m_1920_1080_FullScreen->IsInside(e.button.x, e.button.y))
	{
		return true;
	}
}
