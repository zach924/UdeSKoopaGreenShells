#include "TileGround.h"

Texture TileGround::m_texture = {};

TileGround::TileGround(Position position)
:Tile(position)
{
	try
	{
		m_texture.LoadFromFile("..\\Sprite\\Terrain\\64x64\\Grass.bmp");
	}
	catch (std::exception e)
	{
		//std::cout << e.what();
	}
}


TileGround::~TileGround()
{
}
