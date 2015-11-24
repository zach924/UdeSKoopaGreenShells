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
#include "DistrictFarm.h"

#include "UnitBase.h"

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
        auto tempUnit = firstTile->GetUnit();
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

bool MapLocal::Attack(int ownerID, Position attackerPosition, Position targetPosition)
{
    std::cout << "Received an attack request by " << ownerID << " from " << attackerPosition << " to " << targetPosition << std::endl;

    auto targetTile = GetTile(targetPosition);
    auto attackerTile = GetTile(attackerPosition);
    auto attacker = attackerTile->GetUnit();

    // No unit on the Attacker tile
    if (!attacker) // TODO : might be useless, probably the selection manager that validate that
    {
        return false;
    }

    // Unit doesn't belong to the requester
    if (attacker->GetOwnerID() != ownerID) // TODO : might be useless, probably the selection manager that validate that
    {
        return false;
    }

    // Nothing to attack on target Tile
    if (targetTile->IsFree()) // TODO : might be useless, probably the selection manager that validate that (with GetArea giving only attackable tile)
    {
        return false;
    }

    auto unitTargeted = targetTile->GetUnit();
    auto districtTargeted = targetTile->GetDistrict();

    AttackNotification notification = unitTargeted ? attacker->Attack(unitTargeted) : attacker->Attack(districtTargeted);

    // Attacker is dead?
    if (notification.AttackerIsDead)
    {
        attackerTile->SetUnit(nullptr);
        attacker = nullptr;
    }

    // Target is dead?
    if (notification.TargetIsDead)
    {
        if (unitTargeted)
        {
            targetTile->SetUnit(nullptr);
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
                    auto district = tile->GetDistrict();
                    if (district != nullptr)
                    {
                        district->ChangeOwner(ownerID);
                    }
                    tile->SetPlayerOwnerId(ownerID);
                }

                //Change the owner of the city center
                playerThatLostACity->RemoveCityCenter(districtTargeted->GetPosition());
                districtTargeted->ChangeOwner(ownerID);
                ServerSession::GetInstance().GetWorldState()->GetPlayer(ownerID)->AddCityCenter(districtTargeted->GetPosition(), turnCreated);
            }
            else if (districtTargeted->GetTypeAsInt() != DistrictCityCenter::DISTRICT_TYPE)
            {
                targetTile->SetDistrict(nullptr);
            }
        }

        // Attacker is not dead, the tile is empty and attacker can move after combat (is melee?)
        if (!notification.AttackerIsDead && notification.CanMove && targetTile->IsFree())
        {
            MoveUnit(ownerID, attackerPosition, targetPosition);
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

    std::shared_ptr<UnitBase> unit = nullptr;
    switch (unitType)
    {
    case UnitSwordsmanI::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitSwordsmanI(owner) };
        player->ConsumeWeapon(player->GetWeaponCostForTier(UnitSwordsmanI::UNIT_TIER));
        break;
    case UnitSwordsmanII::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitSwordsmanII(owner) };
        player->ConsumeWeapon(player->GetWeaponCostForTier(UnitSwordsmanII::UNIT_TIER));
        break;
    case UnitSwordsmanIII::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitSwordsmanIII(owner) };
        player->ConsumeWeapon(player->GetWeaponCostForTier(UnitSwordsmanIII::UNIT_TIER));
        break;
    case UnitArcherI::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitArcherI(owner) };
        player->ConsumeWeapon(player->GetWeaponCostForTier(UnitArcherI::UNIT_TIER));
        break;
    case UnitArcherII::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitArcherII(owner) };
        player->ConsumeWeapon(player->GetWeaponCostForTier(UnitArcherII::UNIT_TIER));
        break;
    case UnitArcherIII::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitArcherIII(owner) };
        player->ConsumeWeapon(player->GetWeaponCostForTier(UnitArcherIII::UNIT_TIER));
        break;
    case UnitSettler::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitSettler(owner) };
        player->ConsumeWeapon(player->GetWeaponCostForTier(UnitSettler::UNIT_TIER));
        break;
    case UnitAxemanI::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitAxemanI(owner) };
        player->ConsumeWeapon(player->GetWeaponCostForTier(UnitAxemanI::UNIT_TIER));
        break;
    case UnitAxemanII::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitAxemanII(owner) };
        player->ConsumeWeapon(player->GetWeaponCostForTier(UnitAxemanII::UNIT_TIER));
        break;
    case UnitCannon::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitCannon(owner) };
        player->ConsumeWeapon(player->GetWeaponCostForTier(UnitCannon::UNIT_TIER));
        break;
    case UnitShield::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitShield(owner) };
        player->ConsumeWeapon(player->GetWeaponCostForTier(UnitShield::UNIT_TIER));
        break;
    case UnitMaceI::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitMaceI(owner) };
        player->ConsumeWeapon(player->GetWeaponCostForTier(UnitMaceI::UNIT_TIER));
        break;
    case UnitMaceII::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitMaceII(owner) };
        player->ConsumeWeapon(player->GetWeaponCostForTier(UnitMaceII::UNIT_TIER));
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

    std::shared_ptr<DistrictBase> district;
    switch (districtType)
    {
    case DistrictCityCenter::DISTRICT_TYPE:
        district = std::shared_ptr<DistrictBase>{ new DistrictCityCenter(owner) };
        ServerSession::GetInstance().GetWorldState()->GetPlayer(owner)->AddCityCenter(pos, ServerSession::GetInstance().GetWorldState()->GetCurrentTurn());
        break;
    case DistrictFarm::DISTRICT_TYPE:
        district = std::shared_ptr<DistrictBase>{ new DistrictFarm(owner) };
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