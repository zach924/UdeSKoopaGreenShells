#include <iostream>
#include <sstream>
#include <assert.h>
#include <utility>

#include "GameWindow.h"
#include "ServerSession.h"
#include "GameSession.h"
#include "WorldState.h"
#include <assert.h>
#include "Map.h"
#include "TileGround.h"
#include "ClickManager.h"

//Buttons
#include "ButtonGeneralCancel.h"
#include "ButtonDiplomacy.h"
#include "ButtonSkillTree.h"
#include "ButtonSpawnUnit.h"
#include "ButtonConstructDistrict.h"

#include "ButtonUnitAttack.h"
#include "ButtonUnitMove.h"
#include "ButtonUnitHeal.h"
#include "ButtonUnitCancel.h"
#include "ButtonUnitSell.h"
#include "ButtonUnitUpgrade.h"

#include "ButtonDistrictCancel.h"
#include "ButtonDistrictRepair.h"
#include "ButtonDistrictSell.h"
#include "ButtonDistrictUpgrade.h"


GameWindow::GameWindow(ScreenResolution res)
	:m_window(), m_screenSurface(), m_renderer(), m_CurrentScreen(res), m_currentLeftmostX(0), m_currentLowestY(0), m_currentlyScrolling(false)
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
    ClickManager::GetInstance().AddButton(new ButtonDiplomacy(0, 1, 1, ButtonState::Unpressed), LeftMenuPart::GeneralPart);
    ClickManager::GetInstance().AddButton(new ButtonSkillTree(0, 2, 1, ButtonState::Unpressed), LeftMenuPart::GeneralPart);
    ClickManager::GetInstance().AddButton(new ButtonSpawnUnit(0, 1, 2, ButtonState::Unpressed), LeftMenuPart::GeneralPart);
    ClickManager::GetInstance().AddButton(new ButtonConstructDistrict(0, 2, 2, ButtonState::Unpressed), LeftMenuPart::GeneralPart);
    ClickManager::GetInstance().AddButton(new ButtonGeneralCancel(0, 2, 3), LeftMenuPart::GeneralPart);
}

void GameWindow::CreateDistrictButtons()
{
    ClickManager::GetInstance().AddButton(new ButtonDistrictUpgrade(m_CurrentScreen.DISTRICT_MENU_HEIGHT, 1, 1), LeftMenuPart::DistrictPart);
    ClickManager::GetInstance().AddButton(new ButtonDistrictSell(m_CurrentScreen.DISTRICT_MENU_HEIGHT, 2, 1), LeftMenuPart::DistrictPart);
    ClickManager::GetInstance().AddButton(new ButtonDistrictRepair(m_CurrentScreen.DISTRICT_MENU_HEIGHT, 1, 2), LeftMenuPart::DistrictPart);
    ClickManager::GetInstance().AddButton(new ButtonDistrictCancel(m_CurrentScreen.DISTRICT_MENU_HEIGHT, 2, 2), LeftMenuPart::DistrictPart);
}

void GameWindow::CreateUnitButtons()
{
    ClickManager::GetInstance().AddButton(new ButtonUnitAttack(m_CurrentScreen.UNIT_MENU_HEIGHT, 1, 1), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitHeal(m_CurrentScreen.UNIT_MENU_HEIGHT, 2, 1), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitUpgrade(m_CurrentScreen.UNIT_MENU_HEIGHT, 1, 2), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitSell(m_CurrentScreen.UNIT_MENU_HEIGHT, 2, 2), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitMove(m_CurrentScreen.UNIT_MENU_HEIGHT, 1, 3), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitCancel(m_CurrentScreen.UNIT_MENU_HEIGHT, 2, 3), LeftMenuPart::UnitPart);
}

#include "Player.h"
#include "Swordsman.h"
#include "Archer.h"
#include "Farm.h"
#include "CityCenter.h"

void GameWindow::ShowWindow()
{
	GameSession::GetInstance().Load("SavedFile\\Test2.xml");

	GameSession::GetInstance().GetWorldState()->GetMap()->GetTile(Position(0, 0))->SetUnit(new Swordsman(0));
	GameSession::GetInstance().GetWorldState()->GetMap()->GetTile(Position(1, 0))->SetUnit(new Archer(0));
	GameSession::GetInstance().GetWorldState()->GetMap()->GetTile(Position(0, 0))->SetDistrict(new Farm(0));
	GameSession::GetInstance().GetWorldState()->GetMap()->GetTile(Position(1, 0))->SetDistrict(new CityCenter(0));

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
				//std::cout << "clicked at X: " << e.button.x << " Y: " << e.button.y << std::endl;
				if (IsClickInMap(e.button.x, e.button.y))
				{
					int posX = ((e.button.x - m_CurrentScreen.HUD_WIDTH) / m_CurrentScreen.TILE_SIZE) + m_currentLeftmostX;
					int posY = ((e.button.y - m_CurrentScreen.HUD_HEIGHT) / m_CurrentScreen.TILE_SIZE) + m_currentLowestY;

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
            else if (e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                case (SDLK_UP) :
                    if (m_currentLowestY > 0)
                        m_currentLowestY--;
                    break;
                case (SDLK_LEFT) :
                    if (m_currentLeftmostX > 0)
                        m_currentLeftmostX--;
                    break;
                case (SDLK_RIGHT) :
                    if (m_currentLeftmostX < Map::COLUMNS - m_CurrentScreen.NUM_TILE_WIDTH-1)
                        m_currentLeftmostX++;
                    break;
                case (SDLK_DOWN) :
                    if (m_currentLowestY < Map::ROWS - m_CurrentScreen.NUM_TILE_HEIGHT-1)
                        m_currentLowestY++;
                    break;
                }
            }
            else if (e.type == SDL_MOUSEMOTION)
            {
                m_currentlyScrolling = e.button.x > m_CurrentScreen.RIGHT_SCROLL_POSITION
                    || (e.button.x < m_CurrentScreen.LEFT_SCROLL_POSITION && e.button.x > m_CurrentScreen.HUD_WIDTH)
                    || e.button.y > m_CurrentScreen.DOWN_SCROLL_POSITION
                    || (e.button.y < m_CurrentScreen.UP_SCROLL_POSITION && e.button.y > m_CurrentScreen.HUD_HEIGHT);
            }
		}

        //mouse scroll
        if (m_currentlyScrolling)
        {
            int mouseX = 0;
            int mouseY = 0;
            SDL_GetMouseState(&mouseX, &mouseY);

            if (m_currentLeftmostX < Map::COLUMNS - m_CurrentScreen.NUM_TILE_WIDTH - 1 && mouseX > m_CurrentScreen.RIGHT_SCROLL_POSITION)
                m_currentLeftmostX++;
            else if (m_currentLeftmostX > 0 && mouseX < m_CurrentScreen.LEFT_SCROLL_POSITION && e.button.x > m_CurrentScreen.HUD_WIDTH)
                m_currentLeftmostX--;

            if (m_currentLowestY < Map::ROWS - m_CurrentScreen.NUM_TILE_HEIGHT - 1 && mouseY > m_CurrentScreen.DOWN_SCROLL_POSITION)
                m_currentLowestY++;
            else if (m_currentLowestY > 0 && mouseY < m_CurrentScreen.UP_SCROLL_POSITION && mouseY > m_CurrentScreen.HUD_HEIGHT)
                m_currentLowestY--;


        }

		//Clear screen
		SDL_SetRenderDrawColor(m_renderer, 32, 32, 32, 0);
		SDL_RenderClear(m_renderer);

        //Render UI
        //Render Buttons
        const std::vector<Button*> generalButtons = ClickManager::GetInstance().GetGeneralButtons();
        for (Button* button : generalButtons)
        {
            int x = button->GetLeftX();
            int y = button->GetTopY();
            int width = button->GetWidth();
            int height = button->GetHeight();
            SDL_Rect renderQuad = { x, y, width, height };

            Texture* buttonTexture = button->GetButtonTexture();
            Texture * textTexture = button->GetTextTexture();

            SDL_RenderCopy(m_renderer, buttonTexture->GetTexture(), NULL, &renderQuad);
            SDL_RenderCopy(m_renderer, textTexture->GetTexture(), NULL, &renderQuad);
        }

        const std::vector<Button*> districtButtons = ClickManager::GetInstance().GetDistrictButtons();
        for (Button* button : districtButtons)
        {
            int x = button->GetLeftX();
            int y = button->GetTopY();
            int width = button->GetWidth();
            int height = button->GetHeight();
            SDL_Rect renderQuad = { x, y, width, height };

            Texture* buttonTexture = button->GetButtonTexture();
            Texture * textTexture = button->GetTextTexture();

            SDL_RenderCopy(m_renderer, buttonTexture->GetTexture(), NULL, &renderQuad);
            SDL_RenderCopy(m_renderer, textTexture->GetTexture(), NULL, &renderQuad);
        }

		const std::vector<Button*> unitButtons = ClickManager::GetInstance().GetUnitButtons();
		for (Button* button : unitButtons)
		{
			int x = button->GetLeftX();
			int y = button->GetTopY();
			int width = button->GetWidth();
			int height = button->GetHeight();
			SDL_Rect renderQuad = { x, y, width, height };

            Texture* buttonTexture = button->GetButtonTexture();
            Texture * textTexture = button->GetTextTexture();

			SDL_RenderCopy(m_renderer, buttonTexture->GetTexture(), NULL, &renderQuad);
            SDL_RenderCopy(m_renderer, textTexture->GetTexture(), NULL, &renderQuad);
		}

		//Render Map
		Map map = GameSession::GetInstance().GetWorldState()->GetMapCopy();

        int yIndex = 0;
		for (int i = m_currentLowestY; i <= (m_currentLowestY + m_CurrentScreen.NUM_TILE_HEIGHT); ++i)
		{
            int xIndex = 0;
			for (int j = m_currentLeftmostX; j <= (m_currentLeftmostX + m_CurrentScreen.NUM_TILE_WIDTH); ++j )
			{
				Texture* tileTexture = map.GetTile(Position(i, j))->GetTexture();

				//Position the tile on the screen
				int xPos = m_CurrentScreen.HUD_WIDTH + (xIndex * m_CurrentScreen.TILE_SIZE);
				int yPos = m_CurrentScreen.HUD_HEIGHT + (yIndex * m_CurrentScreen.TILE_SIZE);
				SDL_Rect renderQuad = { xPos, yPos, tileTexture->GetWidth(), tileTexture->GetHeight() };
				//Render the tile
				SDL_RenderCopy(m_renderer, tileTexture->GetTexture(), NULL, &renderQuad);
                xIndex++;
				//TODO Render the district + unit on the tile
			}
            yIndex++;
		}
		//Draw screen
		SDL_RenderPresent(m_renderer);
	}
	GameSession::GetInstance().Save("SavedFile\\Test2.xml");

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
	return x < m_CurrentScreen.HUD_WIDTH && 0 < y;
}

bool GameWindow::IsClickInMap(const int& x, const int& y)
{
	return m_CurrentScreen.HUD_WIDTH < x && x < m_CurrentScreen.MAX_WIDTH && m_CurrentScreen.HUD_HEIGHT < y && y < m_CurrentScreen.MAX_HEIGHT;
}
