#pragma once
#include "Tile.h"
class TileGround :
    public Tile<TileGround>
{
public:
    static const int TILE_TYPE = 0;
    typedef Tile<TileGround> tBase;
    void LoadTexture();

    TileGround(Position position);
    ~TileGround();
    virtual TileBase* Clone();

	virtual bool CanTraverse(MapFilter filter);	
    virtual int GetTypeAsInt();
    static TileGround* Deserialize(boost::property_tree::ptree tileNode, Position pos);
};
