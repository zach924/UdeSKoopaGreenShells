#pragma once
#include <string>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Surface;

class Texture
{
public:
	Texture();
	~Texture();

	bool LoadFromFile(std::string path);
	void Free();
	void SetColor(int red, int green, int blue);
	int GetWidth();
	int GetHeight();
	void Render(int x, int y);
private:
	SDL_Texture* m_texture;
	int m_height;
	int m_width;
};

