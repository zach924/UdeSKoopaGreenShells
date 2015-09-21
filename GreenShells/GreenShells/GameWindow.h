#pragma once

#include <SDL.h>

class GameWindow
{
private:
  
    SDL_Window* m_window;

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

    void Init();
    void Show(int width, int height);
    void Close();

};