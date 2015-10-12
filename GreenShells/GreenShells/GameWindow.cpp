#include <iostream>
#include <sstream>
#include <assert.h>
#include <utility>

#include "GameWindow.h"
#include "ServerSession.h"
#include "GameSession.h"
#include "Texture.h"
#include "WorldState.h"
#include <assert.h>
#include "Map.h"
#include "TileGround.h"
#include "ClickManager.h"

#include "ButtonUnitAttack.h"
#include "ButtonUnitMove.h"

GameWindow::GameWindow(ScreenResolution res)
	:m_window(), m_screenSurface(), m_renderer(), m_CurrentScreen(res),
  	m_topMenuHeight(res.MAX_HEIGHT - res.MAP_HEIGHT),m_leftMenuWidth(res.MAX_WIDTH - res.MAP_WIDTH)
{
	//Initialize SDL
	assert(SDL_Init(SDL_INIT_VIDEO) >= 0 && SDL_GetError());
	
	m_window = SDL_CreateWindow("GreenShells", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_CurrentScreen.MAX_WIDTH, m_CurrentScreen.MAX_HEIGHT, SDL_WINDOW_SHOWN);
	assert(m_window != NULL && SDL_GetError());

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	assert(m_renderer != NULL && SDL_GetError());

	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	ClickManager::GetInstance().AddButton(new ButtonUnitAttack(m_CurrentScreen.MAX_HEIGHT - 170, m_CurrentScreen.MAX_HEIGHT - 106, 21, 85), LeftMenuPart::UnitPart); // Magic number here because I can't do struct 
	ClickManager::GetInstance().AddButton(new ButtonUnitMove(m_CurrentScreen.MAX_HEIGHT - 170, m_CurrentScreen.MAX_HEIGHT - 106, 106, 170), LeftMenuPart::UnitPart); // to reprensent it since it depends on m_currentScreen
}

GameWindow::~GameWindow()
{
	Close();
}



#include "Player.h"
#include "UnitMelee.h"
#include "unitRange.h"
#include "DistrictDefensive.h"

void GameWindow::ShowWindow()
{
	bool quit = false;
    Map* map = ServerSession::GetInstance().m_worldState.GetMap();

    //TODO when replication is available, use gamesession
	//Map* map = GameSession::GetInstance().GetWorldState()->GetMap();

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
					int posX = (e.button.x - m_leftMenuWidth) / m_CurrentScreen.TILE_SIZE;
					int posY = (e.button.y - m_topMenuHeight) / m_CurrentScreen.TILE_SIZE;

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

		//Clear screen
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
		SDL_RenderClear(m_renderer);

		const std::vector<Button*> unitButton = ClickManager::GetInstance().GetUnitButton();

		for (Button* button : unitButton)
		{
			int x = button->GetLeftX();
			int y = button->GetTopY();
			int width = button->GetWidth();
			int height = button->GetHeight();
			Texture * buttonTexture = button->GetTexture();
			SDL_Rect renderQuad = { x, y, width, height };

			SDL_RenderCopy(m_renderer, buttonTexture->GetTexture(), NULL, &renderQuad);
		}

		//Render Screen (Not ready to draw yet)
		for (int i = 0; i <= m_CurrentScreen.NUM_TILE_HEIGHT; ++i)
		{
			for (int j = 0; j <= m_CurrentScreen.NUM_TILE_WIDTH; ++j)
			{
				Texture* tileTexture = map->GetTile(Position(i, j))->GetTexture();

				//Position the tile on the screen
				int x = m_CurrentScreen.HUD_WIDTH + (j * m_CurrentScreen.TILE_SIZE);
				int y = m_CurrentScreen.HUD_HEIGHT + (i * m_CurrentScreen.TILE_SIZE);
				SDL_Rect renderQuad = { x, y, tileTexture->GetWidth(), tileTexture->GetHeight() };

				//Render the tile
				SDL_RenderCopy(m_renderer, tileTexture->GetTexture(), NULL, &renderQuad);

				//TODO Render the district + unit on the tile
			}
		}

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
	return m_leftMenuWidth < x && x < m_CurrentScreen.MAX_WIDTH && m_topMenuHeight < y && y < m_CurrentScreen.MAX_HEIGHT;
}
