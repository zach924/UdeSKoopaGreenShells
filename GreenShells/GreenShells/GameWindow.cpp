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
#include "TileMountain.h"
#include "TileWater.h"
#include "ClickManager.h"
#include "SelectionManager.h"
#include "Player.h"

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

#include "ButtonMenu.h"
#include "ButtonNextTurn.h"

#include "UnitSettler.h"
#include "UnitBuilder.h"

#include "UnitArcherI.h"
#include "UnitArcherII.h"
#include "UnitArcherIII.h"

#include "UnitSwordsmanI.h"
#include "UnitSwordsmanII.h"
#include "UnitSwordsmanIII.h"

#include "UnitAxemanI.h"
#include "UnitAxemanII.h"

#include "UnitMaceI.h"
#include "UnitMaceII.h"

#include "UnitCannon.h"
#include "UnitShield.h"
#include "UnitEmpty.h"

#include "DistrictCityCenter.h"

#include "DistrictHunter.h"
#include "DistrictFarm.h"
#include "DistrictWindMill.h"
#include "DistrictWarehouse.h"

#include "DistrictBlacksmith.h"
#include "DistrictStable.h"
#include "DistrictFort.h"
#include "DistrictFortress.h"

#include "DistrictMonastery.h"
#include "DistrictCathedral.h"
#include "DistrictSchool.h"
#include "DistrictUniversity.h"

#include "DistrictWatchTower.h"
#include "DistrictInn.h"
#include "DistrictTavern.h"
#include "DistrictMilitaryTent.h"
#include "DistrictEmpty.h"

GameWindow::GameWindow(ScreenResolution res)
    :m_window()
    , m_renderer()
    , m_CurrentScreenResolution(res)
    , m_currentLeftmostColumn(0)
    , m_currentLowestRow(0)
    , m_currentlyScrolling(false)
    , m_foodTexture()
    , m_overlayTexture()
    , m_selectdOverlayTexture()
    , m_scienceTexture()
    , m_weaponTexture()
    , m_doQuit(false)
    , m_resChanged(false)
{
    //Initialize SDL                                                                                                                            
    assert(SDL_Init(SDL_INIT_VIDEO) >= 0 && SDL_GetError());
    assert(TTF_Init() >= 0 && TTF_GetError());

    auto windowType = m_CurrentScreenResolution.FULLSCREEN ? SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_SHOWN;
    m_window = SDL_CreateWindow("GreenShells", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_CurrentScreenResolution.MAX_WIDTH, m_CurrentScreenResolution.MAX_HEIGHT, windowType);
    assert(m_window != NULL && SDL_GetError());

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);//VSYNC caps at 60 fps
    assert(m_renderer != NULL && SDL_GetError());

    SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");

    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    CreateButtons();
    LoadLocalTextures();

    auto cityCenterMap = GameSession::GetInstance().GetCurrentPlayerCopy()->GetCityCenterLocations();

    assert(cityCenterMap.begin() != cityCenterMap.end() && "The current player should have a city center when creating a window for the first time");

    m_currentLeftmostColumn = cityCenterMap.begin()->first.Column - (m_CurrentScreenResolution.NUM_TILE_WIDTH / 2);
    if (m_currentLeftmostColumn < 0)
    {
        m_currentLeftmostColumn += Map::COLUMNS;
    }
    else if (m_currentLeftmostColumn >= Map::COLUMNS)
    {
        m_currentLeftmostColumn -= Map::COLUMNS;
    }

    m_currentLowestRow = cityCenterMap.begin()->first.Row - (m_CurrentScreenResolution.NUM_TILE_HEIGHT / 2);
    if (m_currentLowestRow < 0)
    {
        m_currentLowestRow += Map::ROWS;
    }
    else if (m_currentLowestRow >= Map::ROWS)
    {
        m_currentLowestRow -= Map::ROWS;
    }
}

GameWindow::~GameWindow()
{
    delete m_foodTexture;
    delete m_scienceTexture;
    delete m_weaponTexture;
    delete m_overlayTexture;
    delete m_selectdOverlayTexture;
    m_foodTexture = nullptr;
    m_scienceTexture = nullptr;
    m_weaponTexture = nullptr;
    m_overlayTexture = nullptr;
    m_selectdOverlayTexture = nullptr;

    Close();
}

void GameWindow::CreateButtons()
{
    ClickManager::GetInstance().AddButton(new ButtonDiplomacy(0, 1, 1, m_CurrentScreenResolution.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreenResolution.BUTTON_VERTICAL_OFFSET, ButtonState::Unpressed));
    ClickManager::GetInstance().AddButton(new ButtonSkillTree(0, 2, 1, m_CurrentScreenResolution.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreenResolution.BUTTON_VERTICAL_OFFSET, ButtonState::Unpressed));
    ClickManager::GetInstance().AddButton(new ButtonSpawnUnit(0, 1, 2, m_CurrentScreenResolution.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreenResolution.BUTTON_VERTICAL_OFFSET));
    ClickManager::GetInstance().AddButton(new ButtonConstructDistrict(0, 2, 2, m_CurrentScreenResolution.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreenResolution.BUTTON_VERTICAL_OFFSET));
    ClickManager::GetInstance().AddButton(new ButtonGeneralCancel(0, 2, 3, m_CurrentScreenResolution.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreenResolution.BUTTON_VERTICAL_OFFSET));

    //Next turn
    ClickManager::GetInstance().AddButton(new ButtonNextTurn(m_CurrentScreenResolution.MINIMAP_BORDER_X,
        m_CurrentScreenResolution.MINIMAP_BORDER_Y - m_CurrentScreenResolution.NEXT_TURN_BUTTON_HEIGHT,
        m_CurrentScreenResolution.NEXT_TURN_BUTTON_WIDTH,
        m_CurrentScreenResolution.NEXT_TURN_BUTTON_HEIGHT));

    //Districts
    ClickManager::GetInstance().AddButton(new ButtonDistrictUpgrade(m_CurrentScreenResolution.DISTRICT_MENU_BUTTON_HEIGHT, 1, 1, m_CurrentScreenResolution.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreenResolution.BUTTON_VERTICAL_OFFSET));
    ClickManager::GetInstance().AddButton(new ButtonDistrictSell(m_CurrentScreenResolution.DISTRICT_MENU_BUTTON_HEIGHT, 2, 1, m_CurrentScreenResolution.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreenResolution.BUTTON_VERTICAL_OFFSET));
    ClickManager::GetInstance().AddButton(new ButtonDistrictRepair(m_CurrentScreenResolution.DISTRICT_MENU_BUTTON_HEIGHT, 1, 2, m_CurrentScreenResolution.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreenResolution.BUTTON_VERTICAL_OFFSET));
    ClickManager::GetInstance().AddButton(new ButtonDistrictCancel(m_CurrentScreenResolution.DISTRICT_MENU_BUTTON_HEIGHT, 2, 2, m_CurrentScreenResolution.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreenResolution.BUTTON_VERTICAL_OFFSET));

    //Units
    ClickManager::GetInstance().AddButton(new ButtonUnitAttack(m_CurrentScreenResolution.UNIT_MENU_BUTTON_HEIGHT, 1, 1, m_CurrentScreenResolution.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreenResolution.BUTTON_VERTICAL_OFFSET));
    ClickManager::GetInstance().AddButton(new ButtonUnitHeal(m_CurrentScreenResolution.UNIT_MENU_BUTTON_HEIGHT, 2, 1, m_CurrentScreenResolution.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreenResolution.BUTTON_VERTICAL_OFFSET));
    ClickManager::GetInstance().AddButton(new ButtonUnitUpgrade(m_CurrentScreenResolution.UNIT_MENU_BUTTON_HEIGHT, 1, 2, m_CurrentScreenResolution.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreenResolution.BUTTON_VERTICAL_OFFSET));
    ClickManager::GetInstance().AddButton(new ButtonUnitSell(m_CurrentScreenResolution.UNIT_MENU_BUTTON_HEIGHT, 2, 2, m_CurrentScreenResolution.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreenResolution.BUTTON_VERTICAL_OFFSET));
    ClickManager::GetInstance().AddButton(new ButtonUnitMove(m_CurrentScreenResolution.UNIT_MENU_BUTTON_HEIGHT, 1, 3, m_CurrentScreenResolution.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreenResolution.BUTTON_VERTICAL_OFFSET));
    ClickManager::GetInstance().AddButton(new ButtonUnitCancel(m_CurrentScreenResolution.UNIT_MENU_BUTTON_HEIGHT, 2, 3, m_CurrentScreenResolution.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreenResolution.BUTTON_VERTICAL_OFFSET));

    //Menu
    ClickManager::GetInstance().AddButton(new ButtonMenu(0, 1, 1, m_CurrentScreenResolution.MAX_WIDTH - 100, 10, ButtonState::Unpressed));
}

void GameWindow::LoadLocalTextures()
{
    m_ressourcesFont = TTF_OpenFont("Resources\\Fonts\\roboto\\Roboto-Light.ttf", 20);
    m_infoFont = TTF_OpenFont("Resources\\Fonts\\roboto\\Roboto-Light.ttf", 16);
    assert(m_ressourcesFont != NULL && TTF_GetError());
    assert(m_infoFont != NULL && TTF_GetError());

    m_foodTexture = new Texture();
    m_weaponTexture = new Texture();
    m_scienceTexture = new Texture();
    m_overlayTexture = new Texture();
    m_selectdOverlayTexture = new Texture();

    try
    {
        // Do not remove the renderer from this call otherwise the Load from file will call
        // GetInstance of game window wich will lead us back here and.... you know the rest INFINITY LOOP
        m_foodTexture->LoadFromFile("Resources\\Sprite\\Resources\\64x64\\food.bmp", m_renderer);

        m_weaponTexture->LoadFromFile("Resources\\Sprite\\Resources\\64x64\\weapons.bmp", m_renderer);

        m_scienceTexture->LoadFromFile("Resources\\Sprite\\Resources\\64x64\\science.bmp", m_renderer);

        m_overlayTexture->LoadFromFile("Resources\\Sprite\\overlay.bmp", m_renderer);

        m_selectdOverlayTexture->LoadFromFile("Resources\\Sprite\\selectedOverlay.bmp", m_renderer);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

void GameWindow::ShowWindow()
{
    while (!m_doQuit)
    {
        SDL_Event e;

        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                m_doQuit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONUP)
            {
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    if (SDL_GetWindowID(m_window) == e.button.windowID && !IsGameWindowInBackground())
                    {
                        if (IsClickInMap(e.button.x, e.button.y))
                        {
                            int posCol = ((e.button.x - m_CurrentScreenResolution.HUD_WIDTH) / m_CurrentScreenResolution.TILE_SIZE) + m_currentLeftmostColumn;
                            posCol %= Map::COLUMNS;

                            int posRow = ((e.button.y - m_CurrentScreenResolution.HUD_HEIGHT) / m_CurrentScreenResolution.TILE_SIZE) + m_currentLowestRow;
                            posRow %= Map::ROWS;

                            ClickManager::GetInstance().ManageMapClick(Position(posCol, posRow));
                        }
                        else if (IsClickInMinimap(e.button.x, e.button.y))
                        {
                            int posCol = ((e.button.x - m_CurrentScreenResolution.MINIMAP_POSX) / m_CurrentScreenResolution.MINIMAP_TILE_SIZE) - (m_CurrentScreenResolution.NUM_TILE_WIDTH / 2);
                            if (posCol < 0)
                            {
                                posCol += Map::COLUMNS;
                            }

                            m_currentLeftmostColumn = posCol;

                            int posRow = ((e.button.y - m_CurrentScreenResolution.MINIMAP_POSY) / m_CurrentScreenResolution.MINIMAP_TILE_SIZE) - (m_CurrentScreenResolution.NUM_TILE_HEIGHT / 2);
                            if (posRow < 0)
                            {
                                posRow += Map::ROWS;
                            }
                            m_currentLowestRow = posRow;
                        }
                        else
                        {
                            ClickManager::GetInstance().ManageMenuClick(e.button.x, e.button.y);
                        }
                    }


                    else
                    {
                        PopUpWindow* popUpToRemove = nullptr;
                        for (PopUpWindow* popUp : m_activePopUpWindow)
                        {
                            SDL_RaiseWindow(popUp->GetWindow());
                            if (SDL_GetWindowID(popUp->GetWindow()) == e.button.windowID)
                            {
                                if (popUp->handleEvent(e))
                                {
                                    popUpToRemove = popUp;
                                }
                                break;
                            }
                        }

                        if (popUpToRemove != nullptr)
                        {
                            //Remove it from the vector
                            m_activePopUpWindow.erase(std::remove(m_activePopUpWindow.begin(), m_activePopUpWindow.end(), popUpToRemove), m_activePopUpWindow.end());
                            popUpToRemove->Close();
                            SelectionManager::GetInstance().UpdateButtonState();
                        }
                    }
                }
                else if (e.button.button == SDL_BUTTON_RIGHT)
                {
                    if (IsClickInMap(e.button.x, e.button.y))
                    {
                        int posCol = ((e.button.x - m_CurrentScreenResolution.HUD_WIDTH) / m_CurrentScreenResolution.TILE_SIZE) + m_currentLeftmostColumn;
                        posCol %= Map::COLUMNS;

                        int posRow = ((e.button.y - m_CurrentScreenResolution.HUD_HEIGHT) / m_CurrentScreenResolution.TILE_SIZE) + m_currentLowestRow;
                        posRow %= Map::ROWS;

                        ClickManager::GetInstance().ManageMapRightClickUnpressed(Position(posCol, posRow));
                    }
                }
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (e.button.button == SDL_BUTTON_RIGHT)
                {
                    if (IsClickInMap(e.button.x, e.button.y))
                    {
                        int posCol = ((e.button.x - m_CurrentScreenResolution.HUD_WIDTH) / m_CurrentScreenResolution.TILE_SIZE) + m_currentLeftmostColumn;
                        posCol %= Map::COLUMNS;

                        int posRow = ((e.button.y - m_CurrentScreenResolution.HUD_HEIGHT) / m_CurrentScreenResolution.TILE_SIZE) + m_currentLowestRow;
                        posRow %= Map::ROWS;

                        ClickManager::GetInstance().ManageMapRightClickPressed(Position(posCol, posRow));
                    }
                }
            }
            else if (e.type == SDL_KEYDOWN && !IsGameWindowInBackground())
            {
                switch (e.key.keysym.sym)
                {
                case (SDLK_UP) :
                    if (m_currentLowestRow > 0)
                    {
                        m_currentLowestRow--;
                    }
                    else
                    {
                        m_currentLowestRow = Map::ROWS - 1;
                    }
                               break;
                case (SDLK_LEFT) :
                    if (m_currentLeftmostColumn > 0)
                    {
                        m_currentLeftmostColumn--;
                    }
                    else
                    {
                        m_currentLeftmostColumn = Map::COLUMNS - 1;
                    }
                                 break;
                case (SDLK_RIGHT) :
                    m_currentLeftmostColumn = (m_currentLeftmostColumn + 1) % (Map::COLUMNS);
                    break;
                case (SDLK_DOWN) :
                    m_currentLowestRow = (m_currentLowestRow + 1) % (Map::ROWS);
                    break;
                }
            }
        }
        
        //Clear screen
        SDL_SetRenderDrawColor(m_renderer, 32, 32, 32, 0);
        SDL_RenderClear(m_renderer);
        auto currentPlayer = GameSession::GetInstance().GetCurrentPlayerCopy();
        //Render UI
        //Render ressources and turns
        {
            SDL_Color textColor = { 255, 255, 255 };


            /************
                FOOD
            *************/
            int iconTextSpacing = 5;
            int x = m_CurrentScreenResolution.HUD_WIDTH;
            int yIcon = 10;
            int widthIcon = 64;
            int heightIcon = 64;
            int widthText = 0;
            int heightText = 0;
            int yText = 0;

            SDL_Rect renderQuadFood = { x, yIcon, widthIcon, heightIcon };
            SDL_RenderCopy(m_renderer, m_foodTexture->GetTexture(), NULL, &renderQuadFood);

            std::string foodRessourceToDisplay = std::to_string(currentPlayer->GetPrintableFoodQuantity()) + " (+"
                                               + std::to_string(currentPlayer->GetPrintableFoodPerTurn()) + ")";

            SDL_Surface *foodSurf = TTF_RenderText_Solid(m_ressourcesFont, foodRessourceToDisplay.c_str(), textColor);
            assert(foodSurf != NULL && TTF_GetError());

            SDL_Texture* foodTextTexture = SDL_CreateTextureFromSurface(m_renderer, foodSurf);
            assert(foodTextTexture != NULL && TTF_GetError());

            x += widthIcon + iconTextSpacing;
            widthText = foodSurf->w;
            heightText = foodSurf->h;
            yText = yIcon + heightIcon - heightText;

            SDL_Rect renderQuadFoodValue = { x, yText, widthText, heightText };
            SDL_RenderCopy(m_renderer, foodTextTexture, NULL, &renderQuadFoodValue);
            SDL_DestroyTexture(foodTextTexture);
            SDL_FreeSurface(foodSurf);

            /************
                WEAPON
            *************/
            x += widthIcon + widthText + iconTextSpacing;

            SDL_Rect renderQuadWeapon = { x, yIcon, widthIcon, heightIcon };
            SDL_RenderCopy(m_renderer, m_weaponTexture->GetTexture(), NULL, &renderQuadWeapon);

            std::string weaponRessourceToDisplay = std::to_string(currentPlayer->GetPrintableWeaponQuantity()) + " (+"
                                                  + std::to_string(currentPlayer->GetPrintableWeaponPerTurn()) + ")";

            SDL_Surface *weaponSurf = TTF_RenderText_Solid(m_ressourcesFont, weaponRessourceToDisplay.c_str(), textColor);
            assert(weaponSurf != NULL && TTF_GetError());

            SDL_Texture* weaponTextTexture = SDL_CreateTextureFromSurface(m_renderer, weaponSurf);
            assert(weaponTextTexture != NULL && TTF_GetError());

            x += widthIcon + iconTextSpacing;
            widthText = weaponSurf->w;
            heightText = weaponSurf->h;

            SDL_Rect renderQuadWeaponValue = { x, yText, widthText, heightText };
            SDL_RenderCopy(m_renderer, weaponTextTexture, NULL, &renderQuadWeaponValue);
            SDL_DestroyTexture(weaponTextTexture);
            SDL_FreeSurface(weaponSurf);

            /************
                SCIENCE
            *************/
            x += widthIcon + widthText + iconTextSpacing;

            SDL_Rect renderQuadScience = { x, yIcon, widthIcon, heightIcon };
            SDL_RenderCopy(m_renderer, m_scienceTexture->GetTexture(), NULL, &renderQuadScience);

            std::string scienceRessourceToDisplay = std::to_string(currentPlayer->GetPrintableScienceQuantity()) + " (+"
                                                  + std::to_string(currentPlayer->GetPrintableSciencePerTurn()) + ")";

            SDL_Surface *scienceSurf = TTF_RenderText_Solid(m_ressourcesFont, scienceRessourceToDisplay.c_str(), textColor);
            assert(scienceSurf != NULL && TTF_GetError());

            SDL_Texture* scienceTextTexture = SDL_CreateTextureFromSurface(m_renderer, scienceSurf);
            assert(scienceTextTexture != NULL && TTF_GetError());

            x += widthIcon + iconTextSpacing;
            widthText = scienceSurf->w;
            heightText = scienceSurf->h;

            SDL_Rect renderQuadScienceValue = { x, yText, widthText, heightText };
            SDL_RenderCopy(m_renderer, scienceTextTexture, NULL, &renderQuadScienceValue);
            SDL_DestroyTexture(scienceTextTexture);
            SDL_FreeSurface(scienceSurf);

            /************
                TURN
            *************/
            x += widthIcon + widthText + iconTextSpacing;
            std::string turnText = "Turn : ";
            turnText.append(std::to_string(GameSession::GetInstance().GetWorldState()->GetCurrentTurn()));

            SDL_Surface* turnSurf = TTF_RenderText_Solid(m_ressourcesFont, turnText.c_str(), textColor);
            assert(turnSurf != NULL && TTF_GetError());

            SDL_Texture* turnTextTexture = SDL_CreateTextureFromSurface(m_renderer, turnSurf);
            assert(turnTextTexture != NULL && TTF_GetError());

            widthText = turnSurf->w;
            heightText = turnSurf->h;

            SDL_Rect renderQuadTurnValue = { x, yText, widthText, heightText };
            SDL_RenderCopy(m_renderer, turnTextTexture, NULL, &renderQuadTurnValue);
            SDL_DestroyTexture(turnTextTexture);
            SDL_FreeSurface(turnSurf);
        }


        //Render Map
        auto map = GameSession::GetInstance().GetWorldState()->GetMapCopy();

        //Set overlay visible to true
        std::vector<Position> overlayTiles = SelectionManager::GetInstance().GetOverlayTiles();
        for (Position pos : overlayTiles)
        {
            map->GetTile(pos)->SetOverlayVisible(true);
        }

        int rowIndex = m_currentLowestRow;
        for (int row = 0; row <= m_CurrentScreenResolution.NUM_TILE_HEIGHT; ++row)
        {
            int columnIndex = m_currentLeftmostColumn;
            for (int column = 0; column <= m_CurrentScreenResolution.NUM_TILE_WIDTH; ++column)
            {
                Position pos{ columnIndex, rowIndex };
                TileBase* tile = map->GetTile(pos);
                Texture* tileTexture = tile->GetTexture();

                bool isDiscovered = tile->IsDiscovered(GameSession::GetInstance().GetCurrentPlayerID());
                bool isSeen = tile->IsSeen(GameSession::GetInstance().GetCurrentPlayerID());

                //Position the tile on the screen
                int xPos = m_CurrentScreenResolution.HUD_WIDTH + (column * m_CurrentScreenResolution.TILE_SIZE);
                int yPos = m_CurrentScreenResolution.HUD_HEIGHT + (row * m_CurrentScreenResolution.TILE_SIZE);
                SDL_Rect renderQuad = { xPos, yPos, tileTexture->GetWidth(), tileTexture->GetHeight() };

                if (!currentPlayer->GetUtilitySkillTree().NoFogOfWar && !isDiscovered)
                {
                    tileTexture->SetColor(MAP_FOW);
                }
                else if (tile->GetPlayerOwnerId() >= 0)
                {
                    tileTexture->SetColor(PLAYER_BORDER_COLORS[tile->GetPlayerOwnerId()]);
                }
                else if (isSeen)
                {
                    tileTexture->SetColor(EMPTY_COLOR);
                }
                else
                {
                    tileTexture->SetColor(MAP_NOVISIBILITY);
                }

                //Render the tile
                SDL_RenderCopy(m_renderer, tileTexture->GetTexture(), NULL, &renderQuad);

                if (isDiscovered)
                {
                    //Render the district
                    auto district = tile->GetDistrict();
                    if (district)
                    {
                        Texture* districtTexture = district->GetTexture();
                        districtTexture->SetColor(PLAYER_ACTOR_COLORS[district->GetOwnerID()]);
                        SDL_RenderCopy(m_renderer, districtTexture->GetTexture(), NULL, &renderQuad);
                    }

                    if (isSeen)
                    {
                        //Render the unit
                        auto unit = tile->GetUnit();
                        if (unit)
                        {
                            if (map->GetTile(unit->GetPosition())->GetTypeAsInt() == TileWater::TILE_TYPE)
                            {
                                Texture* selectedUnitBoatTexture = unit->GetBoatTexture();
                                selectedUnitBoatTexture->SetColor(PLAYER_ACTOR_COLORS[unit->GetOwnerID()]);
                                SDL_Rect renderQuadBoat = { xPos, yPos, selectedUnitBoatTexture->GetWidth(), selectedUnitBoatTexture->GetHeight() };
                                SDL_RenderCopy(m_renderer, selectedUnitBoatTexture->GetTexture(), NULL, &renderQuadBoat);
                            }
                            Texture* unitTexture = unit->GetUnitTexture();
                            unitTexture->SetColor(PLAYER_ACTOR_COLORS[unit->GetOwnerID()]);
                            SDL_RenderCopy(m_renderer, unitTexture->GetTexture(), NULL, &renderQuad);
                        }
                    }
                    //Render the overlay
                    if (tile->GetOverlayVisible())
                    {
                        SDL_RenderCopy(m_renderer, m_overlayTexture->GetTexture(), NULL, &renderQuad);
                    }

                    if (SelectionManager::GetInstance().GetSelectedPosition() == pos)
                    {
                        SDL_RenderCopy(m_renderer, m_selectdOverlayTexture->GetTexture(), NULL, &renderQuad);
                    }
                }
                columnIndex = (columnIndex + 1) % (Map::COLUMNS);
            }
            rowIndex = (rowIndex + 1) % (Map::ROWS);

        }

        /************
        MINIMAP
        *************/
        //Draw background
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        SDL_Rect minimapBackgroundQuad =
        {
            m_CurrentScreenResolution.MINIMAP_BORDER_X,
            m_CurrentScreenResolution.MINIMAP_BORDER_Y,
            (m_CurrentScreenResolution.MINIMAP_TILE_SIZE * Map::COLUMNS) + m_CurrentScreenResolution.MINIMAP_BORDER,
            (m_CurrentScreenResolution.MINIMAP_TILE_SIZE * Map::ROWS) + m_CurrentScreenResolution.MINIMAP_BORDER
        };

        SDL_RenderFillRect(m_renderer, &minimapBackgroundQuad);

        //Draw minimap
        int posRow = m_CurrentScreenResolution.MINIMAP_POSY;
        for (int row = 0; row < Map::ROWS; ++row)
        {
            int posColumn = m_CurrentScreenResolution.MINIMAP_POSX;
            for (int column = 0; column < Map::COLUMNS; ++column)
            {
                SDL_Rect tileQuad = { posColumn, posRow, m_CurrentScreenResolution.MINIMAP_TILE_SIZE, m_CurrentScreenResolution.MINIMAP_TILE_SIZE };
                TileBase* tile = map->GetTile(Position(column, row));
                Color tileColor;

                if (!tile->IsDiscovered(GameSession::GetInstance().GetCurrentPlayerID()))
                {
                    tileColor = MAP_FOW;
                }
                else if (tile->GetDistrict() != nullptr && tile->GetDistrict()->GetTypeAsInt() == DistrictCityCenter::DISTRICT_TYPE)
                {
                    tileColor = MINIMAP_CITY;
                }
                else if (tile->GetPlayerOwnerId() >= 0)
                {
                    tileColor = PLAYER_BORDER_COLORS[tile->GetPlayerOwnerId()];
                }
                else
                {
                    tileColor = tile->GetMinimapColor();
                }

                SDL_SetRenderDrawColor(m_renderer, tileColor.m_red, tileColor.m_green, tileColor.m_blue, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(m_renderer, &tileQuad);
                posColumn += m_CurrentScreenResolution.MINIMAP_TILE_SIZE;
            }
            posRow += m_CurrentScreenResolution.MINIMAP_TILE_SIZE;
        }

        //Draw current camera rectangle(s)
        int currentCamRow = m_CurrentScreenResolution.MINIMAP_POSX + m_currentLeftmostColumn * m_CurrentScreenResolution.MINIMAP_TILE_SIZE;
        int currentCamColumn = m_CurrentScreenResolution.MINIMAP_POSY + m_currentLowestRow * m_CurrentScreenResolution.MINIMAP_TILE_SIZE;
        int camWidth = currentCamRow + ((m_CurrentScreenResolution.NUM_TILE_WIDTH + 1) * m_CurrentScreenResolution.MINIMAP_TILE_SIZE);//+1 because we start counting at 0
        int camHeight = currentCamColumn + ((m_CurrentScreenResolution.NUM_TILE_HEIGHT + 1) * m_CurrentScreenResolution.MINIMAP_TILE_SIZE);//+1 because we start counting at 0
        int heightOverflow = camHeight - m_CurrentScreenResolution.MAX_HEIGHT + (m_CurrentScreenResolution.MINIMAP_BORDER / 2);
        int widthOverflow = camWidth - m_CurrentScreenResolution.MAX_WIDTH + (m_CurrentScreenResolution.MINIMAP_BORDER / 2);

        //white rectangles
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        //leftOverflow
        if (widthOverflow > 0)
        {
            SDL_Rect minimapLeftOverflow = { m_CurrentScreenResolution.MINIMAP_POSX, currentCamColumn, widthOverflow, camHeight - currentCamColumn };
            SDL_RenderDrawRect(m_renderer, &minimapLeftOverflow);
            camWidth = m_CurrentScreenResolution.MAX_WIDTH;
        }

        //upOverflow
        if (heightOverflow > 0)
        {
            SDL_Rect minimapUpOverflow = { currentCamRow, m_CurrentScreenResolution.MINIMAP_POSY, camWidth - currentCamRow, heightOverflow };
            SDL_RenderDrawRect(m_renderer, &minimapUpOverflow);
            camHeight = m_CurrentScreenResolution.MAX_HEIGHT;
        }

        //upLeftOverflow
        if (heightOverflow > 0 && widthOverflow > 0)
        {
            SDL_Rect minimapUpLeftOverflow = { m_CurrentScreenResolution.MINIMAP_POSX, m_CurrentScreenResolution.MINIMAP_POSY, widthOverflow, heightOverflow };
            SDL_RenderDrawRect(m_renderer, &minimapUpLeftOverflow);
        }

        //CurrentCamera
        SDL_Rect minimapCurrentCamera = { currentCamRow, currentCamColumn, camWidth - currentCamRow, camHeight - currentCamColumn };
        SDL_RenderDrawRect(m_renderer, &minimapCurrentCamera);

        //Render Buttons
        const std::vector<Button*> Buttons = ClickManager::GetInstance().GetButtons();
        for (Button* button : Buttons)
        {
            //the button
            Texture* buttonTexture = button->GetButtonTexture();
            int buttonX = button->GetLeftX();
            int buttonY = button->GetTopY();

            //this will stretch the texture to the following width/height
            int buttonWidth = button->GetWidth();
            int buttonHeight = button->GetHeight();
            SDL_Rect buttonRect = { buttonX, buttonY, buttonWidth, buttonHeight };
            SDL_RenderCopy(m_renderer, buttonTexture->GetTexture(), NULL, &buttonRect);

            //the text on the button
            Texture * textTexture = button->GetTextTexture();
            int textH = textTexture->GetHeight();
            int textW = textTexture->GetWidth();
            int horizontalOffset = (buttonWidth - textW) / 2;
            int verticalOffset = (buttonHeight - textH) / 2;
            SDL_Rect textRect = { buttonX + horizontalOffset, buttonY + verticalOffset, textW, textH };
            SDL_RenderCopy(m_renderer, textTexture->GetTexture(), NULL, &textRect);
        }

        //Render Selected district
        {
            auto selectedDistrict = SelectionManager::GetInstance().GetSelectedDistrict();
            Texture* selectedDistrictTexture = selectedDistrict->GetTexture();
            int xPos = m_CurrentScreenResolution.BUTTON_HORIZONTAL_OFFSET;
            int yPos = m_CurrentScreenResolution.SELECTED_DISTRICT_HEIGHT;
            SDL_Rect renderQuad = { xPos, yPos, selectedDistrictTexture->GetWidth(), selectedDistrictTexture->GetHeight() };

            //Remove Color and render
            selectedDistrictTexture->SetColor(EMPTY_COLOR);
            SDL_RenderCopy(m_renderer, selectedDistrictTexture->GetTexture(), NULL, &renderQuad);

            SDL_Color textColor = { 255, 255, 255 };
            int iconTextSpacing = 5;
            int widthIcon = 64;
            int heightIcon = 64;
            int widthText = 0;
            int heightText = 0;
            int yText = 0;

            if (selectedDistrict->GetTypeAsInt() != DistrictEmpty::DISTRICT_TYPE)
            {
                bool isInVision = map->GetTile(selectedDistrict->GetPosition())->IsSeen(GameSession::GetInstance().GetCurrentPlayerID());

                xPos += widthIcon + iconTextSpacing;

                /************
                NAME
                *************/
                {
                    SDL_Surface* nameSurface = TTF_RenderText_Solid(m_infoFont, selectedDistrict->GetName(), textColor);
                    assert(nameSurface != NULL && TTF_GetError());

                    SDL_Texture* nameTextTexture = SDL_CreateTextureFromSurface(m_renderer, nameSurface);
                    assert(nameTextTexture != NULL && TTF_GetError());

                    widthText = nameSurface->w;
                    heightText = nameSurface->h;

                    SDL_Rect renderQuadTurnValue = { xPos, yPos, widthText, heightText };
                    SDL_RenderCopy(m_renderer, nameTextTexture, NULL, &renderQuadTurnValue);
                    SDL_DestroyTexture(nameTextTexture);
                    SDL_FreeSurface(nameSurface);
                }
                yPos += heightText;

                /************
                HEALTH
                *************/
                {
                    std::string healthText = "Health : ";

                    if (isInVision)
                    {
                        healthText.append(std::to_string(selectedDistrict->GetHealth()));
                        healthText.append("/");
                        healthText.append(std::to_string(selectedDistrict->GetMaxHealth()));
                    }
                    else
                    {
                        healthText.append("???/???");
                    }

                    SDL_Surface* healthSurface = TTF_RenderText_Solid(m_infoFont, healthText.c_str(), textColor);
                    assert(healthSurface != NULL && TTF_GetError());

                    SDL_Texture* healthTextTexture = SDL_CreateTextureFromSurface(m_renderer, healthSurface);
                    assert(healthTextTexture != NULL && TTF_GetError());

                    widthText = healthSurface->w;
                    heightText = healthSurface->h;

                    SDL_Rect renderQuadTurnValue = { xPos, yPos, widthText, heightText };
                    SDL_RenderCopy(m_renderer, healthTextTexture, NULL, &renderQuadTurnValue);
                    SDL_DestroyTexture(healthTextTexture);
                    SDL_FreeSurface(healthSurface);
                }
                yPos += heightText;

                /************
                ATTACK
                *************/
                {
                    std::string attackText = "Atk dmg : ";
                    if (isInVision)
                    {
                        attackText.append(std::to_string(selectedDistrict->GetAttackDamage() / 2));
                    }
                    else
                    {
                        attackText.append("???");
                    }

                    SDL_Surface* attackSurface = TTF_RenderText_Solid(m_infoFont, attackText.c_str(), textColor);
                    assert(attackSurface != NULL && TTF_GetError());

                    SDL_Texture* attackTextTexture = SDL_CreateTextureFromSurface(m_renderer, attackSurface);
                    assert(attackTextTexture != NULL && TTF_GetError());

                    widthText = attackSurface->w;
                    heightText = attackSurface->h;

                    SDL_Rect renderQuadTurnValue = { xPos, yPos, widthText, heightText };
                    SDL_RenderCopy(m_renderer, attackTextTexture, NULL, &renderQuadTurnValue);
                    SDL_DestroyTexture(attackTextTexture);
                    SDL_FreeSurface(attackSurface);
                }
                yPos += heightText;

                /************
                Ressource given
                *************/
                if (selectedDistrict->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID())
                {
                    int positionX = xPos;

                    /*************
                      Food yield
                    *************/
                    if (selectedDistrict->GetFoodYield() > 0)
                    {
                        SDL_Rect renderQuadScience = { positionX, yPos, heightText, heightText };
                        SDL_RenderCopy(m_renderer, m_foodTexture->GetTexture(), NULL, &renderQuadScience);

                        positionX += heightText + 2;

                        std::string foodYieldText = to_string(selectedDistrict->GetFoodYield());
                        SDL_Surface* foodYieldTextSurface = TTF_RenderText_Solid(m_infoFont, foodYieldText.c_str(), textColor);
                        assert(foodYieldTextSurface != NULL && TTF_GetError());

                        SDL_Texture* foodYieldTextTexture = SDL_CreateTextureFromSurface(m_renderer, foodYieldTextSurface);
                        assert(foodYieldTextTexture != NULL && TTF_GetError());

                        widthText = foodYieldTextSurface->w;
                        heightText = foodYieldTextSurface->h;

                        SDL_Rect renderQuadTurnValue = { positionX, yPos, widthText, heightText };
                        SDL_RenderCopy(m_renderer, foodYieldTextTexture, NULL, &renderQuadTurnValue);
                        SDL_DestroyTexture(foodYieldTextTexture);
                        SDL_FreeSurface(foodYieldTextSurface);

                        positionX += widthText + 5;
                    }

                    /*************
                    Weapon yield
                    *************/
                    if (selectedDistrict->GetWeaponYield() > 0)
                    {
                        SDL_Rect renderQuadScience = { positionX, yPos, heightText, heightText };
                        SDL_RenderCopy(m_renderer, m_weaponTexture->GetTexture(), NULL, &renderQuadScience);

                        positionX += heightText + 2;

                        std::string weaponYieldText = to_string(selectedDistrict->GetWeaponYield());
                        SDL_Surface* weaponYieldTextSurface = TTF_RenderText_Solid(m_infoFont, weaponYieldText.c_str(), textColor);
                        assert(weaponYieldTextSurface != NULL && TTF_GetError());

                        SDL_Texture* weaponYieldTextTexture = SDL_CreateTextureFromSurface(m_renderer, weaponYieldTextSurface);
                        assert(weaponYieldTextTexture != NULL && TTF_GetError());

                        widthText = weaponYieldTextSurface->w;
                        heightText = weaponYieldTextSurface->h;

                        SDL_Rect renderQuadTurnValue = { positionX, yPos, widthText, heightText };
                        SDL_RenderCopy(m_renderer, weaponYieldTextTexture, NULL, &renderQuadTurnValue);
                        SDL_DestroyTexture(weaponYieldTextTexture);
                        SDL_FreeSurface(weaponYieldTextSurface);

                        positionX += widthText + 5;
                    }

                    /*************
                    Science yield
                    *************/
                    if (selectedDistrict->GetScienceYield() > 0)
                    {
                        SDL_Rect renderQuadScience = { positionX, yPos, heightText, heightText };
                        SDL_RenderCopy(m_renderer, m_scienceTexture->GetTexture(), NULL, &renderQuadScience);

                        positionX += heightText + 2;

                        std::string scienceYieldText = to_string(selectedDistrict->GetScienceYield());
                        SDL_Surface* scienceYieldTextSurface = TTF_RenderText_Solid(m_infoFont, scienceYieldText.c_str(), textColor);
                        assert(scienceYieldTextSurface != NULL && TTF_GetError());

                        SDL_Texture* scienceYieldTextTexture = SDL_CreateTextureFromSurface(m_renderer, scienceYieldTextSurface);
                        assert(scienceYieldTextTexture != NULL && TTF_GetError());

                        widthText = scienceYieldTextSurface->w;
                        heightText = scienceYieldTextSurface->h;

                        SDL_Rect renderQuadTurnValue = { positionX, yPos, widthText, heightText };
                        SDL_RenderCopy(m_renderer, scienceYieldTextTexture, NULL, &renderQuadTurnValue);
                        SDL_DestroyTexture(scienceYieldTextTexture);
                        SDL_FreeSurface(scienceYieldTextSurface);

                        positionX += widthText + 5;
                    }

                    /*************
                    Food bonus
                    *************/
                    if (selectedDistrict->GetFoodBonus() > 0)
                    {
                        SDL_Rect renderQuadScience = { positionX, yPos, heightText, heightText };
                        SDL_RenderCopy(m_renderer, m_foodTexture->GetTexture(), NULL, &renderQuadScience);

                        positionX += heightText + 2;

                        std::string foodBonusText = to_string(static_cast<int>(selectedDistrict->GetFoodBonus() * 100));
                        foodBonusText.append("%");
                        SDL_Surface* foodBonusTextSurface = TTF_RenderText_Solid(m_infoFont, foodBonusText.c_str(), textColor);
                        assert(foodBonusTextSurface != NULL && TTF_GetError());

                        SDL_Texture* foodBonusTextTexture = SDL_CreateTextureFromSurface(m_renderer, foodBonusTextSurface);
                        assert(foodBonusTextTexture != NULL && TTF_GetError());

                        widthText = foodBonusTextSurface->w;
                        heightText = foodBonusTextSurface->h;

                        SDL_Rect renderQuadTurnValue = { positionX, yPos, widthText, heightText };
                        SDL_RenderCopy(m_renderer, foodBonusTextTexture, NULL, &renderQuadTurnValue);
                        SDL_DestroyTexture(foodBonusTextTexture);
                        SDL_FreeSurface(foodBonusTextSurface);

                        positionX += widthText + 5;
                    }

                    /*************
                    Science bonus
                    *************/
                    if (selectedDistrict->GetScienceBonus() > 0)
                    {
                        SDL_Rect renderQuadScience = { positionX, yPos, heightText, heightText };
                        SDL_RenderCopy(m_renderer, m_scienceTexture->GetTexture(), NULL, &renderQuadScience);

                        positionX += heightText + 2;

                        std::string scienceBonusText = to_string(static_cast<int>(selectedDistrict->GetScienceBonus() * 100));
                        scienceBonusText.append("%");
                        SDL_Surface* scienceBonusTextSurface = TTF_RenderText_Solid(m_infoFont, scienceBonusText.c_str(), textColor);
                        assert(scienceBonusTextSurface != NULL && TTF_GetError());

                        SDL_Texture* scienceBonusTextTexture = SDL_CreateTextureFromSurface(m_renderer, scienceBonusTextSurface);
                        assert(scienceBonusTextTexture != NULL && TTF_GetError());

                        widthText = scienceBonusTextSurface->w;
                        heightText = scienceBonusTextSurface->h;

                        SDL_Rect renderQuadTurnValue = { positionX, yPos, widthText, heightText };
                        SDL_RenderCopy(m_renderer, scienceBonusTextTexture, NULL, &renderQuadTurnValue);
                        SDL_DestroyTexture(scienceBonusTextTexture);
                        SDL_FreeSurface(scienceBonusTextSurface);

                        positionX += widthText + 5;
                    }

                    /*************
                    Weapon bonus
                    *************/
                    if (selectedDistrict->GetWeaponBonus() > 0)
                    {
                        SDL_Rect renderQuadScience = { positionX, yPos, heightText, heightText };
                        SDL_RenderCopy(m_renderer, m_weaponTexture->GetTexture(), NULL, &renderQuadScience);

                        positionX += heightText + 2;

                        std::string weaponBonusText = to_string(static_cast<int>(selectedDistrict->GetWeaponBonus() * 100));
                        weaponBonusText.append("%");
                        SDL_Surface* weaponBonusTextSurface = TTF_RenderText_Solid(m_infoFont, weaponBonusText.c_str(), textColor);
                        assert(weaponBonusTextSurface != NULL && TTF_GetError());

                        SDL_Texture* weaponBonusTextTexture = SDL_CreateTextureFromSurface(m_renderer, weaponBonusTextSurface);
                        assert(weaponBonusTextTexture != NULL && TTF_GetError());

                        widthText = weaponBonusTextSurface->w;
                        heightText = weaponBonusTextSurface->h;

                        SDL_Rect renderQuadTurnValue = { positionX, yPos, widthText, heightText };
                        SDL_RenderCopy(m_renderer, weaponBonusTextTexture, NULL, &renderQuadTurnValue);
                        SDL_DestroyTexture(weaponBonusTextTexture);
                        SDL_FreeSurface(weaponBonusTextSurface);

                        positionX += widthText + 5;
                    }
                }
            }

        }

        //Render Selected unit
        {
            auto selectedUnit = SelectionManager::GetInstance().GetSelectedUnit();
            int xPos = m_CurrentScreenResolution.BUTTON_HORIZONTAL_OFFSET;
            int yPos = m_CurrentScreenResolution.SELECTED_UNIT_HEIGHT;
            if (selectedUnit->GetTypeAsInt() != UnitEmpty::UNIT_TYPE && map->GetTile(selectedUnit->GetPosition())->GetTypeAsInt() == TileWater::TILE_TYPE)
            {
                Texture* selectedUnitBoatTexture = selectedUnit->GetBoatTexture();
                SDL_Rect renderQuadBoat = { xPos, yPos, selectedUnitBoatTexture->GetWidth(), selectedUnitBoatTexture->GetHeight() };
                selectedUnitBoatTexture->SetColor(EMPTY_COLOR);
                SDL_RenderCopy(m_renderer, selectedUnitBoatTexture->GetTexture(), NULL, &renderQuadBoat);
            }
            Texture* selectedUnitTexture = selectedUnit->GetUnitTexture();
            SDL_Rect renderQuad = { xPos, yPos, selectedUnitTexture->GetWidth(), selectedUnitTexture->GetHeight() };

            //Remove Color and render
            selectedUnitTexture->SetColor(EMPTY_COLOR);
            SDL_RenderCopy(m_renderer, selectedUnitTexture->GetTexture(), NULL, &renderQuad);

            SDL_Color textColor = { 255, 255, 255 };
            int iconTextSpacing = 10;
            int widthIcon = 64;
            int widthText = 0;
            int heightText = 0;
            int yText = 0;

            if (selectedUnit->GetTypeAsInt() != UnitEmpty::UNIT_TYPE)
            {
                xPos += widthIcon + iconTextSpacing;

                /************
                NAME
                *************/
                {
                    SDL_Surface* nameSurface = TTF_RenderText_Solid(m_infoFont, selectedUnit->GetName(), textColor);
                    assert(nameSurface != NULL && TTF_GetError());

                    SDL_Texture* nameTextTexture = SDL_CreateTextureFromSurface(m_renderer, nameSurface);
                    assert(nameTextTexture != NULL && TTF_GetError());

                    widthText = nameSurface->w;
                    heightText = nameSurface->h;

                    SDL_Rect renderQuadTurnValue = { xPos, yPos, widthText, heightText };
                    SDL_RenderCopy(m_renderer, nameTextTexture, NULL, &renderQuadTurnValue);
                    SDL_DestroyTexture(nameTextTexture);
                    SDL_FreeSurface(nameSurface);
                }
                yPos += heightText;

                /************
                HEALTH
                *************/
                {
                    std::string healthText = "Health : ";
                    healthText.append(std::to_string(selectedUnit->GetHealth()));
                    healthText.append("/");
                    healthText.append(std::to_string(selectedUnit->GetMaxHealth()));

                    SDL_Surface* healthSurface = TTF_RenderText_Solid(m_infoFont, healthText.c_str(), textColor);
                    assert(healthSurface != NULL && TTF_GetError());

                    SDL_Texture* healthTextTexture = SDL_CreateTextureFromSurface(m_renderer, healthSurface);
                    assert(healthTextTexture != NULL && TTF_GetError());

                    widthText = healthSurface->w;
                    heightText = healthSurface->h;

                    SDL_Rect renderQuadTurnValue = { xPos, yPos, widthText, heightText };
                    SDL_RenderCopy(m_renderer, healthTextTexture, NULL, &renderQuadTurnValue);
                    SDL_DestroyTexture(healthTextTexture);
                    SDL_FreeSurface(healthSurface);
                }
                yPos += heightText;

                /************
                ATTACK
                *************/
                {
                    std::string attackText = "Atk dmg : ";
                    attackText.append(std::to_string(selectedUnit->GetAttackDamage()));
                    attackText.append("    Range :");
                    attackText.append(std::to_string(selectedUnit->GetAttackRange()));

                    SDL_Surface* attackSurface = TTF_RenderText_Solid(m_infoFont, attackText.c_str(), textColor);
                    assert(attackSurface != NULL && TTF_GetError());

                    SDL_Texture* attackTextTexture = SDL_CreateTextureFromSurface(m_renderer, attackSurface);
                    assert(attackTextTexture != NULL && TTF_GetError());

                    widthText = attackSurface->w;
                    heightText = attackSurface->h;

                    SDL_Rect renderQuadTurnValue = { xPos, yPos, widthText, heightText };
                    SDL_RenderCopy(m_renderer, attackTextTexture, NULL, &renderQuadTurnValue);
                    SDL_DestroyTexture(attackTextTexture);
                    SDL_FreeSurface(attackSurface);
                }
                yPos += heightText;

                /************
                ACTION
                *************/
                if (selectedUnit->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID())
                {
                    std::string attackText = "Action left : ";
                    attackText.append(std::to_string(selectedUnit->GetActionPointsRemaining()));

                    SDL_Surface* actionSurface = TTF_RenderText_Solid(m_infoFont, attackText.c_str(), textColor);
                    assert(actionSurface != NULL && TTF_GetError());

                    SDL_Texture* actionTextTexture = SDL_CreateTextureFromSurface(m_renderer, actionSurface);
                    assert(actionTextTexture != NULL && TTF_GetError());

                    widthText = actionSurface->w;
                    heightText = actionSurface->h;

                    SDL_Rect renderQuadTurnValue = { xPos, yPos, widthText, heightText };
                    SDL_RenderCopy(m_renderer, actionTextTexture, NULL, &renderQuadTurnValue);
                    SDL_DestroyTexture(actionTextTexture);
                    SDL_FreeSurface(actionSurface);
                }
            }
        }
        //Render the different popUps
        for (PopUpWindow* popUp : m_activePopUpWindow)
        {
            popUp->ShowWindow(m_renderer);
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
    TTF_CloseFont(m_ressourcesFont);
    TTF_CloseFont(m_infoFont);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    m_ressourcesFont = NULL;
    m_infoFont = NULL;
    m_window = NULL;
    m_renderer = NULL;

    //Quit SDL subsystems
    TTF_Quit();
    SDL_Quit();
}

bool GameWindow::IsClickInLeftMenu(const int & x, const int & y)
{
    return x < m_CurrentScreenResolution.HUD_WIDTH && 0 < y;
}

void GameWindow::AddPopUpWindow(PopUpWindow * window)
{
    m_activePopUpWindow.emplace_back(window);
}

bool GameWindow::IsGameWindowInBackground()
{
    return m_activePopUpWindow.size() > 0;
}

void GameWindow::RequestQuit()
{
    m_doQuit = true;
}

void GameWindow::ChangeResolution(const ScreenResolution& newRes)
{
    m_CurrentScreenResolution = newRes;
    auto windowType = m_CurrentScreenResolution.FULLSCREEN ? SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_SHOWN;
    SDL_DestroyWindow(m_window);
    m_window = SDL_CreateWindow("GreenShells", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_CurrentScreenResolution.MAX_WIDTH, m_CurrentScreenResolution.MAX_HEIGHT, windowType);
    assert(m_window != NULL && SDL_GetError());
    SDL_DestroyRenderer(m_renderer);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    assert(m_renderer != NULL && SDL_GetError());
    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    ClickManager::GetInstance().ClearButtons();
    CreateButtons();
    LoadLocalTextures();

    UnitBuilder::tBase::ForceReload();
    UnitCannon::tBase::ForceReload();
    UnitEmpty::tBase::ForceReload();
    UnitSettler::tBase::ForceReload();
    UnitShield::tBase::ForceReload();

    UnitArcherI::tBase::ForceReload();
    UnitArcherII::tBase::ForceReload();
    UnitArcherIII::tBase::ForceReload();

    UnitAxemanI::tBase::ForceReload();
    UnitAxemanII::tBase::ForceReload();
 
    UnitMaceI::tBase::ForceReload();
    UnitMaceII::tBase::ForceReload();

    UnitSwordsmanI::tBase::ForceReload();
    UnitSwordsmanII::tBase::ForceReload();
    UnitSwordsmanIII::tBase::ForceReload();

    TileGround::tBase::ForceReload();
    TileMountain::tBase::ForceReload();
    TileWater::tBase::ForceReload();

    DistrictBlacksmith::tBase::ForceReload();
    DistrictCathedral::tBase::ForceReload();
    DistrictCityCenter::tBase::ForceReload();
    DistrictEmpty::tBase::ForceReload();
    DistrictFarm::tBase::ForceReload();
    DistrictFort::tBase::ForceReload();
    DistrictFortress::tBase::ForceReload();
    DistrictHunter::tBase::ForceReload();
    DistrictInn::tBase::ForceReload();
    DistrictMilitaryTent::tBase::ForceReload();
    DistrictMonastery::tBase::ForceReload();
    DistrictSchool::tBase::ForceReload();
    DistrictStable::tBase::ForceReload();
    DistrictTavern::tBase::ForceReload();
    DistrictUniversity::tBase::ForceReload();
    DistrictWarehouse::tBase::ForceReload();
    DistrictWatchTower::tBase::ForceReload();
    DistrictWindMill::tBase::ForceReload();
}

bool GameWindow::IsClickInMap(const int& x, const int& y)
{
    return m_CurrentScreenResolution.HUD_WIDTH < x
        && x < m_CurrentScreenResolution.MAX_WIDTH
        && m_CurrentScreenResolution.HUD_HEIGHT < y
        && y < m_CurrentScreenResolution.MAX_HEIGHT
        && (x < m_CurrentScreenResolution.MINIMAP_BORDER_X || y < m_CurrentScreenResolution.MINIMAP_BORDER_Y - m_CurrentScreenResolution.NEXT_TURN_BUTTON_HEIGHT);
}

bool GameWindow::IsClickInMinimap(const int& x, const int& y)
{
    return  x >= m_CurrentScreenResolution.MINIMAP_POSX
        && x < m_CurrentScreenResolution.MAX_WIDTH
        && y > m_CurrentScreenResolution.MINIMAP_POSY
        && y < m_CurrentScreenResolution.MAX_HEIGHT;
}
