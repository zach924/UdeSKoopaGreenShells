#pragma once
#include <bitset> 

typedef std::bitset<4> MapFilter;

static const MapFilter NO_FILTER("0111");
static const MapFilter BLOCK_ALL ("0000");

static const MapFilter ALLOW_GROUND ("0001");
static const MapFilter ALLOW_MOUNTAIN ("0010");
static const MapFilter ALLOW_WATER("0100");

static const MapFilter ALLOW__GROUND_WATER (ALLOW_GROUND | ALLOW_WATER);
static const MapFilter ALLOW__GROUND_MOUNTAIN(ALLOW_GROUND | ALLOW_MOUNTAIN); 
static const MapFilter ALLOW__GWATER_MOUNTAIN( ALLOW_WATER | ALLOW_MOUNTAIN ); // Maybe super useless 

static const MapFilter BLOCK_ENEMIES("1000");
