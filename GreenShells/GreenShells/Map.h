#pragma once
#include <vector>
#include <map>
#include <set>

#include "Position.h"
#include "TileBase.h"
#include "Texture.h"
#include "Ptree_ForwardDeclaration.h"
#include "MapFilter.h"



class Map
{
protected:

    std::vector<std::vector<TileBase*>> m_tiles;
    std::vector<Position> m_spawnPositions;

public:
    static const int ROWS = 64;
    static const int COLUMNS = 64;

    Map();
    ~Map();

    virtual Map* Clone() = 0;
    static Texture m_texture;

    void GenerateTiles();
    std::vector<Position> GetSpawnPositions();

    std::map<Position, int> GetArea(Position position, int distance, MapFilter filter);


    TileBase* GetTile(Position);
    virtual bool MoveUnit(int ownerID, Position unitLocation, Position newLocation, int actionCost) = 0;
    virtual bool Attack(int ownerID, Position attackerPosition, Position targetPosition, int actionCost) = 0;
    virtual bool CreateUnit(int unitType, Position pos, int owner) = 0;
    virtual bool CreateDistrict(int districtType, Position pos, int owner) = 0;
    void NotifyNewTurn(int turn);

    virtual boost::property_tree::ptree Serialize();

private:
    void GetAreaIntern(int distance, std::set<Position>& toVisit, std::map<Position, int>& alreadyVisited, MapFilter filter, const int maxDistance);

};
