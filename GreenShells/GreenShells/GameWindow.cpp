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
	:m_window(), m_screenSurface(), m_renderer(), m_CurrentScreen(res)
{
	//Initialize SDL
	assert(SDL_Init(SDL_INIT_VIDEO) >= 0 && SDL_GetError());
	
	m_window = SDL_CreateWindow("GreenShells", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_CurrentScreen.MAX_WIDTH, m_CurrentScreen.MAX_HEIGHT, SDL_WINDOW_SHOWN);
	assert(m_window != NULL && SDL_GetError());

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	assert(m_renderer != NULL && SDL_GetError());

	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    CreateGeneralButtons();
    CreateDistrictButtons();
    CreateUnitButtons();
}

GameWindow::~GameWindow()
{
	Close();
}

void GameWindow::CreateGeneralButtons()
{
    ClickManager::GetInstance().AddButton(new ButtonUnitAttack(0, 1, 1), LeftMenuPart::GeneralPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitMove(0, 1, 2), LeftMenuPart::GeneralPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitAttack(0, 1, 3), LeftMenuPart::GeneralPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitMove(0, 2, 1), LeftMenuPart::GeneralPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitAttack(0, 2, 2), LeftMenuPart::GeneralPart);
}

void GameWindow::CreateDistrictButtons()
{
    ClickManager::GetInstance().AddButton(new ButtonUnitAttack(m_CurrentScreen.DISTRICT_MENU_HEIGHT, 1, 1), LeftMenuPart::DistrictPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitMove(m_CurrentScreen.DISTRICT_MENU_HEIGHT, 1, 2), LeftMenuPart::DistrictPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitAttack(m_CurrentScreen.DISTRICT_MENU_HEIGHT, 1, 3), LeftMenuPart::DistrictPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitMove(m_CurrentScreen.DISTRICT_MENU_HEIGHT, 2, 1), LeftMenuPart::DistrictPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitAttack(m_CurrentScreen.DISTRICT_MENU_HEIGHT, 2, 2), LeftMenuPart::DistrictPart);
}

void GameWindow::CreateUnitButtons()
{
    ClickManager::GetInstance().AddButton(new ButtonUnitAttack(m_CurrentScreen.UNIT_MENU_HEIGHT, 1, 1), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitMove(m_CurrentScreen.UNIT_MENU_HEIGHT,1,2), LeftMenuPart::UnitPart); 
    ClickManager::GetInstance().AddButton(new ButtonUnitAttack(m_CurrentScreen.UNIT_MENU_HEIGHT, 1, 3), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitMove(m_CurrentScreen.UNIT_MENU_HEIGHT, 2, 1), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitAttack(m_CurrentScreen.UNIT_MENU_HEIGHT, 2, 2), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitMove(m_CurrentScreen.UNIT_MENU_HEIGHT, 2, 3), LeftMenuPart::UnitPart);
}

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
					int posX = (e.button.x - m_CurrentScreen.HUD_WIDTH) / m_CurrentScreen.TILE_SIZE;
					int posY = (e.button.y - m_CurrentScreen.HUD_HEIGHT) / m_CurrentScreen.TILE_SIZE;

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

		const std::vector<Button*> unitButtons = ClickManager::GetInstance().GetUnitButtons();

		for (Button* button : unitButtons)
		{
			int x = button->GetLeftX();
			int y = button->GetTopY();
			int width = button->GetWidth();
			int height = button->GetHeight();
			Texture * buttonTexture = button->GetTexture();
			SDL_Rect renderQuad = { x, y, width, height };

			SDL_RenderCopy(m_renderer, buttonTexture->GetTexture(), NULL, &renderQuad);
		}
        
        const std::vector<Button*> districtButtons = ClickManager::GetInstance().GetDistrictButtons();

        for (Button* button : districtButtons)
        {
            int x = button->GetLeftX();
            int y = button->GetTopY();
            int width = button->GetWidth();
            int height = button->GetHeight();
            Texture * buttonTexture = button->GetTexture();
            SDL_Rect renderQuad = { x, y, width, height };

            SDL_RenderCopy(m_renderer, buttonTexture->GetTexture(), NULL, &renderQuad);
        }


        const std::vector<Button*> generalButtons = ClickManager::GetInstance().GetGeneralButtons();

        for (Button* button : generalButtons)
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
				Texture* tileTexture = map->GetTile(Position(j, i))->GetTexture();

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
	return x < m_CurrentScreen.HUD_WIDTH && m_CurrentScreen.HUD_HEIGHT< y;
}

bool GameWindow::IsClickInMap(const int& x, const int& y)
{
	return m_CurrentScreen.HUD_WIDTH < x && x < m_CurrentScreen.MAX_WIDTH && m_CurrentScreen.HUD_HEIGHT < y && y < m_CurrentScreen.MAX_HEIGHT;
}
