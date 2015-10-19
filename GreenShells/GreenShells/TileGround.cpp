#include "TileGround.h"
#include <iostream>
#include <string>
#include "District.h"
#include "Unit.h"
#include <boost\property_tree\ptree.hpp>

void TileGround::LoadTexture()
{
	try
	{
		TileGround::tBase::m_Texture.LoadFromFile("..\\Sprite\\Terrain\\64x64\\Grass.bmp");
	}
	catch (std::exception e)
	{
		std::string msg{ e.what() };
		std::cout << msg << std::endl;
	}
}

TileGround::TileGround(Position position)
:Tile(position)
{
}

TileGround::~TileGround()
{
}

TileGround* TileGround::Deserialize(boost::property_tree::ptree tileNode, Position pos)
{
    TileGround* tile = new TileGround{ pos };

	tile->m_position = pos;
    tile->m_owner = tileNode.get<int>("<xmlattr>.O");

    for each(auto child in tileNode)
    {
        if (child.first == "U")
        {
            // TODO : When we will have unit to log. Will need to check how exactly, i think a switch case depend on unit type
        }
        else if (child.first == "D")
        {
            // TODO : When district will be done. Will need to check how exactly, i think a switch case depend on district type
        }
    }

    return tile;
}

bool TileGround::CanTraverse()
{
	return true;
}

int TileGround::GetTypeAsInt()
{
	return TILE_TYPE;
}
