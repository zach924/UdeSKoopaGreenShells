#pragma once
#include "Tile.h"
class TileGround : 
	public Tile<TileGround>
{
public:
	static const int TILE_TYPE = 0;
	typedef Tile<TileGround> tBase;
	void LoadTexture();
	TileGround(Position position);
	~TileGround();

	virtual bool CanTraverse();	
	virtual int GetTypeAsInt();
	//virtual boost::property_tree::ptree Serialize();
	static TileGround* Deserialize(boost::property_tree::ptree tileNode, Position pos);
};

