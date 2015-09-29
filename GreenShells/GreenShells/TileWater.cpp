#include "TileWater.h"

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
		//std::cout << e.what();
	}
}


TileWater::~TileWater()
{
}
