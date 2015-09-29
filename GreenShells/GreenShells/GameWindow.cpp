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
	//bool loaded = false;
	//Texture* text = new Texture();

	//Map map = GameSession::GetGameSession().GetWorldState()->GetMap();
	//TileBase* tile = map.GetTile(Position(0, 0));
	//Texture text = tile->GetTexture();
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

		//Render Screen
		//this is temporary
		//TileBase* tile= new TileGround(Position(0,0));
		//tile->GetTexture().Render(0, 0);
		Map map = GameSession::GetGameSession().GetWorldState()->GetMap();
		for (int i = 0; i <= 2; ++i)
		{
			for (int j = 0; j <= 2; ++j)
			{
				Texture text = map.GetTile(Position(i, j))->GetTexture();;
				SDL_Rect renderQuad = { i*64, j*64, text.GetWidth(), text.GetHeight() };
				text.SetColor(200, 100, 100);
				SDL_RenderCopy(m_renderer, text.GetTexture(), NULL, &renderQuad);
			}
		}

		//TileBase* tile = map.GetTile(Position(0, 0));
		//Texture text = tile->GetTexture();

		//if(!loaded)
		//{
		//	text->LoadFromFile("..\\Sprite\\Terrain\\64x64\\Grass.bmp");
		//	loaded = true;
		//}


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