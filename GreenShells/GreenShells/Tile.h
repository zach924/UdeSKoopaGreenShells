#pragma once
#include "Position.h"
#include "Ptree_ForwardDeclaration.h"

class District;
class Unit;
class Player;

class Tile 
{
protected:
    District* m_district;
    Unit* m_unit;
    int m_owner;

public:

	static const int TILEGROUND_TYPE = 0;
	static const int TILEMOUNTAIN_TYPE = 1;
	static const int TILEWATER_TYPE = 2;

    Position m_position;
    Tile(Position position);
    Tile();
    ~Tile();

	void NotifyNewTurn();
	District* GetDistrict();
	void SetDistrict(District* district);

	Unit* GetUnit();
	void SetUnit(Unit* unit);

	int GetPlayerOwnerID();
	void SetPlayerOwnerID(int id);

	virtual bool CanTraverse()=0;
	
	virtual boost::property_tree::ptree Serialize()=0;
	static Tile* Deserialize(boost::property_tree::ptree tileNode, Position pos = Position{ -1, 0 });

};

