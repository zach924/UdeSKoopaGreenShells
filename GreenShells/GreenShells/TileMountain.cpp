#include "TileMountain.h"

Texture TileMountain::m_texture = {};
TileMountain::TileMountain(Position position)
:Tile(position)
{
	try
	{
		m_texture.LoadFromFile("..\\Sprite\\Terrain\\64x64\\Mountain.bmp");
	}
	catch (std::exception e)
	{
		//std::cout << e.what();
	}
}


TileMountain::~TileMountain()
{
}
