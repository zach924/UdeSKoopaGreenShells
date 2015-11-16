#include "PlayerLocal.h"
#include <boost\property_tree\ptree.hpp>
#include "DistrictCityCenter.h"
#include "Map.h"
#include "MapFilter.h"

PlayerLocal::PlayerLocal()
    :Player()
{
}

PlayerLocal::~PlayerLocal()
{
}

Player* PlayerLocal::Clone()
{
    PlayerLocal* player = new PlayerLocal{};

    player->m_playerName = m_playerName;
    player->m_playerID = m_playerID;
    player->m_isReadyForNewTurn = m_isReadyForNewTurn;
    player->m_isAlive = m_isAlive;
    player->m_isDisconnected = m_isDisconnected;
    player->m_cityCenterLocations = m_cityCenterLocations;
    player->m_unitCount = m_unitCount;
    player->m_food = m_food;
    player->m_science = m_science;
    player->m_weapon = m_weapon;
    player->m_foodMultiplier = m_foodMultiplier;
    player->m_scienceMultiplier = m_scienceMultiplier;
    player->m_weaponMultiplier = m_weaponMultiplier;
    player->m_utilitySkillTree = m_utilitySkillTree;
    player->m_armySkillTree = m_armySkillTree;
    player->m_empireSkillTree = m_empireSkillTree;

    return player;
}

void PlayerLocal::SetPlayerName(std::string name)
{
    m_playerName = name;
}

void PlayerLocal::SetPlayerID(int ID)
{
    m_playerID = ID;
}

void PlayerLocal::NotifyNewTurn(int turn, Map* map)
{
    m_isReadyForNewTurn = false;

    if (m_isAlive)
    {
        UpdateTilesOwned(turn, map);
    }
}

void PlayerLocal::SetPlayerReadyForNextTurn(bool isReady)
{
    m_isReadyForNewTurn = isReady;
}

void PlayerLocal::SetIsAlive(bool value)
{
    m_isAlive = value;
}


void PlayerLocal::AddFood(unsigned int qty)
{
    m_food += static_cast<unsigned int>(qty * m_foodMultiplier);
}

void PlayerLocal::AddScience(unsigned int qty)
{
    m_science += static_cast<unsigned int>(qty * m_scienceMultiplier);
}

void PlayerLocal::AddWeapon(unsigned int qty)
{
    m_weapon += static_cast<unsigned int>(qty * m_weaponMultiplier);
}

bool PlayerLocal::ConsumeFood(unsigned int qty)
{
    bool enoughtRessource = m_food >= qty;

    if (enoughtRessource)
    {
        m_food -= qty;
    }
    return enoughtRessource;
}

bool PlayerLocal::ConsumeScience(unsigned int qty)
{
    bool enoughtRessource = m_science >= qty;

    if (enoughtRessource)
    {
        m_science -= qty;
    }
    return enoughtRessource;
}

bool PlayerLocal::ConsumeWeapon(unsigned int qty)
{
    bool enoughtRessource = m_weapon >= qty;

    if (enoughtRessource)
    {
        m_weapon -= qty;
    }
    return enoughtRessource;
}

void PlayerLocal::AddFoodMultiplier(double multiplier)
{
    m_foodMultiplier += multiplier;
}

void PlayerLocal::AddScienceMultiplier(double multiplier)
{
    m_scienceMultiplier += multiplier;
}

void PlayerLocal::AddWeaponMultiplier(double multiplier)
{
    m_weaponMultiplier += multiplier;
}

void PlayerLocal::AddCityCenter(Position pos, int turn)
{
    m_cityCenterLocations[pos] = turn;
}

void PlayerLocal::RemoveCityCenter(Position pos)
{
    m_cityCenterLocations.erase(pos);

    if (m_cityCenterLocations.size() <= 0)
    {
        m_isAlive = false;
    }
}

void PlayerLocal::SetIsDisconnected(bool value)
{
    m_isDisconnected = true;
}

void PlayerLocal::UnlockSkill(int turn, Skills skill)
{
    switch (skill)
    {
    case Watchtower:
        if (m_science >= SKILL_COST_TIER1)
        {
            m_science -= SKILL_COST_TIER1;
            m_utilitySkillTree.Watchtower = true;
        }
        break;
    case ScienceUpgrade:
        if (m_science >= SKILL_COST_TIER2)
        {
            m_science -= SKILL_COST_TIER2;
            m_utilitySkillTree.ScienceUpgrade = true;
            AddScienceMultiplier(0.15);
        }
        break;
    case BorderGrowth:
        if (m_science >= SKILL_COST_TIER3)
        {
            m_science -= SKILL_COST_TIER3;
            m_utilitySkillTree.BorderGrowth = true;
        }
        break;
    case MovementUpgrade:
        if (m_science >= SKILL_COST_TIER4)
        {
            m_science -= SKILL_COST_TIER4;
            m_utilitySkillTree.MovementUpgrade = true;
            //TODO after merge
        }
        break;
    case Embark:
        if (m_science >= SKILL_COST_TIER4)
        {
            m_science -= SKILL_COST_TIER4;
            m_utilitySkillTree.Embark = true;
        }
        break;
    case VisionUpgrade:
        if (m_science >= SKILL_COST_TIER5)
        {
            m_science -= SKILL_COST_TIER5;
            m_utilitySkillTree.VisionUpgrade = true;
        }
        break;
    case MountainWalking:
        if (m_science >= SKILL_COST_TIER5)
        {
            m_science -= SKILL_COST_TIER5;
            m_utilitySkillTree.MountainWalking = true;
        }
        break;
    case MountainConstruction:
        if (m_science >= SKILL_COST_TIER6)
        {
            m_science -= SKILL_COST_TIER6;
            m_utilitySkillTree.MountainConstruction = true;
        }
        break;
    case ArmorUpgrade:
        if (m_science >= SKILL_COST_TIER6)
        {
            m_science -= SKILL_COST_TIER6;
            m_utilitySkillTree.ArmorUpgrade = true;
        }
        break;
    case University:
        if (m_science >= SKILL_COST_TIER7)
        {
            m_science -= SKILL_COST_TIER7;
            m_utilitySkillTree.University = true;
        }
        break;
    case NoFogOfWar:
        if (m_science >= SKILL_COST_TIER7)
        {
            m_science -= SKILL_COST_TIER7;
            m_utilitySkillTree.NoFogOfWar = true;
        }
        break;
    case Militia:
        if (m_science >= SKILL_COST_TIER2)
        {
            m_science -= SKILL_COST_TIER2;
            m_armySkillTree.Militia = true;
        }
        break;
    case RangerT1:
        if (m_science >= SKILL_COST_TIER1)
        {
            m_science -= SKILL_COST_TIER1;
            m_armySkillTree.RangerT1 = true;
        }
        break;
    case RangerT2:
        if (m_science >= SKILL_COST_TIER4)
        {
            m_science -= SKILL_COST_TIER4;
            m_armySkillTree.RangerT2 = true;
        }
        break;
    case RangerT3:
        if (m_science >= SKILL_COST_TIER6)
        {
            m_science -= SKILL_COST_TIER6;
            m_armySkillTree.RangerT3 = true;
        }
        break;
    case SwordT2:
        if (m_science >= SKILL_COST_TIER3)
        {
            m_science -= SKILL_COST_TIER3;
            m_armySkillTree.SwordT2 = true;
        }
        break;
    case SwordT3:
        if (m_science >= SKILL_COST_TIER4)
        {
            m_science -= SKILL_COST_TIER4;
            m_armySkillTree.SwordT3 = true;
        }
        break;
    case AxeT1:
        if (m_science >= SKILL_COST_TIER3)
        {
            m_science -= SKILL_COST_TIER3;
            m_armySkillTree.AxeT1 = true;
        }
        break;
    case AxeT2:
        if (m_science >= SKILL_COST_TIER4)
        {
            m_science -= SKILL_COST_TIER4;
            m_armySkillTree.AxeT2 = true;
        }
        break;
    case MaceT1:
        if (m_science >= SKILL_COST_TIER5)
        {
            m_science -= SKILL_COST_TIER5;
            m_armySkillTree.MaceT1 = true;
        }
        break;
    case MaceT2:
        if (m_science >= SKILL_COST_TIER6)
        {
            m_science -= SKILL_COST_TIER6;
            m_armySkillTree.MaceT2 = true;
        }
        break;
    case Fortress:
        if (m_science >= SKILL_COST_TIER7)
        {
            m_science -= SKILL_COST_TIER7;
            m_armySkillTree.Fortress = true;
        }
        break;
    case Shield:
        if (m_science >= SKILL_COST_TIER7)
        {
            m_science -= SKILL_COST_TIER7;
            m_armySkillTree.Shield = true;
        }
        break;
    case Canon:
        if (m_science >= SKILL_COST_TIER8)
        {
            m_science -= SKILL_COST_TIER8;
            m_armySkillTree.Canon = true;
        }
        break;
    case Settler:
        if (m_science >= SKILL_COST_TIER1)
        {
            m_science -= SKILL_COST_TIER1;
            m_empireSkillTree.Settler = true;
        }
        break;
    case Monastery:
        if (m_science >= SKILL_COST_TIER2)
        {
            m_science -= SKILL_COST_TIER2;
            m_empireSkillTree.Monastery = true;
        }
        break;
    case Farm:
        if (m_science >= SKILL_COST_TIER3)
        {
            m_science -= SKILL_COST_TIER3;
            m_empireSkillTree.Farm = true;
        }
        break;
    case Windmill:
        if (m_science >= SKILL_COST_TIER4)
        {
            m_science -= SKILL_COST_TIER4;
            m_empireSkillTree.Windmill = true;
        }
        break;
    case Fishery:
        if (m_science >= SKILL_COST_TIER3)
        {
            m_science -= SKILL_COST_TIER3;
            m_empireSkillTree.Fishery = true;
        }
        break;
    case Stable:
        if (m_science >= SKILL_COST_TIER3)
        {
            m_science -= SKILL_COST_TIER3;
            m_empireSkillTree.Stable = true;
        }
        break;
    case Cathedral:
        if (m_science >= SKILL_COST_TIER4)
        {
            m_science -= SKILL_COST_TIER4;
            m_empireSkillTree.Cathedral = true;
        }
        break;
    case Fort:
        if (m_science >= SKILL_COST_TIER4)
        {
            m_science -= SKILL_COST_TIER4;
            m_empireSkillTree.Fort = true;
        }
        break;
    case MilitaryTent:
        if (m_science >= SKILL_COST_TIER5)
        {
            m_science -= SKILL_COST_TIER5;
            m_empireSkillTree.MilitaryTent = true;
        }
        break;
    case InnAndTavern:
        if (m_science >= SKILL_COST_TIER5)
        {
            m_science -= SKILL_COST_TIER5;
            m_empireSkillTree.InnAndTavern = true;
        }
        break;
    case Warehouse:
        if (m_science >= SKILL_COST_TIER6)
        {
            m_science -= SKILL_COST_TIER6;
            m_empireSkillTree.Warehouse = true;
        }
        break;
    case RessourcesBonus:
        if (m_science >= SKILL_COST_TIER7)
        {
            m_science -= SKILL_COST_TIER7;
            m_empireSkillTree.RessourcesBonus = true;
        }
        break;
    default:
        assert(false && "Tried unlocking a random skill...");
        break;
    }
}

PlayerLocal* PlayerLocal::Deserialize(boost::property_tree::ptree playerNode)
{
    PlayerLocal* player = new PlayerLocal();

    player->m_playerID = playerNode.get<int>("<xmlattr>.PId");
    player->m_playerName = playerNode.get<std::string>("<xmlattr>.PName");
    player->m_unitCount = playerNode.get<int>("<xmlattr>.UC");
    player->m_food = playerNode.get<int>("<xmlattr>.F");
    player->m_science = playerNode.get<int>("<xmlattr>.S");
    player->m_weapon = playerNode.get<int>("<xmlattr>.W");
    player->m_foodMultiplier = playerNode.get<double>("<xmlattr>.FM");
    player->m_scienceMultiplier = playerNode.get<double>("<xmlattr>.SM");
    player->m_weaponMultiplier = playerNode.get<double>("<xmlattr>.WM");
    player->m_isAlive = playerNode.get<bool>("<xmlattr>.IA");
    player->m_isReadyForNewTurn = playerNode.get<bool>("<xmlattr>.IR");
    player->m_isDisconnected = playerNode.get<bool>("<xmlattr>.ID");
    player->m_utilitySkillTree = UtilitySkillTree(playerNode.get<std::string>("<xmlattr>.UST"));
    player->m_empireSkillTree = EmpireSkillTree(playerNode.get<std::string>("<xmlattr>.EST"));
    player->m_armySkillTree = ArmySkillTree(playerNode.get<std::string>("<xmlattr>.AST"));

    for (auto cityCenterNode : playerNode.get_child("CCL"))
    {
        int column = cityCenterNode.second.get<int>("<xmlattr>.Co");
        int row = cityCenterNode.second.get<int>("<xmlattr>.Ro");
        int turnFounded = cityCenterNode.second.get<int>("<xmlattr>.TF");
        player->m_cityCenterLocations[Position{ column , row }] = turnFounded;
    }
    return player;
}

void PlayerLocal::UpdateTilesOwned(int turn, Map* map)
{
    for (auto cityCenter : m_cityCenterLocations)
    {
        std::vector<Position> ownedTiles;
        int cityCenterTier = turn - cityCenter.second;
        if (cityCenterTier > (m_utilitySkillTree.BorderGrowth ? DistrictCityCenter::TURN_FOR_BORDER_T4 : DistrictCityCenter::TURN_FOR_BORDER_T4 * BORDER_GROWTH_BONUS_RATE) )
        {
            ownedTiles = map->GetArea(cityCenter.first, 4, NO_FILTER);
        }
        else if (cityCenterTier > (m_utilitySkillTree.BorderGrowth ? DistrictCityCenter::TURN_FOR_BORDER_T3 : DistrictCityCenter::TURN_FOR_BORDER_T3 * BORDER_GROWTH_BONUS_RATE))
        {
            ownedTiles = map->GetArea(cityCenter.first, 3, NO_FILTER);
        }
        else if (cityCenterTier > (m_utilitySkillTree.BorderGrowth ? DistrictCityCenter::TURN_FOR_BORDER_T2 : DistrictCityCenter::TURN_FOR_BORDER_T2 * BORDER_GROWTH_BONUS_RATE))
        {
            ownedTiles = map->GetArea(cityCenter.first, 2, NO_FILTER);
        }
        else if (cityCenterTier > (m_utilitySkillTree.BorderGrowth ? DistrictCityCenter::TURN_FOR_BORDER_T1 : DistrictCityCenter::TURN_FOR_BORDER_T1 * BORDER_GROWTH_BONUS_RATE))
        {
            ownedTiles = map->GetArea(cityCenter.first, 1, NO_FILTER);
        }
        else
        {
            ownedTiles = map->GetArea(cityCenter.first, 0, NO_FILTER);
        }

        for (auto position : ownedTiles)
        {
            if (map->GetTile(position)->GetPlayerOwnerId() == -1)
            {
                map->GetTile(position)->SetPlayerOwnerId(m_playerID);
            }
        }
    }
}