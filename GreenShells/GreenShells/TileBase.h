#pragma once
#include "Texture.h"
#include "Position.h"
#include "Ptree_ForwardDeclaration.h"

class DistrictBase;
class UnitBase;
class Player;

class TileBase
{
protected:
	DistrictBase* m_district;
	UnitBase* m_unit;
    int m_owner;    
    Position m_position;

public:
    TileBase(Position position = Position(-1, -1));
	virtual Texture* GetTexture()=0;
    virtual bool CanTraverse()=0;
    virtual boost::property_tree::ptree Serialize()=0;
    virtual TileBase* Deserialize(boost::property_tree::ptree tileNode, Position pos);
    virtual void NotifyNewTurn();
    virtual DistrictBase* GetDistrict();
    virtual void SetDistrict(DistrictBase* district);
    virtual UnitBase* GetUnit();
    virtual void SetUnit(UnitBase* unit);
    virtual int GetPlayerOwnerId();
    virtual void SetPlayerOwnerId(int id);

	bool IsFree();
};

