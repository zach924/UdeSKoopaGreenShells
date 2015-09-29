#include "TileMountain.h"


TileMountain::TileMountain(Position position)
:Tile(position)
{
}

void TileMountain::LoadTexture()
{
	try
	{
		TileMountain::tBase::m_Texture.LoadFromFile("..\\Sprite\\Terrain\\64x64\\Grass.bmp");
	}
	catch (std::exception e)
	{
		//std::cout << e.what();
	}
}

TileMountain::~TileMountain()
{
}
