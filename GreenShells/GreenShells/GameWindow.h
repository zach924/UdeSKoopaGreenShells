#pragma once
#include <SDL.h>
#include <thread>
#include "GameSession.h"

class GameWindow
{
private:
    SDL_Window* m_window;
    SDL_Surface* m_screenSurface;
	SDL_Renderer* m_renderer;

	int m_height;
	int m_width;

	int m_topMenuHeight;
	int m_leftMenuWidth;

	int m_mapHeightEnd;
	int m_mapWidthEnd;

    GameWindow(int width = 1600, int height = 1024);
    ~GameWindow();

    GameWindow(GameWindow const&) = delete;
    void operator=(GameWindow const&) = delete;

public:
    static GameWindow& GetInstance()
    {
		static GameWindow m_instance{1600,1024};
        return m_instance;
    }

    void ShowWindow();
	SDL_Renderer* GetRenderer();
    void Close();

	bool IsClickInMap(const int& x,const int& y);
	bool IsClickInLeftMenu(const int& x, const int& y);


};