#include <iostream>
#include <sstream>
#include <assert.h>
#include <utility>
#include <assert.h>

#include "UnitBase.h"
#include "DistrictBase.h"
#include "GameWindow.h"
#include "ServerSession.h"
#include "GameSession.h"
#include "WorldState.h"
#include "Map.h"
#include "TileGround.h"
#include "ClickManager.h"
#include "SelectionManager.h"

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

// Unit
#include "UnitArcher.h"
#include "UnitSwordsman.h"
#include "UnitSettler.h"

// District 
#include "DistrictFarm.h"
#include "DistrictCityCenter.h"


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
    ClickManager::GetInstance().AddButton(new ButtonDiplomacy(0, 1, 1, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET, ButtonState::Unpressed), LeftMenuPart::GeneralPart);
    ClickManager::GetInstance().AddButton(new ButtonSkillTree(0, 2, 1, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET, ButtonState::Unpressed), LeftMenuPart::GeneralPart);
    ClickManager::GetInstance().AddButton(new ButtonSpawnUnit(0, 1, 2, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET, ButtonState::Unpressed), LeftMenuPart::GeneralPart);
    ClickManager::GetInstance().AddButton(new ButtonConstructDistrict(0, 2, 2, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET, ButtonState::Unpressed), LeftMenuPart::GeneralPart);
    ClickManager::GetInstance().AddButton(new ButtonGeneralCancel(0, 2, 3, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::GeneralPart);
}

void GameWindow::CreateDistrictButtons()
{
    ClickManager::GetInstance().AddButton(new ButtonDistrictUpgrade(m_CurrentScreen.DISTRICT_MENU_BUTTON_HEIGHT, 1, 1, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::DistrictPart);
    ClickManager::GetInstance().AddButton(new ButtonDistrictSell(m_CurrentScreen.DISTRICT_MENU_BUTTON_HEIGHT, 2, 1, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::DistrictPart);
    ClickManager::GetInstance().AddButton(new ButtonDistrictRepair(m_CurrentScreen.DISTRICT_MENU_BUTTON_HEIGHT, 1, 2, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::DistrictPart);
    ClickManager::GetInstance().AddButton(new ButtonDistrictCancel(m_CurrentScreen.DISTRICT_MENU_BUTTON_HEIGHT, 2, 2, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::DistrictPart);
}

void GameWindow::CreateUnitButtons()
{
    ClickManager::GetInstance().AddButton(new ButtonUnitAttack(m_CurrentScreen.UNIT_MENU_BUTTON_HEIGHT, 1, 1, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitHeal(m_CurrentScreen.UNIT_MENU_BUTTON_HEIGHT, 2, 1, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitUpgrade(m_CurrentScreen.UNIT_MENU_BUTTON_HEIGHT, 1, 2, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitSell(m_CurrentScreen.UNIT_MENU_BUTTON_HEIGHT, 2, 2, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitMove(m_CurrentScreen.UNIT_MENU_BUTTON_HEIGHT, 1, 3, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitCancel(m_CurrentScreen.UNIT_MENU_BUTTON_HEIGHT, 2, 3, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::UnitPart);
}

void GameWindow::ShowWindow()
{
	GameSession::GetInstance().Load("SavedFile\\Test2.xml");
	std::cout << GameSession::GetInstance().GetCurrentPlayerID() << std::endl;
	GameSession::GetInstance().GetWorldState()->GetMap()->GetTile(Position(2, 4))->SetUnit(new UnitSwordsman(0));
	GameSession::GetInstance().GetWorldState()->GetMap()->GetTile(Position(3, 4))->SetUnit(new UnitSwordsman(1));

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
                    int posCol = ((e.button.x - m_CurrentScreen.HUD_WIDTH) / m_CurrentScreen.TILE_SIZE) + m_currentLeftmostX;
                    posCol %= (Map::COLUMNS -1);

                    int posRow = ((e.button.y - m_CurrentScreen.HUD_HEIGHT) / m_CurrentScreen.TILE_SIZE) + m_currentLowestY;
                    posRow %= (Map::ROWS -1);

                    ClickManager::GetInstance().ManageMapClick(Position(posRow, posCol));
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
				switch (e.key.keysym.sym)
				{
				case (SDLK_UP) :
					if (m_currentLowestY > 0)
                    {
						m_currentLowestY--;
                    }
                    else
                    {
                        m_currentLowestY = Map::ROWS - 1;
                    }
					break;
				case (SDLK_LEFT) :
					if (m_currentLeftmostX > 0)
                    {
						m_currentLeftmostX--;
                    }
                    else
                    {
                        m_currentLeftmostX = Map::COLUMNS - 1;
                    }
					break;
				case (SDLK_RIGHT) :
                        m_currentLeftmostX = (m_currentLeftmostX + 1) % (Map::COLUMNS -1);
					break;
				case (SDLK_DOWN) :
                        m_currentLowestY = (m_currentLowestY + 1) % (Map::ROWS - 1);
					break;
				}
			}
            /*
            TODO Remove comment when the speed for scroll is reduced

			else if (e.type == SDL_MOUSEMOTION)
			{
				m_currentlyScrolling = e.button.x > m_CurrentScreen.RIGHT_SCROLL_POSITION
					|| (e.button.x < m_CurrentScreen.LEFT_SCROLL_POSITION && e.button.x > m_CurrentScreen.HUD_WIDTH)
					|| e.button.y > m_CurrentScreen.DOWN_SCROLL_POSITION
					|| (e.button.y < m_CurrentScreen.UP_SCROLL_POSITION && e.button.y > m_CurrentScreen.HUD_HEIGHT);
			}
            */
		}

        /*
        TODO Remove comment when the speed for scroll is reduced
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
        */

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

        //Render Selected district
        {
            Texture* selectedDistrictTexture = SelectionManager::GetInstance().GetSelectedDistrict()->GetTexture();
            int xPos = m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET;
            int yPos = m_CurrentScreen.SELECTED_DISTRICT_HEIGHT;
            SDL_Rect renderQuad = { xPos, yPos, selectedDistrictTexture->GetWidth(), selectedDistrictTexture->GetHeight() };

            //Remove Color and render
            selectedDistrictTexture->SetColor(255, 255, 255);
            SDL_RenderCopy(m_renderer, selectedDistrictTexture->GetTexture(), NULL, &renderQuad);
        }

        //Render Selected unit 
        {
            Texture* selectedUnitTexture = SelectionManager::GetInstance().GetSelectedUnit()->GetTexture();
            int xPos = m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET;
            int yPos = m_CurrentScreen.SELECTED_UNIT_HEIGHT;
            SDL_Rect renderQuad = { xPos, yPos, selectedUnitTexture->GetWidth(), selectedUnitTexture->GetHeight() };

            //Remove Color and render
            selectedUnitTexture->SetColor(255, 255, 255);
            SDL_RenderCopy(m_renderer, selectedUnitTexture->GetTexture(), NULL, &renderQuad);
        }

		//Render Map
		Map map = GameSession::GetInstance().GetWorldState()->GetMapCopy();

        int yIndex = m_currentLowestY;
        for (int i = 0; i <= m_CurrentScreen.NUM_TILE_HEIGHT; ++i)
		{
            int xIndex = m_currentLeftmostX;
            for (int j = 0; j <= m_CurrentScreen.NUM_TILE_WIDTH; ++j)
			{
                TileBase* tile = map.GetTile(Position(yIndex, xIndex));
				Texture* tileTexture = tile->GetTexture();

				//Position the tile on the screen
                int xPos = m_CurrentScreen.HUD_WIDTH + (j * m_CurrentScreen.TILE_SIZE);
                int yPos = m_CurrentScreen.HUD_HEIGHT + (i * m_CurrentScreen.TILE_SIZE);
				SDL_Rect renderQuad = { xPos, yPos, tileTexture->GetWidth(), tileTexture->GetHeight() };

				//Render the tile
				SDL_RenderCopy(m_renderer, tileTexture->GetTexture(), NULL, &renderQuad);

				DistrictBase* district = tile->GetDistrict();
				if (district)
				{
					Texture* districtTexture = district->GetTexture();
                    districtTexture->SetColor(PLAYER_COLORS[district->GetOwnerID()]);
					SDL_RenderCopy(m_renderer, districtTexture->GetTexture(), NULL, &renderQuad);
				}

				UnitBase* unit = tile->GetUnit();
				if (unit)
				{
					Texture* unitTexture = unit->GetTexture();
                    unitTexture->SetColor(PLAYER_COLORS[unit->GetOwnerID()]);
					SDL_RenderCopy(m_renderer, unitTexture->GetTexture(), NULL, &renderQuad);
				}
                xIndex = (xIndex + 1) % (Map::COLUMNS - 1);

			}
            yIndex = (yIndex + 1) % (Map::ROWS - 1);
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
	return x < m_CurrentScreen.HUD_WIDTH && 0 < y;
}

bool GameWindow::IsClickInMap(const int& x, const int& y)
{
	return m_CurrentScreen.HUD_WIDTH < x && x < m_CurrentScreen.MAX_WIDTH && m_CurrentScreen.HUD_HEIGHT < y && y < m_CurrentScreen.MAX_HEIGHT;
}
