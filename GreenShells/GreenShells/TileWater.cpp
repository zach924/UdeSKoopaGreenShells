#include "TileWater.h"

Texture TileWater::m_texture = {};

TileWater::TileWater(Position position)
:Tile(position)
{
	try
	{
		m_texture.LoadFromFile("..\\Sprite\\Terrain\\64x64\\Water.bmp");
	}
	catch (std::exception e)
	{
		//std::cout << e.what();
	}
}


TileWater::~TileWater()
{
}
