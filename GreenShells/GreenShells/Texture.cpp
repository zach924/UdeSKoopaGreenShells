#include "Texture.h"
#include <SDL.h>
#include <exception>
#include "GameWindow.h"

Texture::Texture()
	:m_texture(), m_width(), m_height()
{
}

Texture::~Texture()
{
	Free();
}

bool Texture::IsLoaded()
{
	return m_IsLoaded;
}

bool Texture::LoadFromFile(std::string path)
{
	Free();
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		std::string msg(SDL_GetError());
		SDL_FreeSurface(loadedSurface);
		throw new std::exception(msg.c_str());
		return false;
	}
	else
	{
		//To remove background of a certain color, might be usefull
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0, 0));

		newTexture = SDL_CreateTextureFromSurface(GameWindow::GetInstance().GetRenderer(), loadedSurface);
		if (newTexture == NULL)
		{
			std::string msg(SDL_GetError());
			SDL_FreeSurface(loadedSurface);
			throw new std::exception(msg.c_str());
			return false;
		}
		else
		{
			m_width = loadedSurface->w;
			m_height = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	m_texture = newTexture;
	m_IsLoaded = m_texture != NULL;
	return m_IsLoaded;
}

void Texture::Free()
{
	if (m_texture != NULL)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
}

void Texture::Render(int x, int y)
{	
	SDL_Rect renderQuad = { x, y, m_width, m_height };
	SDL_RenderCopy(GameWindow::GetInstance().GetRenderer(), m_texture, NULL, &renderQuad);
}

void Texture::SetColor(int red, int green, int blue)
{
	SDL_SetTextureColorMod(m_texture, red, green, blue);
}

int Texture::GetHeight()
{
	return m_height;
}

int Texture::GetWidth()
{
	return m_width;
}

SDL_Texture* Texture::GetTexture()
{
	return m_texture;
}