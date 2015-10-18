#pragma once
#include "Tile.h"
class TileWater :
	public Tile<TileWater>
{
private:
	//Serialize
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		//ar & boost::serialization::base_object<TileBase>(*this);
	}
public:
	static const int TILE_TYPE = 2;
	typedef Tile<TileWater> tBase;
	void LoadTexture();
	TileWater(Position position);
	~TileWater();

	virtual bool CanTraverse();
	
	virtual boost::property_tree::ptree Serialize();
    static TileWater* Deserialize(boost::property_tree::ptree tileNode, Position pos = Position{ -1, 0 });
};

