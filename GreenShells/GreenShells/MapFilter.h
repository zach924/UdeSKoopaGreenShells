#pragma once
#include <bitset> 

typedef std::bitset<4> Filter;

static const Filter NO_FILTER("0111");
static const Filter BLOCK_ALL ("0000");

static const Filter ALLOW_GROUND ("0001");
static const Filter ALLOW_MOUNTAIN ("0010");
static const Filter ALLOW_WATER("0100");

static const Filter ALLOW__GROUND_WATER (ALLOW_GROUND | ALLOW_WATER);
static const Filter ALLOW__GROUND_MOUNTAIN(ALLOW_GROUND | ALLOW_MOUNTAIN); 
static const Filter ALLOW__GWATER_MOUNTAIN( ALLOW_WATER | ALLOW_MOUNTAIN ); // Maybe super useless 

static const Filter BLOCK_ENEMIES("1000");
