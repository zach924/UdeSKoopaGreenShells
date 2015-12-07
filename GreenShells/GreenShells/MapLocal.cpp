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

#include "DistrictFishery.h"
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

#include "UnitBase.h"

#include "UnitSettler.h"
#include "UnitBuilder.h"

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

std::vector<Position> MapLocal::DiscoverArea(Position pos, int range, int playerId)
{
    std::vector<Position> discovered;
    auto positionToDiscover = GetArea(pos, range, NO_FILTER, true);

    for (const std::pair<Position, int>& pos : positionToDiscover)
    {
        auto tile = GetTile(pos.first);
        if (!tile->IsDiscovered(playerId))
        {
            tile->PlayerDiscover(playerId);
            discovered.push_back(pos.first);
        }
    }
    return discovered;
}

void MapLocal::RemoveFogOfWarForPlayer(int playerID)
{
    for (std::vector<TileBase*>& aRow : m_tiles)
    {
        for (TileBase* tile : aRow)
        {
            tile->PlayerDiscover(playerID);
        }
    }
}

std::vector<Position> MapLocal::MoveUnit(int ownerID, Position unitLocation, Position newLocation, int actionCost)
{
    std::cout << "Received a move request by " << ownerID << " from " << unitLocation << " to " << newLocation << std::endl;
    auto firstTile = GetTile(unitLocation);

    //No unit to select
    if (!firstTile->GetUnit())
    {
        return std::vector<Position>{};
    }

    //There is a unit be he does not belong to the requester
    if (firstTile->GetUnit()->GetOwnerID() != ownerID)
    {
        return std::vector<Position>{};
    }

    auto secondTile = GetTile(newLocation);

    std::shared_ptr<Player> currentPlayer{ GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID()) };

    if (secondTile->GetTypeAsInt() == TileWater::TILE_TYPE && !currentPlayer->GetUtilitySkillTree().Embark)
    {
        return std::vector<Position>{};
    }

    if (secondTile->GetTypeAsInt() == TileMountain::TILE_TYPE && !currentPlayer->GetUtilitySkillTree().MountainWalking)
    {
        return std::vector<Position>{};
    }

    //New Location is emtpy or there is a district and it belongs to the player. Move him
    if ((!secondTile->GetUnit() && !secondTile->GetDistrict()) || (!secondTile->GetUnit() && secondTile->GetDistrict() && secondTile->GetDistrict()->GetOwnerID() == ownerID))
    {
        auto tempUnit = firstTile->GetUnit();
        firstTile->SetUnit(nullptr);
        tempUnit->SetPosition(newLocation);
        tempUnit->UseActionPoints(actionCost);
        secondTile->SetUnit(tempUnit);

        auto player = GameSession::GetInstance().GetCurrentPlayerCopy();
        auto utilitySK = player->GetUtilitySkillTree();
        int viewModifier = utilitySK.VisionUpgrade ? 1 : 0;

        return DiscoverArea(newLocation, tempUnit->GetViewRange() + viewModifier, ownerID);
    }

    //Other cases are all refused
    return std::vector<Position>{};
}

std::vector<Position> MapLocal::Attack(int attackerID, Position attackerPosition, Position targetPosition, int actionCost)
{
    std::cout << "Received an attack request by " << attackerID << " from " << attackerPosition << " to " << targetPosition << std::endl;

    auto targetTile = GetTile(targetPosition);
    auto attackerTile = GetTile(attackerPosition);
    auto attacker = attackerTile->GetUnit();

    // No unit on the Attacker tile
    if (!attacker)
    {
        return std::vector<Position>{};
    }

    // Unit doesn't belong to the requester
    if (attacker->GetOwnerID() != attackerID)
    {
        return std::vector<Position>{};
    }

    // Nothing to attack on target Tile
    if (targetTile->IsFree())
    {
        return std::vector<Position>{};
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
                auto playerThatLostACity = ServerSession::GetInstance().GetWorldState()->GetPlayer(districtTargeted->GetOwnerID());
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
                        if (district->GetTypeAsInt() == DistrictUniversity::DISTRICT_TYPE)
                        {
                            ServerSession::GetInstance().GetWorldState()->GetPlayer(district->GetOwnerID())->RemoveScienceMultiplier(DistrictUniversity::SCIENCE_BONUS);
                            ServerSession::GetInstance().GetWorldState()->GetPlayer(attackerID)->AddScienceMultiplier(DistrictUniversity::SCIENCE_BONUS);
                        }
                        else if (district->GetTypeAsInt() == DistrictMilitaryTent::DISTRICT_TYPE)
                        {
                            ServerSession::GetInstance().GetWorldState()->GetPlayer(district->GetOwnerID())->RemoveWeaponMultiplier(DistrictMilitaryTent::WEAPON_BONUS);
                            ServerSession::GetInstance().GetWorldState()->GetPlayer(attackerID)->AddWeaponMultiplier(DistrictMilitaryTent::WEAPON_BONUS);
                        }
                        else if (district->GetTypeAsInt() == DistrictWarehouse::DISTRICT_TYPE)
                        {
                            ServerSession::GetInstance().GetWorldState()->GetPlayer(district->GetOwnerID())->RemoveFoodMultiplier(DistrictUniversity::SCIENCE_BONUS);
                            ServerSession::GetInstance().GetWorldState()->GetPlayer(attackerID)->AddFoodMultiplier(DistrictUniversity::SCIENCE_BONUS);
                        }
                        district->ChangeOwner(attackerID);
                    }
                    tile->SetPlayerOwnerId(attackerID);
                }

                //Change the owner of the city center
                playerThatLostACity->RemoveCityCenter(districtTargeted->GetPosition());
                districtTargeted->ChangeOwner(attackerID);
                ServerSession::GetInstance().GetWorldState()->GetPlayer(attackerID)->AddCityCenter(districtTargeted->GetPosition(), turnCreated);
            }
            else if (districtTargeted->GetTypeAsInt() != DistrictCityCenter::DISTRICT_TYPE)
            {
                if (districtTargeted->GetTypeAsInt() == DistrictUniversity::DISTRICT_TYPE)
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

                targetTile->SetDistrict(nullptr);
            }
        }

        // Attacker is not dead, the tile is empty and attacker can move after combat (is melee?)
        if (!notification.AttackerIsDead && notification.CanMove && targetTile->IsFree())
        {
            return MoveUnit(attackerID, attackerPosition, targetPosition, attacker->GetActionPointsRemaining());
        }
        else
        {
            attacker->UseActionPoints(actionCost);
        }
    }

    return std::vector<Position>{};
}

bool MapLocal::CreateUnit(int unitType, Position pos, int owner, bool upgrade = false)
{
    if (GetTile(pos)->GetUnit() != nullptr)
    {
        return false;
    }

    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayer(owner);
    std::shared_ptr<UnitBase> unit = nullptr;

    switch (unitType)
    {
    case UnitSwordsmanI::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitSwordsmanI(owner, player->GetUtilitySkillTree().MovementUpgrade) };
        break;
    case UnitSwordsmanII::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitSwordsmanII(owner, player->GetUtilitySkillTree().MovementUpgrade) };
        break;
    case UnitSwordsmanIII::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitSwordsmanIII(owner, player->GetUtilitySkillTree().MovementUpgrade) };
        break;
    case UnitArcherI::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitArcherI(owner, player->GetUtilitySkillTree().MovementUpgrade) };
        break;
    case UnitArcherII::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitArcherII(owner, player->GetUtilitySkillTree().MovementUpgrade) };
        break;
    case UnitArcherIII::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitArcherIII(owner, player->GetUtilitySkillTree().MovementUpgrade) };
        break;
    case UnitSettler::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitSettler(owner, player->GetUtilitySkillTree().MovementUpgrade) };
        player->ConsumeFood(unit->GetFoodCost());
        break;
    case UnitBuilder::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitBuilder(owner, player->GetUtilitySkillTree().MovementUpgrade) };
        break;
    case UnitAxemanI::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitAxemanI(owner, player->GetUtilitySkillTree().MovementUpgrade) };
        break;
    case UnitAxemanII::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitAxemanII(owner, player->GetUtilitySkillTree().MovementUpgrade) };
        break;
    case UnitCannon::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitCannon(owner, player->GetUtilitySkillTree().MovementUpgrade) };
        break;
    case UnitShield::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitShield(owner, player->GetUtilitySkillTree().MovementUpgrade) };
        break;
    case UnitMaceI::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitMaceI(owner, player->GetUtilitySkillTree().MovementUpgrade) };
        break;
    case UnitMaceII::UNIT_TYPE:
        unit = std::shared_ptr<UnitBase>{ new UnitMaceII(owner, player->GetUtilitySkillTree().MovementUpgrade) };
        break;
    default:
        return false;
        break;
    }

    if (unit)
    {
        GetTile(pos)->SetUnit(unit);
        player->ConsumeWeapon(unit->GetWeaponCost() / (upgrade ? 2 : 1));
        player->ConsumeFood(unit->GetFoodCost() / (upgrade ? 2 : 1));

        DiscoverArea(pos, unit->GetViewRange(), owner);
    }
    return true;
}

bool MapLocal::CreateDistrict(int districtType, Position pos, int owner, bool upgrade = false)
{
    if (GetTile(pos)->GetDistrict() != nullptr)
    {
        return false;
    }

    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayer(owner);
    std::shared_ptr<DistrictBase> district;

    switch (districtType)
    {
    case DistrictCityCenter::DISTRICT_TYPE:
        district = std::shared_ptr<DistrictBase>{ new DistrictCityCenter(owner) };
        ServerSession::GetInstance().GetWorldState()->GetPlayer(owner)->AddCityCenter(pos, ServerSession::GetInstance().GetWorldState()->GetCurrentTurn());
        break;
    case DistrictHunter::DISTRICT_TYPE:
        district = std::shared_ptr<DistrictBase>{ new DistrictHunter(owner) };
        break;
    case DistrictFarm::DISTRICT_TYPE:
        district = std::shared_ptr<DistrictBase>{ new DistrictFarm(owner) };
        break;
    case DistrictWindMill::DISTRICT_TYPE:
        district = std::shared_ptr<DistrictBase>{ new DistrictWindMill(owner) };
        break;
    case DistrictWarehouse::DISTRICT_TYPE:
        district = std::shared_ptr<DistrictBase>{ new DistrictWarehouse(owner) };
        ServerSession::GetInstance().GetWorldState()->GetPlayer(owner)->AddFoodMultiplier(DistrictWarehouse::FOOD_BONUS);
        break;
    case DistrictBlacksmith::DISTRICT_TYPE:
        district = std::shared_ptr<DistrictBase>{ new DistrictBlacksmith(owner) };
        break;
    case DistrictStable::DISTRICT_TYPE:
        district = std::shared_ptr<DistrictBase>{ new DistrictStable(owner) };
        break;
    case DistrictFort::DISTRICT_TYPE:
        district = std::shared_ptr<DistrictBase>{ new DistrictFort(owner) };
        break;
    case DistrictMonastery::DISTRICT_TYPE:
        district = std::shared_ptr<DistrictBase>{ new DistrictMonastery(owner) };
        break;
    case DistrictCathedral::DISTRICT_TYPE:
        district = std::shared_ptr<DistrictBase>{ new DistrictCathedral(owner) };
        break;
    case DistrictSchool::DISTRICT_TYPE:
        district = std::shared_ptr<DistrictBase>{ new DistrictSchool(owner) };
        break;
    case DistrictUniversity::DISTRICT_TYPE:
        district = std::shared_ptr<DistrictBase>{ new DistrictUniversity(owner) };
        ServerSession::GetInstance().GetWorldState()->GetPlayer(owner)->AddScienceMultiplier(DistrictUniversity::SCIENCE_BONUS);
        break;
    case DistrictWatchTower::DISTRICT_TYPE:
        district = std::shared_ptr<DistrictBase>{ new DistrictWatchTower(owner) };
        break;
    case DistrictInn::DISTRICT_TYPE:
        district = std::shared_ptr<DistrictBase>{ new DistrictInn(owner) };
        break;
    case DistrictTavern::DISTRICT_TYPE:
        district = std::shared_ptr<DistrictBase>{ new DistrictTavern(owner) };
        break;
    case DistrictMilitaryTent::DISTRICT_TYPE:
        district = std::shared_ptr<DistrictBase>{ new DistrictMilitaryTent(owner) };
        ServerSession::GetInstance().GetWorldState()->GetPlayer(owner)->AddAttackMultiplier(DistrictMilitaryTent::ATTACK_MULTIPLIER);
        break;
    case DistrictFishery::DISTRICT_TYPE:
        district = std::shared_ptr<DistrictBase>{ new DistrictFishery(owner) };
        break;
    default:
        assert(false && "Add your new district here");
        return false;
        break;
    }

    if (district)
    {
        GetTile(pos)->SetDistrict(district);
        player->ConsumeFood(district->GetFoodCost() / (upgrade ? 2 : 1));
        DiscoverArea(pos, district->GetViewRange(), owner);
    }
    return true;
}

bool MapLocal::SellDistrict(Position pos, int owner)
{
    auto district = GetTile(pos)->GetDistrict();
    if (!district || district->GetOwnerID() != owner)
    {
        return false;
    }

    int refund = district->GetFoodCost() / 3;
    ServerSession::GetInstance().GetWorldState()->GetPlayer(owner)->AddFood(refund);

    GetTile(pos)->SetDistrict(nullptr);

    return true;
}

bool MapLocal::SellUnit(Position pos, int owner)
{
    auto unit = GetTile(pos)->GetUnit();
    if (!unit || unit->GetOwnerID() != owner)
    {
        return false;
    }
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayer(owner);

    player->AddWeapon(unit->GetWeaponCost() / 3);
    player->AddFood(unit->GetFoodCost() / 3);

    GetTile(pos)->SetUnit(nullptr);

    return true;
}

bool MapLocal::UpgradeUnit(Position pos, int owner)
{
    TileBase* tile = GetTile(pos);
    auto unit = tile->GetUnit();
    if (!unit || unit->GetOwnerID() != owner)
    {
        return false;
    }

    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayer(owner);

    if (unit->CanUpgrade())
    {
        // Upgrade override the unit on the tile by the new one (or override by nullptr (settler/watchTowerUnit)
        //   So we need to delete the object unit after

        if (unit->GetTypeAsInt() == UnitSettler::UNIT_TYPE || unit->GetTypeAsInt() == UnitBuilder::UNIT_TYPE)
        {
            GetTile(pos)->SetUnit(nullptr);
            return CreateDistrict(unit->GetUpgradeType(), pos, owner, true);
        }
        else
        {
            GetTile(pos)->SetUnit(nullptr);
            return CreateUnit(unit->GetUpgradeType(), pos, owner, true);
        }
    }

    return false;
}

bool MapLocal::UpgradeDistrict(Position pos, int owner)
{
    TileBase* tile = GetTile(pos);
    auto district = tile->GetDistrict();
    if (!district || district->GetOwnerID() != owner)
    {
        return false;
    }

    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayer(owner);

    if (district->CanUpgrade())
    {
        GetTile(pos)->SetDistrict(nullptr);
        CreateDistrict(district->GetUpgradeType(), pos, owner, true);

        return true;
    }

    return false;
}

bool MapLocal::HealUnit(Position pos, int owner)
{
    TileBase* tile = GetTile(pos);
    auto unit = tile->GetUnit();
    if (!unit || unit->GetOwnerID() != owner)
    {
        return false;
    }

    unit->Heal(15);
    return true;
}

bool MapLocal::RepairDistrict(Position pos, int owner)
{
    TileBase* tile = GetTile(pos);
    auto district = tile->GetDistrict();
    if (!district || district->GetOwnerID() != owner)
    {
        return false;
    }

    district->Repair(15);
    return true;
}

void MapLocal::ShareVision(int playerOne, int playerTwo)
{
    for (int row = 0; row < ROWS; ++row)
    {
        for (int column = 0; column < COLUMNS; ++column)
        {
            if (m_tiles[row][column]->IsDiscovered(playerOne))
            {
                m_tiles[row][column]->PlayerDiscover(playerTwo);
            }
            if (m_tiles[row][column]->IsDiscovered(playerTwo))
            {
                m_tiles[row][column]->PlayerDiscover(playerOne);
            }
        }
    }
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