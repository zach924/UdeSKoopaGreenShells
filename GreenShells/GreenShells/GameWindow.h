#pragma once
#include <SDL.h>

class GameWindow
{
private:
    SDL_Window* m_window;
    SDL_Surface* m_screenSurface;
	SDL_Renderer* m_renderer;

	int m_height;
	int m_width;

    GameWindow();
    ~GameWindow();

    GameWindow(GameWindow const&) = delete;
    void operator=(GameWindow const&) = delete;

public:
    static GameWindow& GetInstance()
    {
        static GameWindow m_instance;
        return m_instance;
    }

    void Init(int width = 600, int heigth = 800);
    void Show();
    void Close();

};