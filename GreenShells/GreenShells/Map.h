#pragma once
#include <vector>

#include "Position.h"
#include "TileBase.h"
#include "Texture.h"
#include "Ptree_ForwardDeclaration.h"

class Map
{
protected:

	std::vector<std::vector<TileBase*>> m_tiles;
	std::vector<Position> m_spawnPositions;

public:
    static const int ROWS = 64;
    static const int COLUMNS = 64;

    Map();
    ~Map();

	virtual Map* Clone()=0;
	static Texture m_texture;

    void GenerateTiles();
	std::vector<Position> GetSpawnPositions();

	std::vector<Position> GetArea(Position position, int distance);

	TileBase* GetTile(Position);
	virtual bool MoveUnit(int ownerID, Position unitLocation, Position newLocation);
	virtual bool Attack(int ownerID, Position attackerPosition, Position targetPosition);
	void NotifyNewturn();
	
	virtual boost::property_tree::ptree Serialize();
};

