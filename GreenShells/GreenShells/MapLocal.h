#pragma once
#include "Map.h"

class MapLocal : public Map
{
public:
    MapLocal();
    ~MapLocal();
    Map* Clone();

    std::vector<Position> DiscoverArea(Position pos, int range, int playerId);

    virtual std::vector<Position> MoveUnit(int ownerID, Position unitLocation, Position newLocation, int actionCost);
    virtual std::vector<Position> Attack(int ownerID, Position attackerPosition, Position targetPosition, int actionCost);
    virtual bool CreateUnit(int unitType, Position pos, int owner);
    virtual bool CreateDistrict(int districtType, Position pos, int owner);

    void ShareVision(int playerOne, int playerTwo);

    static MapLocal* Deserialize(boost::property_tree::ptree mapNode);
};