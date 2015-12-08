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

    std::map<Position, int> GetArea(Position position, int distance, MapFilter filter, bool stopIfCannotGoFurther);


    TileBase* GetTile(Position);
    virtual std::set<Position> MoveUnit(int ownerID, Position unitLocation, Position newLocation, int actionCost) = 0;
    virtual std::set<Position> Attack(int ownerID, Position attackerPosition, Position targetPosition, int actionCost) = 0;
    virtual std::set<Position> CreateUnit(int unitType, Position pos, int owner, bool upgrade) = 0;
    virtual std::set<Position> CreateDistrict(int districtType, Position pos, int owner, bool upgrade = false) = 0;
    virtual bool SellDistrict(Position pos, int owner) = 0;
    virtual bool SellUnit(Position pos, int owner) = 0;
    virtual std::set<Position> UpgradeUnit(Position pos, int owner) = 0;
    virtual std::set<Position> UpgradeDistrict(Position pos, int owner) = 0;
    virtual bool HealUnit(Position pos, int owner) = 0;
    virtual bool RepairDistrict(Position pos, int owner) = 0;
    virtual void RemoveFogOfWarForPlayer(int playerID) = 0;
    void NotifyNewTurn(int turn);
    virtual boost::property_tree::ptree Serialize();
    void DeserializeTile(boost::property_tree::ptree tileXml);

private:
    void GetAreaIntern(int distance, std::set<Position>& toVisit, std::map<Position, int>& alreadyVisited, MapFilter filter, const int maxDistance);
    void GetAreaIntern(int distance, Position position, std::map<Position, int>& areaOut, MapFilter filter);

};
