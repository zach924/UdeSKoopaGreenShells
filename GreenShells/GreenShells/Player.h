#pragma once
#include <vector>
#include <set>
#include <map>
#include <memory>
#include "Ptree_ForwardDeclaration.h"
#include "MapFilter.h"
#include "Skills.h"
#include "UtilitySkillTree.h"
#include "ArmySkillTree.h"
#include "EmpireSkillTree.h"
#include "DiplomaticRelation.h"
#include "Position.h"

class Map;

class Player
{
public: 
    static const int SKILL_COST_TIER1 = 10;
    static const int SKILL_COST_TIER2 = 100;
    static const int SKILL_COST_TIER3 = 250;
    static const int SKILL_COST_TIER4 = 500;
    static const int SKILL_COST_TIER5 = 1000;
    static const int SKILL_COST_TIER6 = 2000;
    static const int SKILL_COST_TIER7 = 3500;
    static const int SKILL_COST_TIER8 = 5000;

    static const double BORDER_GROWTH_BONUS_RATE; //

protected:

    static const int OFFER_DURATION = 10;
    std::string m_playerName;
    int m_playerID;
    bool m_isReadyForNewTurn;

    bool m_isAlive;
    bool m_isDisconnected;

    std::map<Position, int> m_cityCenterLocations;
    unsigned int m_unitCount;

    double m_food;
    double m_science;
    double m_weapon;

    double m_foodPerTurn;
    double m_sciencePerTurn;
    double m_weaponPerTurn;

    double m_foodMultiplier;
    double m_scienceMultiplier;
    double m_weaponMultiplier;

    double m_attackMultiplier;

    UtilitySkillTree m_utilitySkillTree;
    ArmySkillTree m_armySkillTree;
    EmpireSkillTree m_empireSkillTree;

    //Diplomacy
    std::map<int, DiplomaticRelation> m_diplomaticRelations;

public:

    Player();
    ~Player();

    virtual std::shared_ptr<Player> Clone() = 0;
    virtual void SetPlayerName(std::string name) = 0;
    std::string GetPlayerName();

    virtual void SetPlayerID(int ID) = 0;
    int GetPlayerID();

    virtual void NotifyNewTurn(int turn, Map* map) = 0;

    virtual void SetPlayerReadyForNextTurn(bool isReady = true) = 0;
    bool IsPlayerReadyForNextTurn();

    virtual void SetIsAlive(bool value) = 0;
    bool IsAlive();
    bool IsNegociating();
    int GetPrintableFoodQuantity();
    int GetPrintableScienceQuantity();
    int GetPrintableWeaponQuantity();

    int GetPrintableFoodPerTurn();
    int GetPrintableSciencePerTurn();
    int GetPrintableWeaponPerTurn();

    virtual void AddFood(unsigned int qty) = 0;
    virtual void AddScience(unsigned int qty) = 0;
    virtual void AddWeapon(unsigned int qty) = 0;

    virtual bool ConsumeFood(unsigned int qty) = 0;
    virtual bool ConsumeScience(unsigned int qty) = 0;
    virtual bool ConsumeWeapon(unsigned int qty) = 0;

    virtual void AddFoodMultiplier(double multiplier) = 0;
    virtual void AddScienceMultiplier(double multiplier) = 0;
    virtual void AddWeaponMultiplier(double multiplier) = 0;

    virtual void RemoveFoodMultiplier(double multiplier) = 0;
    virtual void RemoveScienceMultiplier(double multiplier) = 0;
    virtual void RemoveWeaponMultiplier(double multiplier) = 0;

    virtual void RemoveAttackMultiplier(double multiplier) = 0;
    virtual void AddAttackMultiplier(double multiplier) = 0;

    virtual void AddCityCenter(Position pos, int turn) = 0;
    virtual void RemoveCityCenter(Position pos) = 0;
    std::map<Position, int> GetCityCenterLocations();

    //Diplomacy
    std::map<int, DiplomaticRelation> GetDiplomaticRelations();
    virtual void AddNewRelation(int otherPlayerId, int currentTurn = 0, RelationStatus status = RelationStatus::Peace, int mustAnswerPlayerId = -1) = 0;
    virtual void RemoveRelation(int otherPlayerId) = 0;
    virtual void SendPeaceProposition(int otherPlayerId, int currentTurn) = 0;
    virtual void ReceivePeaceProposition(int otherPlayerId, int currentTurn) = 0;
    virtual void RespondPeaceProposition(int otherPlayerId, int currentTurn, bool answer) = 0;
    virtual void GoToPeace(int otherPlayerId, int currentTurn) = 0;

    virtual void SendAllianceProposition(int otherPlayerId, int currentTurn) = 0;
    virtual void ReceiveAllianceProposition(int otherPlayerId, int currentTurn) = 0;
    virtual void GoToAlliance(int otherPlayerId, int currentTurn) = 0;
    virtual void RespondAllianceProposition(int otherPlayerId, int currentTurn, bool answer) = 0;
    virtual void GoToWar(int otherPlayerId, int currentTurn) = 0;
    virtual std::set<Position> GetCityCenterTilesOwned(int currentTurn, Map* map, Position cityCenterPos);

    virtual void SetIsDisconnected(bool value = true) = 0;
    bool IsDisconnected();

    virtual void UnlockSkill(int turn, Skills skill) = 0;
    virtual boost::property_tree::ptree Serialize();
    virtual boost::property_tree::ptree SerializeOnlyPlayer();

    virtual MapFilter GetMoveRestriction();

    virtual UtilitySkillTree GetUtilitySkillTree() ; 
    virtual ArmySkillTree GetArmySkillTree();
    virtual EmpireSkillTree GetEmpireSkillTree();

    double GetAttackMultiplier();

    bool HasEnoughWeapons(unsigned int WeaponCost);
    bool HasEnoughFood(unsigned int FoodCost);

};
