#include "TileGround.h"

void TileGround::LoadTexture()
{
	try
	{
		TileGround::tBase::m_Texture.LoadFromFile("..\\Sprite\\Terrain\\64x64\\Grass.bmp");
	}
	catch (std::exception e)
	{
		//std::cout << e.what();
	}
}

TileGround::TileGround(Position position)
:Tile(position)
{
}

TileGround::~TileGround()
{
}
