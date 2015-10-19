#pragma once
#include "Tile.h"
class TileWater :
	public Tile<TileWater>
{

public:
	static const int TILE_TYPE = 2;
	typedef Tile<TileWater> tBase;
	void LoadTexture();
	TileWater(Position position);
	~TileWater();

	virtual bool CanTraverse();
	virtual int GetTypeAsInt();
	
	//virtual boost::property_tree::ptree Serialize();
    static TileWater* Deserialize(boost::property_tree::ptree tileNode, Position pos = Position{ -1, 0 });
};

