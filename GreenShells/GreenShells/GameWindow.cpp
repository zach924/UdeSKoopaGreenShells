#include <iostream>
#include "GameWindow.h"


GameWindow::GameWindow()
{
    m_window = NULL;
}

GameWindow::~GameWindow()
{

}

void GameWindow::Init()
{
    m_window = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }

}

void GameWindow::Show(int width, int height)
{
    bool quit = false;
    //Event handler
    SDL_Event e;

    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //Create window
    m_window = SDL_CreateWindow("GreenShells", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (m_window == NULL)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }
    else
    {
        while (!quit)
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface(m_window);

            //Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            //Update the surface
            SDL_UpdateWindowSurface(m_window);

            //Handle events on queue
            while (SDL_PollEvent(&e) != 0)
            {
                //User requests quit
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }
        }
    }

}

void GameWindow::Close()
{
    //Destroy window
    SDL_DestroyWindow(m_window);

    //Quit SDL subsystems
    SDL_Quit();
}