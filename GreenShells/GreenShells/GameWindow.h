#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <thread>
#include "GameSession.h"
#include "Texture.h"
#include "PopUpWindow.h"

//////////////////////////////////
//Screen Resolution
/////////////////////////////////
struct ScreenResolution
{
    const int TILE_SIZE = 65;
    const int SELECTED_SPRITES_SIZE = 70;
    const int BUTTON_HORIZONTAL_OFFSET = 25;
    const int MINIMAP_BORDER = 4;
    const int MINIMAP_TILE_SIZE = 4;
    const int NEXT_TURN_BUTTON_HEIGHT = 50;
    const int NEXT_TURN_BUTTON_WIDTH = 260;

    int HUD_WIDTH;
    int HUD_HEIGHT;
    int MAX_WIDTH;
    int MAX_HEIGHT;
    int MAP_HEIGHT;
    int MAP_WIDTH;
    int SELECTED_UNIT_HEIGHT;
    int SELECTED_DISTRICT_HEIGHT;
    int BUTTON_VERTICAL_OFFSET;
    int NUM_TILE_HEIGHT;
    int NUM_TILE_WIDTH;
    int DISTRICT_MENU_BUTTON_HEIGHT;
    int UNIT_MENU_BUTTON_HEIGHT;
    int DOWN_SCROLL_POSITION;
    int UP_SCROLL_POSITION;
    int RIGHT_SCROLL_POSITION;
    int LEFT_SCROLL_POSITION;
    int MINIMAP_POSY;
    int MINIMAP_POSX;
    int MINIMAP_BORDER_X;
    int MINIMAP_BORDER_Y;
    bool FULLSCREEN;

    ScreenResolution(int maxW, int maxH, int mapW, int mapH, int hudW, int hudH, int vOffset, int DistrictH, int UnitH, bool fullScreen)
        :MAX_WIDTH(maxW)
        , MAX_HEIGHT(maxH)
        , MAP_WIDTH(mapW)
        , MAP_HEIGHT(mapH)
        , SELECTED_UNIT_HEIGHT(UnitH - SELECTED_SPRITES_SIZE)
        , SELECTED_DISTRICT_HEIGHT(DistrictH - SELECTED_SPRITES_SIZE)
        , HUD_WIDTH(hudW)
        , HUD_HEIGHT(hudH)
        , BUTTON_VERTICAL_OFFSET(vOffset)
        , NUM_TILE_WIDTH((mapW / TILE_SIZE) - 1)
        , NUM_TILE_HEIGHT((mapH / TILE_SIZE) - 1)
        , DISTRICT_MENU_BUTTON_HEIGHT(DistrictH)
        , UNIT_MENU_BUTTON_HEIGHT(UnitH)
        , DOWN_SCROLL_POSITION(maxH - 15)
        , RIGHT_SCROLL_POSITION(maxW - 15)
        , LEFT_SCROLL_POSITION(hudW + 15)
        , UP_SCROLL_POSITION(hudH + 15)
        , MINIMAP_POSX(maxW - 64 * MINIMAP_TILE_SIZE - MINIMAP_BORDER / 2)
        , MINIMAP_POSY(maxH - 64 * MINIMAP_TILE_SIZE - MINIMAP_BORDER / 2)
        , MINIMAP_BORDER_X(MINIMAP_POSX - MINIMAP_BORDER / 2)
        , MINIMAP_BORDER_Y(MINIMAP_POSY - MINIMAP_BORDER / 2)
        , FULLSCREEN(fullScreen)
    {};
    ScreenResolution& ScreenResolution::operator =(const ScreenResolution& other)
    {
        MAX_WIDTH = other.MAX_WIDTH;
        MAX_HEIGHT = other.MAX_HEIGHT;
        MAP_WIDTH = other.MAP_WIDTH;
        MAP_HEIGHT = other.MAP_HEIGHT;
        SELECTED_UNIT_HEIGHT = other.SELECTED_UNIT_HEIGHT;
        SELECTED_DISTRICT_HEIGHT = other.SELECTED_DISTRICT_HEIGHT;
        HUD_WIDTH = other.HUD_WIDTH;
        HUD_HEIGHT = other.HUD_HEIGHT;
        BUTTON_VERTICAL_OFFSET = other.BUTTON_VERTICAL_OFFSET;
        NUM_TILE_WIDTH = other.NUM_TILE_WIDTH;
        NUM_TILE_HEIGHT = other.NUM_TILE_HEIGHT;
        DISTRICT_MENU_BUTTON_HEIGHT = other.DISTRICT_MENU_BUTTON_HEIGHT;
        UNIT_MENU_BUTTON_HEIGHT = other.UNIT_MENU_BUTTON_HEIGHT;
        DOWN_SCROLL_POSITION = other.DOWN_SCROLL_POSITION;
        RIGHT_SCROLL_POSITION = other.RIGHT_SCROLL_POSITION;
        LEFT_SCROLL_POSITION = other.LEFT_SCROLL_POSITION;
        UP_SCROLL_POSITION = other.UP_SCROLL_POSITION;
        MINIMAP_POSX = other.MINIMAP_POSX;
        MINIMAP_POSY = other.MINIMAP_POSY;
        MINIMAP_BORDER_X = other.MINIMAP_BORDER_X;
        MINIMAP_BORDER_Y = other.MINIMAP_BORDER_Y;
        FULLSCREEN = other.FULLSCREEN;
        return *this;
    };
};
static ScreenResolution RES_800_600{ 800,600,520,520,280,80,5,240,425,false };
static ScreenResolution RES_1280_720{ 1280,720,975,650,305,70,12,292,498,false };
static ScreenResolution RES_1600_900{ 1600,900,1300,780,300,120,25,362,650,false };
static ScreenResolution RES_1600_1024{ 1600,1024,1300,910,300,114,35,410,735,false };
static ScreenResolution RES_1920_1080{ 1920,1080,1625,975,295,105,38,370,664,false };
static ScreenResolution RES_1920_1080_FullScreen{ 1920,1080,1625,975,295,105,38,370,664,true };

class GameWindow
{
private:

    ScreenResolution m_CurrentScreenResolution;
    bool m_doQuit;
    bool m_resChanged;
    GameWindow* m_nextWindow;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    int m_currentLeftmostColumn;
    int m_currentLowestRow;
    bool m_currentlyScrolling;

    std::vector<PopUpWindow*> m_activePopUpWindow;

    //Textures for the window
    TTF_Font* m_ressourcesFont;
    TTF_Font* m_infoFont;
    Texture* m_foodTexture;
    Texture* m_weaponTexture;
    Texture* m_scienceTexture;
    Texture* m_overlayTexture;
    Texture* m_selectdOverlayTexture;

    const Color PLAYER_ACTOR_COLORS[8] =
    {
        Color{ 255,102,102 },
        Color{ 255,255,102 },
        Color{ 102,255,102 },
        Color{ 102,255,255 },
        Color{ 102,102,255 },
        Color{ 255,102,255 },
        Color{ 192,192,192 },
        Color{ 255,180,102 }
    };

    const Color PLAYER_BORDER_COLORS[8] =
    {
        Color{ 255,180,180 },
        Color{ 215,215,115 },
        Color{ 150,255,150 },
        Color{ 050,255,255 },
        Color{ 180,180,255 },
        Color{ 255,102,255 },
        Color{ 192,192,192 },
        Color{ 255,180,102 }
    };

    //Other usefull colors
    const Color MAP_FOW = { 0,0,0 };
    const Color MAP_NOVISIBILITY = { 155,155,155 };
    const Color EMPTY_COLOR = { 255,255,255 };
    const Color MINIMAP_CITY = { 155, 155, 155 };

    GameWindow(ScreenResolution = RES_1280_720);
    ~GameWindow();

    GameWindow(GameWindow const&) = delete;
    void operator=(GameWindow const&) = delete;

    void CreateButtons();
    void LoadLocalTextures();

public:
    static GameWindow& GetInstance()
    {
        static GameWindow m_instance{ RES_1280_720 };
        return m_instance;
    }

    void ShowWindow();
    SDL_Renderer* GetRenderer();
    void Close();

    bool IsClickInMap(const int& x, const int& y);
    bool IsClickInMinimap(const int& x, const int& y);
    bool IsClickInLeftMenu(const int& x, const int& y);

    void AddPopUpWindow(PopUpWindow * window);

    bool IsGameWindowInBackground();

    void RequestQuit();

    void ChangeResolution(const ScreenResolution& newRes);
};