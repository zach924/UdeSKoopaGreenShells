#include <iostream>
#include "GameWindow.h"


GameWindow::GameWindow()
{
    m_window = NULL;
    m_window = NULL;
}

GameWindow::~GameWindow()
{

}

void GameWindow::Init()
{
    m_window = NULL;
    m_screenSurface = NULL;

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


    //Create window
    m_window = SDL_CreateWindow("GreenShells", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (m_window == NULL)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }
    else
    {
        Display();
    }

}

void GameWindow::Close()
{
    //Destroy window
    SDL_DestroyWindow(m_window);

    //Quit SDL subsystems
    SDL_Quit();
}

void GameWindow::Display()
{

    bool quit = false;
    //Event handler
    SDL_Event e;


    while (!quit)
    {
        //Get window surface
        m_screenSurface = SDL_GetWindowSurface(m_window);


        DrawSprite();

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

void GameWindow::DrawSprite()
{
    SDL_Surface* sprite = NULL;

    
    sprite = SDL_LoadBMP("..\\Sprite\\TestTile.bmp");
    if (sprite != NULL)
    {
        //Apply the image
        SDL_BlitSurface(sprite, NULL, sprite, NULL);
    }
    else
    {
        std::cout << "Unable to load image TestTile.bmp! SDL Error: " << SDL_GetError() << std::endl;
    }
}