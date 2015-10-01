#include "TileWater.h"
#include "TileMountain.h"
#include "TileGround.h"

//Allows static polymorphism
Texture TileGround::tBase::m_Texture = {};
Texture TileMountain::tBase::m_Texture = {};
Texture TileWater::tBase::m_Texture = {};