#include "Tile.h"
#include "Player.h"
#include "Unit.h"
#include "District.h"
#include "TileWater.h"
#include "TileMountain.h"
#include "TileGround.h"

Texture TileGround::tBase::m_Texture = {};
Texture TileMountain::tBase::m_Texture = {};
Texture TileWater::tBase::m_Texture = {};

//template<class TileGround>
//Tile<TileGround>::Tile(Position position)
//	: m_district(nullptr), m_unit(nullptr), m_owner(nullptr), m_position(position)
//{
//}
//
//template<class TileWater>
//Tile<TileWater>::Tile(Position position)
//	: m_district(nullptr), m_unit(nullptr), m_owner(nullptr), m_position(position)
//{
//}
//
//template<class TileMountain>
//Tile<TileMountain>::Tile(Position position)
//	: m_district(nullptr), m_unit(nullptr), m_owner(nullptr), m_position(position)
//{
//}