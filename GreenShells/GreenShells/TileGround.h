#pragma once
#include "Tile.h"
class TileGround : 
	public Tile<TileGround>
{
private:
	//Serialize
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<TileBase>(*this);
	}
public:
	static const int TILE_TYPE = 0;
	typedef Tile<TileGround> tBase;
	void LoadTexture();

	TileGround();
	TileGround(Position position);
	~TileGround();

	virtual bool CanTraverse();	
	virtual boost::property_tree::ptree Serialize();
	static TileGround* Deserialize(boost::property_tree::ptree tileNode, Position pos = Position{ -1, 0 });
};

