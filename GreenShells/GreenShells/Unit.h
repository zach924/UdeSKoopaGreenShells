#pragma once
#include "UnitBase.h"
#include "Texture.h"
#include <boost\property_tree\ptree.hpp>

template<class T>
class Unit : public UnitBase
{
public:
	static Texture m_Texture;
	void LoadTexture() {};
	virtual  boost::property_tree::ptree Serialize() = 0;

public:
	Unit(int ownerID, int health, int attackRange, int attackDamage)
		: UnitBase(ownerID, health, attackRange, attackDamage)
	{

	}

	~Unit()
	{

	}


	virtual Unit* Deserialize(boost::property_tree::ptree tileNode, Position pos = Position(-1, 0))
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

