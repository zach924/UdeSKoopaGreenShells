#include "Texture.h"
#include <SDL.h>

Texture::Texture(SDL_Renderer* renderer)
	:m_texture(), m_width(), m_height(), m_renderer(renderer)
{
}

Texture::~Texture()
{
	Free();
}

bool Texture::LoadFromFile(std::string path)
{
	Free();
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		//std::cout << "Unable to load image TestTile.bmp! SDL Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		//To remove background of a certain color, might be usefull
		//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
		if (newTexture == NULL)
		{
			//std::cout << "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError();
		}
		else
		{
			m_width = loadedSurface->w;
			m_height = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	m_texture = newTexture;
	return m_texture != NULL;
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
	SDL_RenderCopy(m_renderer, m_texture, NULL, &renderQuad);
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
