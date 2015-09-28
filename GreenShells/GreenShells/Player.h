#pragma once
#include <vector>
#include "Unit.h"
#include "District.h"

namespace boost
{
    namespace property_tree
    {
        template < class Key, class Data, class KeyCompare >
        class basic_ptree;

        typedef basic_ptree< std::string, std::string, std::less<std::string> > ptree;
    }
}


class Player
{
    static int playerIDCounter;

    std::string m_playerName;
    int m_playerID;
    bool m_isReadyForNewTurn;

    bool m_isAlive;
    
    unsigned int m_cityHallCount;
    unsigned int m_unitCount;

    unsigned int m_food;
    unsigned int m_science;
    unsigned int m_weapon;

    double m_foodMultiplier;
    double m_scienceMultiplier;
    double m_weaponMultiplier;

public:
    Player();
    ~Player();

    int GetPlayerID();

    void NotifyNewTurn();

    void SetPlayerReadyForNextTurn(bool isReady = true);
    bool IsPlayerReadyForNextTurn();

    void SetPlayerDead();

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


    boost::property_tree::ptree Serialize();

};

