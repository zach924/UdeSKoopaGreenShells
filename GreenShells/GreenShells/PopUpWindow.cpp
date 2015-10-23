#include <assert.h>
#include "Button.h"
#include "PopUpWindow.h"



PopUpWindow::PopUpWindow(std::string windowText, int width, int height)
	:m_wind(), m_screenSurface(), m_rend(), m_fontSize(24), m_width(width)
{
	m_wind = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	assert(m_wind != NULL && SDL_GetError());

	SDL_SetWindowBordered(m_wind, SDL_FALSE);

	m_rend = SDL_CreateRenderer(m_wind, -1, SDL_RENDERER_ACCELERATED);
	assert(m_rend != NULL && SDL_GetError());

	SDL_SetRenderDrawColor(m_rend, 80, 80, 80, 0);

	m_font = TTF_OpenFont("..\\Fonts\\roboto\\Roboto-Thin.ttf", m_fontSize);
	assert(m_font != NULL && TTF_GetError());


	SDL_Color textColor = { 255, 255, 255 };

	int numberOfCharPerLine = TTF_FontLineSkip(m_font);
	size_t pos = 0;
	size_t lastPos = 0;

	std::string delimiter = " ";
	std::vector<std::string> allLines;

	// Split text into lines taking account of white spaces
	while (pos != std::string::npos)
	{
		pos = 0;
		while (pos < numberOfCharPerLine)
		{
			lastPos = pos;
			pos = windowText.find(delimiter, pos + 1);
		}

		lastPos = (pos == std::string::npos) ? pos : lastPos;
		std::string aLine = windowText.substr(0, lastPos);
		int numberOfSpceToFill = numberOfCharPerLine - aLine.length();
		aLine.append(numberOfSpceToFill, ' ');
		allLines.emplace_back(aLine);
		windowText.erase(0, lastPos + delimiter.length());
	}

	for (std::string& line : allLines)
	{
		SDL_Surface *surf = TTF_RenderText_Solid(m_font, line.c_str(), textColor);
		assert(surf != NULL && TTF_GetError());

		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_rend, surf);
		assert(textTexture != NULL && TTF_GetError());

		m_texts.emplace_back(textTexture);
	}
}


PopUpWindow::~PopUpWindow()
{
	Close();
}

void PopUpWindow::Close()
{
	//Destroy window    
	SDL_DestroyRenderer(m_rend);
	SDL_DestroyWindow(m_wind);
	m_wind = NULL;
	m_rend = NULL;
}

SDL_Window * PopUpWindow::GetWindow()
{
	return m_wind;
}


