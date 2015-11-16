#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <thread>
#include <string>
#include <vector>

class Button;

class PopUpWindow
{

protected:
    TTF_Font * m_font;
    int m_fontSize;
    int m_width;
    SDL_Surface* m_screenSurface;
    std::vector<SDL_Texture*> m_texts;
    SDL_Renderer* m_rend;
    SDL_Window* m_wind;

public:
    PopUpWindow(std::string windowText, int width, int height);
    ~PopUpWindow();

    void Close();

    SDL_Window* GetWindow();
    virtual bool handleEvent(SDL_Event& e) = 0;

    virtual void ShowWindow(SDL_Renderer* rend) = 0;
};
