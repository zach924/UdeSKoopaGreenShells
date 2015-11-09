#include "PlayerLocal.h"
#include <boost\property_tree\ptree.hpp>

void PlayerLocal::RemoveRelation(int otherPlayerId)
{
    auto relation = m_diplomaticRelations.find(otherPlayerId);
    m_diplomaticRelations.erase(relation);
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
    player->m_cityCenterCount = m_cityCenterCount;
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

void PlayerLocal::NotifyNewTurn()
{
    m_isReadyForNewTurn = false;

    if (m_isAlive)
    {
        //Do stuff
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

void PlayerLocal::AddCityCenter()
{
    ++m_cityCenterCount;
}

void PlayerLocal::RemoveCityCenter()
{
    --m_cityCenterCount;

    if (m_cityCenterCount <= 0)
    {
        m_isAlive = false;
    }
}

void PlayerLocal::SetIsDisconnected(bool value)
{
    m_isDisconnected = true;
}

void PlayerLocal::AddNewRelation(int otherPlayerId, RelationStatus status, int mustAnswerPlayerId)
{
    auto relation = m_diplomaticRelations.find(otherPlayerId);
    if (relation == m_diplomaticRelations.end())
    {
        m_diplomaticRelations[otherPlayerId] = DiplomaticRelation(status, mustAnswerPlayerId);
    }
}
void PlayerLocal::SendPeaceProposition(int otherPlayerId)
{
    auto relation = m_diplomaticRelations.find(otherPlayerId);
    if (relation != m_diplomaticRelations.end() && relation->second.GetRelationStatus() == RelationStatus::War)
    {
        m_diplomaticRelations[otherPlayerId].ChangeRelationStatus(RelationStatus::NegociatingPeace, otherPlayerId);
    }
}

void PlayerLocal::ReceivePeaceProposition(int otherPlayerId)
{
    auto relation = m_diplomaticRelations[otherPlayerId];
    if (relation.GetRelationStatus() == RelationStatus::War)
    {
        relation.ChangeRelationStatus(RelationStatus::NegociatingPeace, m_playerID);
    }
}

void PlayerLocal::RespondPeaceProposition(int otherPlayerId, bool answer)
{
    assert(false && "Should not be used on a local Player");
}

void PlayerLocal::GoToPeace(int otherPlayerId)
{
    auto relation = m_diplomaticRelations.find(otherPlayerId);
    if (relation != m_diplomaticRelations.end() && relation->second.GetRelationStatus() == RelationStatus::NegociatingPeace)
    {
        m_diplomaticRelations[otherPlayerId].ChangeRelationStatus(RelationStatus::Peace);
    }
}

void PlayerLocal::SendAllianceProposition(int otherPlayerId)
{
    auto relation = m_diplomaticRelations.find(otherPlayerId);
    if (relation != m_diplomaticRelations.end() && relation->second.GetRelationStatus() == RelationStatus::Peace)
    {
        m_diplomaticRelations[otherPlayerId].ChangeRelationStatus(RelationStatus::NegocatingAlliance, otherPlayerId);
    }
}

void PlayerLocal::ReceiveAllianceProposition(int otherPlayerId)
{
    auto relation = m_diplomaticRelations[otherPlayerId];
    if (relation.GetRelationStatus() == RelationStatus::Peace)
    {
        relation.ChangeRelationStatus(RelationStatus::NegocatingAlliance, m_playerID);
    }
}

void PlayerLocal::RespondAllianceProposition(int otherPlayerId, bool answer)
{
    assert(false && "This should not be used on a local Player");
}

void PlayerLocal::GoToAlliance(int otherPlayerId)
{
    auto relation = m_diplomaticRelations.find(otherPlayerId);
    if (relation != m_diplomaticRelations.end() && relation->second.GetRelationStatus() == RelationStatus::NegocatingAlliance)
    {
        m_diplomaticRelations[otherPlayerId].ChangeRelationStatus(RelationStatus::Alliance);
    }
}

void PlayerLocal::GoToWar(int otherPlayerId)
{
    auto relation = m_diplomaticRelations.find(otherPlayerId);
    if (relation != m_diplomaticRelations.end() && relation->second.GetRelationStatus() != RelationStatus::War && relation->second.GetRelationStatus() != RelationStatus::Alliance)
    {
        m_diplomaticRelations[otherPlayerId].ChangeRelationStatus(RelationStatus::War);
    }
}

PlayerLocal* PlayerLocal::Deserialize(boost::property_tree::ptree playerNode)
{
    PlayerLocal* player = new PlayerLocal();

    player->m_playerID = playerNode.get<int>("<xmlattr>.PId");
    player->m_playerName = playerNode.get<std::string>("<xmlattr>.PName");
    player->m_cityCenterCount = playerNode.get<int>("<xmlattr>.CHC");
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
            player->m_diplomaticRelations[SP] = DiplomaticRelation(RS, MA);
        }
        else
        {
            assert(false && "You added a new node in player serialize. You need to Deserialize it");
        }
    }
    return player;
}