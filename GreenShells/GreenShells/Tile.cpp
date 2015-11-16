#include "TileWater.h"
#include "TileMountain.h"
#include "TileGround.h"

//Allows static polymorphism
Texture TileGround::tBase::m_Texture = {};
Texture TileMountain::tBase::m_Texture = {};
Texture TileWater::tBase::m_Texture = {};

Color TileGround::tBase::m_MinimapColor = { 0,102,0 };
Color TileWater::tBase::m_MinimapColor = { 0,0,255 };
Color TileMountain::tBase::m_MinimapColor = { 100,50,15 };

bool TileGround::tBase::m_forceLoading = false;
bool TileWater::tBase::m_forceLoading = false;
bool TileMountain::tBase::m_forceLoading = false;
