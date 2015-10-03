#pragma once
#include <SDL.h>
#include <thread>
#include "GameSession.h"

//////////////////////////////////
//Screen Resolution
/////////////////////////////////
struct ScreenResolution
{
	const int TILE_SIZE = 65;

	int HUD_WIDTH;
	int HUD_HEIGHT;
	int MAX_WIDTH;
	int MAX_HEIGHT;
	int MAP_HEIGHT;
	int MAP_WIDTH;
	int NUM_TILE_HEIGHT;
	int NUM_TILE_WIDTH;

	ScreenResolution(int maxW, int maxH, int mapW, int mapH, int hudW, int hudH)
		:MAX_WIDTH(maxW), MAX_HEIGHT(maxH), MAP_WIDTH(mapW), MAP_HEIGHT(mapH), HUD_WIDTH(hudW), HUD_HEIGHT(hudH), NUM_TILE_WIDTH(mapW / TILE_SIZE), NUM_TILE_HEIGHT(mapH / TILE_SIZE)
	{}
};
static ScreenResolution RES_800_600{ 800,600,520,520,280,80 };
static ScreenResolution RES_1280_720{ 1280,720,975,650,305,70 };
static ScreenResolution RES_1600_900{ 1600,900,1300,780,300,120 };
static ScreenResolution RES_1600_1024{ 1600,1024,1300,910,300,114 };
static ScreenResolution RES_1920_1080{ 1920,1080,1625,975,295,105 };


class GameWindow
{
private:
	
	ScreenResolution m_CurrentScreen;

	SDL_Window* m_window;
    SDL_Surface* m_screenSurface;
	SDL_Renderer* m_renderer;

    int m_topMenuHeight;
  	int m_leftMenuWidth;

  	int m_mapHeightEnd;
	  int m_mapWidthEnd;
    GameWindow(ScreenResolution = RES_1600_1024);
    ~GameWindow();

    GameWindow(GameWindow const&) = delete;
    void operator=(GameWindow const&) = delete;

public:
    static GameWindow& GetInstance()
    {
		static GameWindow m_instance{RES_1600_1024};
        return m_instance;
    }

    void ShowWindow();
	SDL_Renderer* GetRenderer();
    void Close();

	bool IsClickInMap(const int& x,const int& y);
	bool IsClickInLeftMenu(const int& x, const int& y);


};