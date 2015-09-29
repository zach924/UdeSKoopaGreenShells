#pragma once
#include "Position.h"
#include "Texture.h"
#include "TileBase.h"

class District;
class Unit;
class Player;

template<class T>
class Tile : public TileBase
{
	District* m_district;
	Unit* m_unit;
	Player* m_owner;

public:
	static Texture m_Texture;

	void LoadTexture() {};

	Texture GetTexture()
	{
		if (!m_Texture.IsLoaded())
		{
			static_cast<T*>(this)->LoadTexture();
		}
		return m_Texture;
	}

	Position m_position;
	Tile(Position position = Position(-1,-1))
		: m_district(nullptr), m_unit(nullptr), m_owner(nullptr), m_position(position)
	{
	}
		
	~Tile()
	{
	}
};

