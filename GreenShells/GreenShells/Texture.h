#pragma once
#include <string>

struct SDL_Texture;
struct SDL_Renderer;

class Texture
{
public:
	Texture(SDL_Renderer* renderer);
	~Texture();

	bool LoadFromFile(std::string path);
	void Free();
	void SetColor(int red, int green, int blue);
	void Render(int x, int y);
	int GetWidth();
	int GetHeight();

private:
	static SDL_Surface* m_surface;
	SDL_Texture* m_texture;
	SDL_Renderer* m_renderer;
	int m_height;
	int m_width;
};

