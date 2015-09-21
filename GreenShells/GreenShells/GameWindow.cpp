#include <iostream>
#include "GameWindow.h"
#include "Texture.h"

GameWindow::GameWindow()
	:m_window(), m_screenSurface(), m_renderer(), m_height(), m_width()
{
}

GameWindow::~GameWindow()
{
	Close();
}

void GameWindow::Init(int width, int height)
{
	m_height = height;
	m_width = width;
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return;
	}
	m_window = SDL_CreateWindow("GreenShells", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);
	if (m_window == NULL)
	{
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;	
		return;
	}
	
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer == NULL)
	{
		std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return;
	}

	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void GameWindow::Show()
{
	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	Texture texture(m_renderer);

	if (!texture.LoadFromFile("..\\Sprite\\TestTile.bmp"))
	{
		return;
	}	

	bool quit = false;

	while (!quit)
	{
		SDL_Event e;

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(m_renderer);

		//Render map
		texture.SetColor(255, 0, 0);
		texture.Render(240, 190);

		texture.SetColor(0, 255, 0);
		texture.Render(0, 0);

		texture.SetColor(0, 0, 255);
		texture.Render(100, 100);


		//Update screen
		SDL_RenderPresent(m_renderer);
	}

	Close();
}

void GameWindow::Close()
{
	//Destroy window    
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_window = NULL;
	m_renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}