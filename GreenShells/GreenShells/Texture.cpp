#include "Texture.h"
#include <SDL.h>
#include <exception>
#include <iostream>
#include "GameWindow.h"

Texture::Texture()
    :m_texture(), m_width(), m_height(), m_IsLoaded(false)
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

bool Texture::LoadFromFile(std::string path, SDL_Renderer* rend)
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
        //Removes the black background to have an alpha, might change in the future but works now
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0, 0));
        if (rend == nullptr)
        {
            rend = GameWindow::GetInstance().GetRenderer();
        }
        newTexture = SDL_CreateTextureFromSurface(rend, loadedSurface);
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

bool Texture::CreateFromText(std::string message, TTF_Font * font, SDL_Renderer * rend)
{
    Free();
    SDL_Texture* newTexture = nullptr;
    SDL_Color Color = { 255, 255, 255 };
    SDL_Surface* surface = nullptr;
    if (font == nullptr)
    {
        TTF_Font* tempFont = TTF_OpenFont("Resources\\Fonts\\roboto\\Roboto-BlackItalic.ttf", 20);
        surface = TTF_RenderText_Blended(const_cast<TTF_Font*>(tempFont), message.c_str(), Color);
        TTF_CloseFont(font);
    }
    else
    {
        surface = TTF_RenderText_Blended(const_cast<TTF_Font*>(font), message.c_str(), Color);
    }

    if (surface == NULL)
    {
        std::string msg(SDL_GetError());
        SDL_FreeSurface(surface);
        throw new std::exception(msg.c_str());
        return false;
    }
    else
    {
        if (rend == nullptr)
        {
            rend = GameWindow::GetInstance().GetRenderer();
        }
        newTexture = SDL_CreateTextureFromSurface(rend, surface);
        if (newTexture == NULL)
        {
            std::string msg(SDL_GetError());
            SDL_FreeSurface(surface);
            throw new std::exception(msg.c_str());
            return false;
        }
        else
        {
            m_width = surface->w;
            m_height = surface->h;
        }
        SDL_FreeSurface(surface);
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

void Texture::SetColor(Color color)
{
    SetColor(color.m_red, color.m_green, color.m_blue);
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