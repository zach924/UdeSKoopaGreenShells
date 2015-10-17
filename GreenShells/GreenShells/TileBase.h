#pragma once
#include <boost/serialization/access.hpp>

#include "Texture.h"
#include "Position.h"
#include "Ptree_ForwardDeclaration.h"

class District;
class Unit;
class Player;

class TileBase
{
private:
	//Serialize
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		//ar & m_district;
		//ar & m_unit;
		//ar & m_owner;
		ar & m_position;
	}
protected:
    District* m_district;
    Unit* m_unit;
    int m_owner;    
    Position m_position;

public:
	TileBase();
    TileBase(Position position = Position(-1, -1));
	virtual Texture* GetTexture()=0;
    virtual bool CanTraverse()=0;
    virtual boost::property_tree::ptree Serialize()=0;
    virtual TileBase* Deserialize(boost::property_tree::ptree tileNode, Position pos);
    virtual void NotifyNewTurn();
    virtual District* GetDistrict();
    virtual void SetDistrict(District* district);
    virtual Unit* GetUnit();
    virtual void SetUnit(Unit* unit);
    virtual int GetPlayerOwnerId();
    virtual void SetPlayerOwnerId(int id);
};

