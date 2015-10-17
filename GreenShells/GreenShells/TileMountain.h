#pragma once
#include "Tile.h"
class TileMountain :
	public Tile<TileMountain>
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
	static const int TILE_TYPE = 1;
	typedef Tile<TileMountain> tBase;
	void LoadTexture();

	TileMountain();
	TileMountain(Position position);
	~TileMountain();

	virtual bool CanTraverse();	
	virtual boost::property_tree::ptree Serialize();
	static TileMountain* Deserialize(boost::property_tree::ptree tileNode, Position pos = Position{ -1, 0 });
};

