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

    GameWindow(int width = 800, int height = 600);
    ~GameWindow();

    GameWindow(GameWindow const&) = delete;
    void operator=(GameWindow const&) = delete;

public:
    static GameWindow& GetInstance()
    {
		static GameWindow m_instance{800,600};
        return m_instance;
    }

    void ShowWindow();
	SDL_Renderer* GetRenderer();
    void Close();

};