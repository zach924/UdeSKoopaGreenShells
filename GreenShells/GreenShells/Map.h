#pragma once
#include <vector>
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>

#include "Position.h"
#include "TileBase.h"
#include "Texture.h"
#include "Ptree_ForwardDeclaration.h"

class Map
{
private:
	//Serialize
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & temp;
		ar & m_tiles;
	}
protected:
	static const int ROWS = 64;
	static const int COLUMNS = 64;


	std::vector<std::vector<TileBase*>> m_tiles;

public:
	TileBase* temp;
    Map();
	Map(const Map& source);
    ~Map();
	static Texture m_texture;

    void GenerateTiles();

	std::vector<TileBase*> GetArea(Position position, int distance);

	TileBase* GetTile(Position);
	virtual bool MoveUnit(int ownerID, Position unitLocation, Position newLocation);
	void NotifyNewturn();
	
	virtual boost::property_tree::ptree Serialize();
};

