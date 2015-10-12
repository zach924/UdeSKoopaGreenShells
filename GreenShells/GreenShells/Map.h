#pragma once
#include <vector>

#include "Position.h"
#include "TileBase.h"
#include "Texture.h"
#include "Ptree_ForwardDeclaration.h"

class Map
{
protected:
	static const int ROWS = 64;
	static const int COLUMNS = 64;

	std::vector<std::vector<TileBase*>> m_tiles;

public:
    Map();
    ~Map();
	static Texture m_texture;

    void GenerateTiles();

	std::vector<TileBase*> GetArea(Position position, int distance);

	TileBase* GetTile(Position);
	virtual bool MoveUnit(int ownerID, Position unitLocation, Position newLocation) = 0;
	virtual bool Attack(int ownerID, Position attackerPosition, Position targetPosition) = 0;
	void NotifyNewturn();
	
	virtual boost::property_tree::ptree Serialize();
};

