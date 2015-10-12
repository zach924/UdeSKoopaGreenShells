#pragma once
#include "UnitBase.h"

template<class T>
class Unit : public UnitBase
{
public:
	static Texture m_Texture;
	void LoadTexture() {};
	virtual  boost::property_tree::ptree Serialize() = 0;

public:
	Unit(int ownerID, int attackRange, int attackDamage)
		: UnitBase(ownerID, attackRange, attackDamage)
	{

	}

	~Unit()
	{

	}


	virtual Tile* Deserialize(boost::property_tree::ptree tileNode, Position pos = Position(-1, 0))
	{
		return nullptr;
	}

	//Every method must be define in header file because of the static polymorphism
	Texture* GetTexture()
	{
		if (!m_Texture.IsLoaded())
		{
			static_cast<T*>(this)->LoadTexture();
		}
		return &m_Texture;
	}
};

