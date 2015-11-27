#include <boost\property_tree\ptree.hpp>
#include <iostream>
#include <exception>

#include "MapLocal.h"
#include "GameSession.h"
#include "ServerSession.h"
#include "PlayerLocal.h"

#include "TileGround.h"
#include "TileMountain.h"
#include "TileWater.h"

#include "DistrictCityCenter.h"

#include "DistrictHunter.h"
#include "DistrictFarm.h"
#include "DistrictWindMill.h"
#include "DistrictWarehouse.h"

#include "DistrictBlacksmith.h"
#include "DistrictStable.h"
#include "DistrictFort.h"
#include "DistrictFortress.h"

#include "DistrictMonastery.h"
#include "DistrictCathedral.h"
#include "DistrictSchool.h"
#include "DistrictUniversity.h"

#include "DistrictWatchTower.h"
#include "DistrictInn.h"
#include "DistrictTavern.h"
#include "DistrictMilitaryTent.h"

#include "UnitSettler.h"

#include "UnitArcherI.h"
#include "UnitArcherII.h"
#include "UnitArcherIII.h"

#include "UnitSwordsmanI.h"
#include "UnitSwordsmanII.h"
#include "UnitSwordsmanIII.h"

#include "UnitAxemanI.h"
#include "UnitAxemanII.h"

#include "UnitMaceI.h"
#include "UnitMaceII.h"

#include "UnitCannon.h"
#include "UnitShield.h"
#include "Position.h"


int MapLocal::GetDistance(Position pos1, Position pos2)
{
    return std::max(std::abs(pos1.Column - pos2.Column), std::abs(pos1.Row - pos2.Row));
}
#include "GameSession.h"

MapLocal::MapLocal()
    :Map()
{
}

MapLocal::~MapLocal()
{
}

Map* MapLocal::Clone()
{
    MapLocal* map = new MapLocal{};

    for (auto spawn : m_spawnPositions)
    {
        map->m_spawnPositions.push_back(spawn);
    }

    for (int i = 0; i < ROWS; i++)
    {
        map->m_tiles.push_back(std::vector<TileBase*>(COLUMNS));
    }
    for (int row = 0; row < ROWS; ++row)
    {
        for (int column = 0; column < COLUMNS; ++column)
        {
            map->m_tiles[row][column] = m_tiles[row][column]->Clone();
        }
    }
    return map;
}

void MapLocal::DiscoverArea(Position pos, int range, int playerId)
{
    auto positionToDiscover = GetArea(pos, range, NO_FILTER);

    for (Position pos : positionToDiscover)
    {
        GetTile(pos)->PlayerDiscover(playerId);
    }
}

bool MapLocal::MoveUnit(int ownerID, Position unitLocation, Position newLocation)
{
    std::cout << "Received a move request by " << ownerID << " from " << unitLocation << " to " << newLocation << std::endl;
    auto firstTile = GetTile(unitLocation);

    //No unit to select
    if (!firstTile->GetUnit())
    {
        return false;
    }

    //There is a unit be he does not belong to the requester
    if (firstTile->GetUnit()->GetOwnerID() != ownerID)
    {
        return false;
    }

    auto secondTile = GetTile(newLocation);

    std::shared_ptr<Player> currentPlayer{ GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID()) };

    if (secondTile->GetTypeAsInt() == TileWater::TILE_TYPE && !currentPlayer->GetUtilitySkillTree().Embark)
    {
        return false;
    }

    if (secondTile->GetTypeAsInt() == TileMountain::TILE_TYPE && !currentPlayer->GetUtilitySkillTree().MountainWalking)
    {
        return false;
    }

    //New Location is emtpy or there is a district and it belongs to the player. Move him
    if ((!secondTile->GetUnit() && !secondTile->GetDistrict()) || (!secondTile->GetUnit() && secondTile->GetDistrict() && secondTile->GetDistrict()->GetOwnerID() == ownerID))
    {
        UnitBase* tempUnit = firstTile->GetUnit();
        firstTile->SetUnit(nullptr);
        tempUnit->SetPosition(newLocation);
        tempUnit->UseActionPoints(GetDistance(unitLocation, newLocation));
        secondTile->SetUnit(tempUnit);

        DiscoverArea(newLocation, tempUnit->GetViewRange(), ownerID);
        return true;
    }

    //Other cases are all refused
    return false;
}

bool MapLocal::Attack(int attackerID, Position attackerPosition, Position targetPosition)
{
    std::cout << "Received an attack request by " << attackerID << " from " << attackerPosition << " to " << targetPosition << std::endl;

    auto targetTile = GetTile(targetPosition);
    auto attackerTile = GetTile(attackerPosition);
    auto attacker = attackerTile->GetUnit();

    // No unit on the Attacker tile
    if (!attacker) // TODO : might be useless, probably the selection manager that validate that
    {
        return false;
    }

    // Unit doesn't belong to the requester
    if (attacker->GetOwnerID() != attackerID) // TODO : might be useless, probably the selection manager that validate that
    {
        return false;
    }

    // Nothing to attack on target Tile
    if (targetTile->IsFree()) // TODO : might be useless, probably the selection manager that validate that (with GetArea giving only attackable tile)
    {
        return false;
    }

    UnitBase* unitTargeted = targetTile->GetUnit();
    DistrictBase* districtTargeted = targetTile->GetDistrict();

    AttackNotification notification = unitTargeted ? attacker->Attack(unitTargeted) : attacker->Attack(districtTargeted);

    // Attacker is dead?
    if (notification.AttackerIsDead)
    {
        attackerTile->SetUnit(nullptr);
        delete attacker;
        attacker = nullptr;
    }

    // Target is dead?
    if (notification.TargetIsDead)
    {
        if (unitTargeted)
        {
            targetTile->SetUnit(nullptr);
            delete unitTargeted;
        }
        else
        {
            if (attacker && notification.CanMove && districtTargeted->GetTypeAsInt() == DistrictCityCenter::DISTRICT_TYPE)
            {
                int currentTurn = ServerSession::GetInstance().GetWorldState()->GetCurrentTurn();
                Player* playerThatLostACity = ServerSession::GetInstance().GetWorldState()->GetPlayer(districtTargeted->GetOwnerID());
                auto allPlayerCityCenters = playerThatLostACity->GetCityCenterLocations();
                int turnCreated = allPlayerCityCenters[districtTargeted->GetPosition()];

                //Flip the borders and district belonging to the city center
                auto ownedTilesPos = playerThatLostACity->GetCityCenterTilesOwned(currentTurn, this, districtTargeted->GetPosition());
                for (auto tilePos : ownedTilesPos)
                {
                    TileBase* tile = GetTile(tilePos);
                    DistrictBase* district = tile->GetDistrict();
                    if (district != nullptr)
                    {
                        district->ChangeOwner(attackerID);
                    }
                    tile->SetPlayerOwnerId(attackerID);
                }

                //Change the owner of the city center
                playerThatLostACity->RemoveCityCenter(districtTargeted->GetPosition());
                districtTargeted->ChangeOwner(attackerID);
                ServerSession::GetInstance().GetWorldState()->GetPlayer(attackerID)->AddCityCenter(districtTargeted->GetPosition(), turnCreated);
            }
            else if (districtTargeted->GetTypeAsInt() == DistrictUniversity::DISTRICT_TYPE)
            {
                ServerSession::GetInstance().GetWorldState()->GetPlayer(districtTargeted->GetOwnerID())->RemoveScienceMultiplier(DistrictUniversity::SCIENCE_BONUS);
            }
            else if (districtTargeted->GetTypeAsInt() == DistrictMilitaryTent::DISTRICT_TYPE)
            {
                ServerSession::GetInstance().GetWorldState()->GetPlayer(districtTargeted->GetOwnerID())->RemoveWeaponMultiplier(DistrictMilitaryTent::WEAPON_BONUS);
            }
            else if (districtTargeted->GetTypeAsInt() == DistrictWarehouse::DISTRICT_TYPE)
            {
                ServerSession::GetInstance().GetWorldState()->GetPlayer(districtTargeted->GetOwnerID())->RemoveFoodMultiplier(DistrictUniversity::SCIENCE_BONUS);
            }
            else if (districtTargeted->GetTypeAsInt() != DistrictCityCenter::DISTRICT_TYPE)
            {
                targetTile->SetDistrict(nullptr);
                delete districtTargeted;
            }
        }

        // Attacker is not dead, the tile is empty and attacker can move after combat (is melee?)
        if (!notification.AttackerIsDead && notification.CanMove && targetTile->IsFree())
        {
            MoveUnit(attackerID, attackerPosition, targetPosition);
        }
    }

    return true;
}

bool MapLocal::CreateUnit(int unitType, Position pos, int owner)
{
    if (GetTile(pos)->GetUnit() != nullptr)
    {
        return false;
    }
    Player* player = ServerSession::GetInstance().GetWorldState()->GetPlayer(owner);

    UnitBase* unit = nullptr;
    switch (unitType)
    {
    case UnitSwordsmanI::UNIT_TYPE:
        unit = new UnitSwordsmanI(owner);
        player->ConsumeWeapon(unit->GetWeaponCost());
        break;
    case UnitSwordsmanII::UNIT_TYPE:
        unit = new UnitSwordsmanII(owner);
        player->ConsumeWeapon(unit->GetWeaponCost());
        break;
    case UnitSwordsmanIII::UNIT_TYPE:
        unit = new UnitSwordsmanIII(owner);
        player->ConsumeWeapon(unit->GetWeaponCost());
        break;
    case UnitArcherI::UNIT_TYPE:
        unit = new UnitArcherI(owner);
        player->ConsumeWeapon(unit->GetWeaponCost());
        break;
    case UnitArcherII::UNIT_TYPE:
        unit = new UnitArcherII(owner);
        player->ConsumeWeapon(unit->GetWeaponCost());
        break;
    case UnitArcherIII::UNIT_TYPE:
        unit = new UnitArcherIII(owner);
        player->ConsumeWeapon(unit->GetWeaponCost());
        break;
    case UnitSettler::UNIT_TYPE:
        //Only the settler consumes food instead of weapons
        unit = new UnitSettler(owner);
        player->ConsumeFood(unit->GetFoodCost());
        break;
    case UnitAxemanI::UNIT_TYPE:
        unit = new UnitAxemanI(owner);
        player->ConsumeWeapon(unit->GetWeaponCost());
        break;
    case UnitAxemanII::UNIT_TYPE:
        unit = new UnitAxemanII(owner);
        player->ConsumeWeapon(unit->GetWeaponCost());
        break;
    case UnitCannon::UNIT_TYPE:
        unit = new UnitCannon(owner);
        player->ConsumeWeapon(unit->GetWeaponCost());
        break;
    case UnitShield::UNIT_TYPE:
        unit = new UnitShield(owner);
        player->ConsumeWeapon(unit->GetWeaponCost());
        break;
    case UnitMaceI::UNIT_TYPE:
        unit = new UnitMaceI(owner);
        player->ConsumeWeapon(unit->GetWeaponCost());
        break;
    case UnitMaceII::UNIT_TYPE:
        unit = new UnitMaceII(owner);
        player->ConsumeWeapon(unit->GetWeaponCost());
        break;
    default:
        return false;
        break;
    }

    if (unit)
    {
        GetTile(pos)->SetUnit(unit);

        DiscoverArea(pos, unit->GetViewRange(), owner);

    }
    return true;
}

bool MapLocal::CreateDistrict(int districtType, Position pos, int owner)
{
    if (GetTile(pos)->GetDistrict() != nullptr)
    {
        return false;
    }

    DistrictBase* district = nullptr;
    switch (districtType)
    {
    case DistrictCityCenter::DISTRICT_TYPE:
        district = new DistrictCityCenter(owner);
        ServerSession::GetInstance().GetWorldState()->GetPlayer(owner)->AddCityCenter(pos, ServerSession::GetInstance().GetWorldState()->GetCurrentTurn());
        break;
    case DistrictHunter::DISTRICT_TYPE:
        district = new DistrictHunter(owner);
        break;
    case DistrictFarm::DISTRICT_TYPE:
        district = new DistrictFarm(owner);
        break;
    case DistrictWindMill::DISTRICT_TYPE:
        district = new DistrictWindMill(owner);
        break;
    case DistrictWarehouse::DISTRICT_TYPE:
        district = new DistrictWarehouse(owner);
        ServerSession::GetInstance().GetWorldState()->GetPlayer(owner)->AddFoodMultiplier(DistrictWarehouse::FOOD_BONUS);
        break;
    case DistrictBlacksmith::DISTRICT_TYPE:
        district = new DistrictBlacksmith(owner);
        break;
    case DistrictStable::DISTRICT_TYPE:
        district = new DistrictStable(owner);
        break;
    case DistrictFort::DISTRICT_TYPE:
        district = new DistrictFort(owner);
        break;
    case DistrictMonastery::DISTRICT_TYPE:
        district = new DistrictMonastery(owner);
        break;
    case DistrictCathedral::DISTRICT_TYPE:
        district = new DistrictCathedral(owner);
        break;
    case DistrictSchool::DISTRICT_TYPE:
        district = new DistrictSchool(owner);
        break;
    case DistrictUniversity::DISTRICT_TYPE:
        district = new DistrictUniversity(owner);
        ServerSession::GetInstance().GetWorldState()->GetPlayer(owner)->AddScienceMultiplier(DistrictUniversity::SCIENCE_BONUS);
        break;
    case DistrictWatchTower::DISTRICT_TYPE:
        district = new DistrictWatchTower(owner);
        break;
    case DistrictInn::DISTRICT_TYPE:
        district = new DistrictInn(owner);
        break;
    case DistrictTavern::DISTRICT_TYPE:
        district = new DistrictTavern(owner);
        break;
    case DistrictMilitaryTent::DISTRICT_TYPE:
        district = new DistrictMilitaryTent(owner);
        ServerSession::GetInstance().GetWorldState()->GetPlayer(owner)->AddWeaponMultiplier(DistrictMilitaryTent::WEAPON_BONUS);
        break;
    default:
        return false;
        break;
    }

    if (district)
    {
        GetTile(pos)->SetDistrict(district);

        DiscoverArea(pos, district->GetViewRange(), owner);
    }
    return true;
}

MapLocal* MapLocal::Deserialize(boost::property_tree::ptree mapNode)
{
    MapLocal* map = new MapLocal();
    int row = 0;
    for each (auto rowNode in mapNode)
    {
        if (rowNode.first == "SPS")
        {
            for each(auto spawnNode in rowNode.second)
            {
                if (spawnNode.first == "SP")
                {
                    map->m_spawnPositions.emplace_back(spawnNode.second.get<int>("<xmlattr>.X"), spawnNode.second.get<int>("<xmlattr>.Y"));
                }
            }
        }
        else
        {
            int column = 0;
            for each(auto tileNode in rowNode.second)
            {
                if (tileNode.first == "T")
                {
                    Position pos{ column, row };

                    switch (tileNode.second.get<int>("<xmlattr>.TT"))
                    {
                    case 0:
                        map->m_tiles[pos.Row][pos.Column] = TileGround::Deserialize(tileNode.second, pos);
                        break;
                    case 1:
                        map->m_tiles[pos.Row][pos.Column] = TileMountain::Deserialize(tileNode.second, pos);
                        break;
                    case 2:
                        map->m_tiles[pos.Row][pos.Column] = TileWater::Deserialize(tileNode.second, pos);
                        break;

                    case -1:
                    default:
                        std::string msg = ("Error while loading the map, a tile is of type unknown.");
                        throw new std::exception(msg.c_str());
                        break;
                    }
                }
                column++;
            }
            row++;
        }
    }

    return map;
}