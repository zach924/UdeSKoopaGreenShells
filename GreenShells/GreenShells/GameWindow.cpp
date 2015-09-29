#include <iostream>
#include <sstream>
#include "GameWindow.h"
#include "GameSession.h"
#include "Texture.h"
#include "WorldState.h"
#include <assert.h>
#include "TileGround.h"

GameWindow::GameWindow(int width, int height)
	:m_window(), m_screenSurface(), m_renderer(), m_height(height), m_width(width)
{
	//Initialize SDL
	assert(SDL_Init(SDL_INIT_VIDEO) >= 0 && SDL_GetError());
	
	m_window = SDL_CreateWindow("GreenShells", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);
	assert(m_window != NULL && SDL_GetError());

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	assert(m_renderer != NULL && SDL_GetError());

	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

GameWindow::~GameWindow()
{
	Close();
}

void GameWindow::ShowWindow()
{
	bool quit = false;
	Map* map = GameSession::GetGameSession().GetWorldState()->GetMap();

	bool loaded = false;
	Texture* unit = new Texture();

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
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
		SDL_RenderClear(m_renderer);

		if (!loaded)
		{
			loaded = true;
			unit->LoadFromFile("..\\Sprite\\Units\\64x64\\mace.bmp");
		}

		//Render Screen
		for (int i = 0; i <= 7; ++i)
		{
			for (int j = 0; j <= 10; ++j)
			{
				Texture* texture = map->GetTile(Position(i, j))->GetTexture();
				int x = j * 65;
				int y = i * 65;
				SDL_Rect renderQuad = { x, y, texture->GetWidth(), texture->GetHeight() };
				//texture->SetColor(200, 100, 100);
				SDL_RenderCopy(m_renderer, texture->GetTexture(), NULL, &renderQuad);
			}
		}
		unit->SetColor(210, 125, 125);
		SDL_Rect renderQuad = { 4*65, 4*65, unit->GetWidth(), unit->GetHeight() };
		SDL_RenderCopy(m_renderer, unit->GetTexture(), NULL, &renderQuad);

		//Draw screen
		SDL_RenderPresent(m_renderer);
	}
	Close();
}

SDL_Renderer * GameWindow::GetRenderer()
{
	return m_renderer;
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