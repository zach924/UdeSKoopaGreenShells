#pragma once
#include <string>
#include <SDL_ttf.h>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Surface;

struct Color
{
    int m_red, m_green, m_blue;
};

class Texture
{
public:
    Texture();
    ~Texture();

    bool IsLoaded();
    /*
    * Omitting rend and it will get rendered on the main game window
    */
    bool LoadFromFile(std::string path, SDL_Renderer* rend = nullptr);
    bool CreateFromText(std::string message, TTF_Font* font = nullptr, SDL_Renderer* rend = nullptr);
    void Free();
    void SetColor(Color color);
    void SetColor(int red, int green, int blue);
    int GetWidth();
    int GetHeight();
    SDL_Texture* GetTexture();
    
private:
    void Render(int x, int y);
    SDL_Texture* m_texture;
    int m_height;
    int m_width;
    bool m_IsLoaded;
};
