#include "PlayerLocal.h"
#include <boost\property_tree\ptree.hpp>
#include "DistrictCityCenter.h"
#include "Map.h"
#include "MapFilter.h"
#include "ServerSession.h"

void PlayerLocal::RemoveRelation(int otherPlayerId)
{
    m_diplomaticRelations.erase(otherPlayerId);
}

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
    player->m_diplomaticRelations.insert(m_diplomaticRelations.begin(), m_diplomaticRelations.end());

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

    if (m_cityCenterLocations.size() <= 0)
    {
        SetIsAlive(false);
    }

    if (m_isAlive)
    {
        UpdateTilesOwned(turn, map);
        for (auto it = m_diplomaticRelations.begin(); it != m_diplomaticRelations.end(); ++it)
        {
            RelationStatus status = it->second.GetRelationStatus();
            int propositionTurn = it->second.GetPropositionTurn();
            if (status == RelationStatus::NegocatingAlliance && propositionTurn + OFFER_DURATION <= turn)
            {
                it->second.ChangeRelationStatus(RelationStatus::Peace, turn);
            }
            else if (status == RelationStatus::NegociatingPeace && propositionTurn + OFFER_DURATION <= turn)
            {
                it->second.ChangeRelationStatus(RelationStatus::War, turn);
            }
            else if (status == RelationStatus::Alliance && propositionTurn + OFFER_DURATION <= turn)
            {
                it->second.ChangeRelationStatus(RelationStatus::Peace, turn);
            }
        }
    }
}

void PlayerLocal::SetPlayerReadyForNextTurn(bool isReady)
{
    m_isReadyForNewTurn = isReady;
}

void PlayerLocal::SetIsAlive(bool value)
{
    if (value)
    {
        auto players = ServerSession::GetInstance().GetWorldState()->GetPlayers();
        for (auto p : players)
        {
            p->AddNewRelation(m_playerID);
            AddNewRelation(p->GetPlayerID());
        }
    }
    else
    {
        auto players = ServerSession::GetInstance().GetWorldState()->GetPlayers();
        for (auto p : players)
        {
            p->RemoveRelation(m_playerID);
        }
        m_diplomaticRelations.clear();
    }
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

void PlayerLocal::RemoveFoodMultiplier(double multiplier)
{
    // no unsigned double so valid we dont go under 0
    if (m_foodMultiplier >= multiplier)
    {
        m_foodMultiplier -= multiplier;
    }
    else
    {
        m_foodMultiplier = 0.0;
    }
}

void PlayerLocal::RemoveScienceMultiplier(double multiplier)
{
    // no unsigned double so valid we dont go under 0
    if (m_scienceMultiplier >= multiplier)
    {
        m_scienceMultiplier -= multiplier;
    }
    else
    {
        m_scienceMultiplier = 0.0;
    }
}

void PlayerLocal::RemoveWeaponMultiplier(double multiplier)
{
    // no unsigned double so valid we dont go under 0
    if (m_weaponMultiplier >= multiplier)
    {
        m_weaponMultiplier -= multiplier;
    }
    else
    {
        m_weaponMultiplier = 0.0;
    }
}

void PlayerLocal::AddCityCenter(Position pos, int turn)
{
    m_cityCenterLocations.insert(map<Position, int>::value_type(pos, turn));
}

void PlayerLocal::RemoveCityCenter(Position pos)
{
    if (m_cityCenterLocations.find(pos) != m_cityCenterLocations.end())
    {
        m_cityCenterLocations.erase(pos);
    }

    if (m_cityCenterLocations.size() <= 0)
    {
        SetIsAlive(false);
    }
}

void PlayerLocal::SetIsDisconnected(bool value)
{
    m_isDisconnected = true;
}

void PlayerLocal::AddNewRelation(int otherPlayerId, int currentTurn, RelationStatus status, int mustAnswerPlayerId)
{
    auto relation = m_diplomaticRelations.find(otherPlayerId);
    if (relation == m_diplomaticRelations.end())
    {
        m_diplomaticRelations.insert(std::map<int, DiplomaticRelation>::value_type(otherPlayerId, DiplomaticRelation(currentTurn, status, mustAnswerPlayerId)));
    }
}
void PlayerLocal::SendPeaceProposition(int otherPlayerId, int currentTurn)
{
    auto relation = m_diplomaticRelations.find(otherPlayerId);
    if (relation != m_diplomaticRelations.end() && relation->second.GetRelationStatus() == RelationStatus::War)
    {
        relation->second.ChangeRelationStatus(RelationStatus::NegociatingPeace, currentTurn, otherPlayerId);
    }
}

void PlayerLocal::ReceivePeaceProposition(int otherPlayerId, int currentTurn)
{
    auto relation = m_diplomaticRelations.find(otherPlayerId);
    if (relation->second.GetRelationStatus() == RelationStatus::War)
    {
        relation->second.ChangeRelationStatus(RelationStatus::NegociatingPeace, currentTurn, m_playerID);
    }
}

void PlayerLocal::RespondPeaceProposition(int otherPlayerId, int currentTurn, bool answer)
{
    assert(false && "Should not be used on a local Player");
}

void PlayerLocal::GoToPeace(int otherPlayerId, int currentTurn)
{
    auto relation = m_diplomaticRelations.find(otherPlayerId);
    if (relation != m_diplomaticRelations.end()
        && (relation->second.GetRelationStatus() == RelationStatus::NegociatingPeace
            || relation->second.GetRelationStatus() == RelationStatus::NegocatingAlliance))
    {
        relation->second.ChangeRelationStatus(RelationStatus::Peace, currentTurn);
    }
}

void PlayerLocal::SendAllianceProposition(int otherPlayerId, int currentTurn)
{
    auto relation = m_diplomaticRelations.find(otherPlayerId);
    if (relation != m_diplomaticRelations.end() && relation->second.GetRelationStatus() == RelationStatus::Peace)
    {
        relation->second.ChangeRelationStatus(RelationStatus::NegocatingAlliance, currentTurn, otherPlayerId);
    }
}

void PlayerLocal::ReceiveAllianceProposition(int otherPlayerId, int currentTurn)
{
    auto relation = m_diplomaticRelations.find(otherPlayerId);
    if (relation->second.GetRelationStatus() == RelationStatus::Peace)
    {
        relation->second.ChangeRelationStatus(RelationStatus::NegocatingAlliance, currentTurn, m_playerID);
    }
}

void PlayerLocal::RespondAllianceProposition(int otherPlayerId, int currentTurn, bool answer)
{
    assert(false && "This should not be used on a local Player");
}

void PlayerLocal::GoToAlliance(int otherPlayerId, int currentTurn)
{
    auto relation = m_diplomaticRelations.find(otherPlayerId);
    if (relation != m_diplomaticRelations.end() && relation->second.GetRelationStatus() == RelationStatus::NegocatingAlliance)
    {
        relation->second.ChangeRelationStatus(RelationStatus::Alliance, currentTurn);
    }
}

void PlayerLocal::GoToWar(int otherPlayerId, int currentTurn)
{
    auto relation = m_diplomaticRelations.find(otherPlayerId);
    if (relation != m_diplomaticRelations.end() && relation->second.GetRelationStatus() != RelationStatus::War && relation->second.GetRelationStatus() != RelationStatus::Alliance)
    {
        relation->second.ChangeRelationStatus(RelationStatus::War, currentTurn);
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

    auto diplomaticRelationsNode = playerNode.get_child("DR");
    for (auto relationNode : diplomaticRelationsNode)
    {
        if (relationNode.first == "R")
        {
            int SP = relationNode.second.get<int>("<xmlattr>.SP");
            RelationStatus RS = static_cast<RelationStatus>(relationNode.second.get<int>("<xmlattr>.RS"));
            int MA = relationNode.second.get<int>("<xmlattr>.MA");
            int PT = relationNode.second.get<int>("<xmlattr>.PT");
            player->m_diplomaticRelations.insert(std::map<int, DiplomaticRelation>::value_type(SP, DiplomaticRelation(PT, RS, MA)));
        }
        else
        {
            assert(false && "You added a new node in player serialize. You need to Deserialize it");
        }
    }

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
        if (cityCenterTier > DistrictCityCenter::TURN_FOR_BORDER_T4)
        {
            ownedTiles = map->GetArea(cityCenter.first, 4, NO_FILTER);
        }
        else if (cityCenterTier > DistrictCityCenter::TURN_FOR_BORDER_T3)
        {
            ownedTiles = map->GetArea(cityCenter.first, 3, NO_FILTER);
        }
        else if (cityCenterTier > DistrictCityCenter::TURN_FOR_BORDER_T2)
        {
            ownedTiles = map->GetArea(cityCenter.first, 2, NO_FILTER);
        }
        else if (cityCenterTier > DistrictCityCenter::TURN_FOR_BORDER_T1)
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