#pragma once
#include "Tile.h"
class TileMountain :
    public Tile<TileMountain>
{
public:
    static const int TILE_TYPE = 1;
    typedef Tile<TileMountain> tBase;
    void LoadTexture();

    TileMountain(Position position);
    ~TileMountain();
    virtual TileBase* Clone();
    virtual bool CanTraverse(Filter filter);
    virtual int GetTypeAsInt();
    static TileMountain* Deserialize(boost::property_tree::ptree tileNode, Position pos = Position{ -1, 0 });
};
