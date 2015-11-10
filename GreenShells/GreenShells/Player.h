#pragma once
#include <vector>
#include <map>
#include "Ptree_ForwardDeclaration.h"
#include "MapFilter.h"
#include "UtilitySkillTree.h"
#include "ArmySkillTree.h"
#include "EmpireSkillTree.h"
#include "DiplomaticRelation.h"
#include "Position.h"

class Map;

class Player
{
protected:
    std::string m_playerName;
    int m_playerID;
    bool m_isReadyForNewTurn;

    bool m_isAlive;
    bool m_isDisconnected;

    std::map<Position, int> m_cityCenterLocations;
    unsigned int m_unitCount;

    unsigned int m_food;
    unsigned int m_science;
    unsigned int m_weapon;

    double m_foodMultiplier;
    double m_scienceMultiplier;
    double m_weaponMultiplier;

    UtilitySkillTree m_utilitySkillTree;
    ArmySkillTree m_armySkillTree;
    EmpireSkillTree m_empireSkillTree;

    //Diplomacy
    std::map<int, DiplomaticRelation> m_diplomaticRelations;
    virtual void RemoveRelation(int otherPlayerId) = 0;

public:
    Player();
    ~Player();

    virtual Player* Clone() = 0;
    virtual void SetPlayerName(std::string name) = 0;
    std::string GetPlayerName();

    virtual void SetPlayerID(int ID) = 0;
    int GetPlayerID();

    virtual void NotifyNewTurn(int turn, Map* map) = 0;

    virtual void SetPlayerReadyForNextTurn(bool isReady = true) = 0;
    bool IsPlayerReadyForNextTurn();

    virtual void SetIsAlive(bool value) = 0;
    bool IsAlive();
    int GetFood();
    int GetScience();
    int GetWeapon();

    virtual void AddFood(unsigned int qty) = 0;
    virtual void AddScience(unsigned int qty) = 0;
    virtual void AddWeapon(unsigned int qty) = 0;

    virtual bool ConsumeFood(unsigned int qty) = 0;
    virtual bool ConsumeScience(unsigned int qty) = 0;
    virtual bool ConsumeWeapon(unsigned int qty) = 0;

    virtual void AddFoodMultiplier(double multiplier) = 0;
    virtual void AddScienceMultiplier(double multiplier) = 0;
    virtual void AddWeaponMultiplier(double multiplier) = 0;

    // TODO : When gameplay will be more canon, see if the multiplier can go under 1.0 (Ennemy affecting my ratio)
    virtual void RemoveFoodMultiplier(double multiplier) = 0;
    virtual void RemoveScienceMultiplier(double multiplier) = 0;
    virtual void RemoveWeaponMultiplier(double multiplier) = 0;

    virtual void AddCityCenter(Position pos, int turn) = 0;
    virtual void RemoveCityCenter(Position pos) = 0;

    //Diplomacy
    std::map<int, DiplomaticRelation> GetDiplomaticRelations();
    virtual void AddNewRelation(int otherPlayerId, RelationStatus status = RelationStatus::Peace, int mustAnswerPlayerId = -1) = 0;
    virtual void SendPeaceProposition(int otherPlayerId) = 0;
    virtual void ReceivePeaceProposition(int otherPlayerId) = 0;
    virtual void RespondPeaceProposition(int otherPlayerId, bool answer) = 0;
    virtual void GoToPeace(int otherPlayerId) = 0;

    virtual void SendAllianceProposition(int otherPlayerId) = 0;
    virtual void ReceiveAllianceProposition(int otherPlayerId) = 0;
    virtual void GoToAlliance(int otherPlayerId) = 0;
    virtual void RespondAllianceProposition(int otherPlayerId, bool answer) = 0;
    virtual void GoToWar(int otherPlayerId) = 0;

    virtual void SetIsDisconnected(bool value = true) = 0;
    bool IsDisconnected();

    MapFilter GetMoveRestriction();

    virtual boost::property_tree::ptree Serialize();
};
