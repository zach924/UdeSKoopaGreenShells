#include "TileMountain.h"
#include <string>
#include <iostream>

TileMountain::TileMountain(Position position)
:Tile(position)
{
}

void TileMountain::LoadTexture()
{
	try
	{
		TileMountain::tBase::m_Texture.LoadFromFile("..\\Sprite\\Terrain\\64x64\\Mountain.bmp");
	}
	catch (std::exception e)
	{
		std::string msg{ e.what() };
		std::cout << msg << std::endl;
	}
}

TileMountain::~TileMountain()
{
}
