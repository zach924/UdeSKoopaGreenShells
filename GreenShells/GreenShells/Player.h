#pragma once
#include <vector>
#include "Ptree_ForwardDeclaration.h"
#include "UtilitySkillTree.h"
#include "ArmySkillTree.h"
#include "EmpireSkillTree.h"


class Player
{
    std::string m_playerName;
    int m_playerID;
    bool m_isReadyForNewTurn;

    bool m_isAlive;
	bool m_isDisconnected;
    
    unsigned int m_cityCenterCount;
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

public:
    Player();
    ~Player();

	void SetPlayerName(std::string name);
	std::string GetPlayerName();

	void SetPlayerID(int ID);
    int GetPlayerID();

    void NotifyNewTurn();

    void SetPlayerReadyForNextTurn(bool isReady = true);
    bool IsPlayerReadyForNextTurn();

	void SetIsAlive(bool value);
	bool IsAlive();
    int GetFood();
    int GetScience();
    int GetWeapon();

    void AddFood(unsigned int qty);
    void AddScience(unsigned int qty);
    void AddWeapon(unsigned int qty);

    bool ConsumeFood(unsigned int qty);
    bool ConsumeScience(unsigned int qty);
    bool ConsumeWeapon(unsigned int qty);

    void AddFoodMultiplier(double multiplier);
    void AddScienceMultiplier(double multiplier);
    void AddWeaponMultiplier(double multiplier);

    // TODO : When gameplay will be more canon, see if the multiplier can go under 1.0 (Ennemy affecting my ratio)
    void RemoveFoodMultiplier(double multiplier);
    void RemoveScienceMultiplier(double multiplier);
    void RemoveWeaponMultiplier(double multiplier);

	void AddCityCenter();
	void RemoveCityCenter();

	void SetIsDisconnected(bool value=true);
	bool IsDisconnected();

    boost::property_tree::ptree Serialize();
    static Player Deserialize(boost::property_tree::ptree playerNode);

};

