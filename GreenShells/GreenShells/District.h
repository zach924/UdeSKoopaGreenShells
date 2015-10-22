#pragma once
#include "DistrictBase.h"
#include "Texture.h"
#include <boost\property_tree\ptree.hpp>

template<class T>
class District : public DistrictBase
{
public:
	static Texture m_Texture;
	void LoadTexture() {};

	virtual int GetTypeAsInt() = 0;

public:
	District(int ownerID, int health, int attackDamage)
		: DistrictBase(ownerID, health, attackDamage)
	{

	}

	~District()
	{

	}


	virtual District* Deserialize(boost::property_tree::ptree tileNode, Position pos = Position(-1, 0))
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

