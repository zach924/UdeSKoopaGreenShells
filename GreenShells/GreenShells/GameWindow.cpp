#include <iostream>
#include <sstream>
#include <assert.h>
#include <utility>

#include "GameWindow.h"
#include "GameSession.h"
#include "Texture.h"
#include "WorldState.h"
#include "Map.h"
#include "ClickManager.h"

#include "ButtonUnitAttack.h"
#include "ButtonUnitMove.h"

GameWindow::GameWindow(int width, int height)
//TODO :  magic number
	:m_window(), m_screenSurface(), m_renderer(), m_height(height), m_width(width),
	m_topMenuHeight(64),m_leftMenuWidth(6*64),
	m_mapHeightEnd(910 + m_topMenuHeight),
	m_mapWidthEnd(1300 + m_leftMenuWidth)
{
	//Initialize SDL
	assert(SDL_Init(SDL_INIT_VIDEO) >= 0 && SDL_GetError());
	
	m_window = SDL_CreateWindow("GreenShells", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);
	assert(m_window != NULL && SDL_GetError());

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	assert(m_renderer != NULL && SDL_GetError());

	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	ClickManager::GetInstance().AddButton(new ButtonUnitAttack(m_height - 170, m_height - 106, 21, 85), LeftMenuPart::UnitPart);
	ClickManager::GetInstance().AddButton(new ButtonUnitMove(m_height - 170, m_height - 106, 106, 170), LeftMenuPart::UnitPart);
}

GameWindow::~GameWindow()
{
	Close();
}

void GameWindow::ShowWindow()
{
	bool quit = false;
	while (!quit)
	{
		SDL_Event e;

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_MOUSEBUTTONUP)
			{
				std::cout << "clicked at X: " << e.button.x << " Y: " << e.button.y << std::endl;
				if (IsClickInMap(e.button.x, e.button.y))
				{
					//TODO :  change 65;
					int posX = (e.button.x - m_leftMenuWidth) / 65;
					int posY = (e.button.y - m_topMenuHeight) / 65;

					ClickManager::GetInstance().ManageMapClick(Position(posX,posY));
				}
				else if (IsClickInLeftMenu(e.button.x, e.button.y))
				{
					ClickManager::GetInstance().ManageLeftMenuClick(e.button.x, e.button.y);
				}
				else
				{
					ClickManager::GetInstance().ManageTopMenuClick(e.button.x, e.button.y);
				}
			}
		}

		const std::vector<Button*> unitButton = ClickManager::GetInstance().GetUnitButton();

		for (Button* button : unitButton)
		{
			int x = button->GetLeftX();
			int y = button->GetTopY();
			int width = button->GetWidth();
			int height = button->GetHeight();
			Texture * buttonTexture = button->GetTexture();
			SDL_Rect renderQuad = { x, y, width, height };

			//SDL_RenderCopy(m_renderer, buttonTexture->GetTexture(), NULL, &renderQuad);
		}

		//Clear screen
		SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(m_renderer);

		//Render Screen
		//this is temporary
		GameSession::GetInstance().GetWorldState()->GetMap()->m_texture.Render(300,300);

		//Draw screen
		SDL_RenderPresent(m_renderer);
	}
	Close();
}

SDL_Renderer * GameWindow::GetRenderer()
{
	return m_renderer;
}

void GameWindow::Close()
{
	//Destroy window    
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_window = NULL;
	m_renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

bool GameWindow::IsClickInLeftMenu(const int & x, const int & y)
{
	return x < m_leftMenuWidth && m_topMenuHeight < y;
}

bool GameWindow::IsClickInMap(const int& x, const int& y)
{
	return m_leftMenuWidth < x && x < m_mapWidthEnd && m_topMenuHeight < y && y < m_mapHeightEnd;
}
