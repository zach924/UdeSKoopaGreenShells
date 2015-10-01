#include "TileWater.h"
#include <iostream>
#include <string>

TileWater::TileWater(Position position)
:Tile(position)
{
}

void TileWater::LoadTexture()
{
	try
	{
		TileWater::tBase::m_Texture.LoadFromFile("..\\Sprite\\Terrain\\64x64\\Water.bmp");
	}
	catch (std::exception e)
	{
		std::string msg{ e.what() };
		std::cout << msg << std::endl;
	}
}


TileWater::~TileWater()
{
}
