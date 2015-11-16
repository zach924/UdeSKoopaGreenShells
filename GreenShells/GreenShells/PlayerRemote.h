#pragma once
#include "Player.h"
#include "RPCBase.h"
#include "Skills.h"

class PlayerRemote :
    public Player, public RPCBase
{
public:
    PlayerRemote();
    ~PlayerRemote();

    virtual Player* Clone();
    virtual void SetPlayerName(std::string name);
    virtual void SetPlayerID(int ID);
    virtual void NotifyNewTurn(int turn, Map* map);
    virtual void SetPlayerReadyForNextTurn(bool isReady = true);
    virtual void SetIsAlive(bool value);
    virtual void AddFood(unsigned int qty);
    virtual void AddScience(unsigned int qty);
    virtual void AddWeapon(unsigned int qty);
    virtual bool ConsumeFood(unsigned int qty);
    virtual bool ConsumeScience(unsigned int qty);
    virtual bool ConsumeWeapon(unsigned int qty);
    virtual void AddFoodMultiplier(double multiplier);
    virtual void AddScienceMultiplier(double multiplier);
    virtual void AddWeaponMultiplier(double multiplier);
    virtual void AddCityCenter(Position pos, int turn);
    virtual void RemoveCityCenter(Position pos);
    virtual void SetIsDisconnected(bool value = true);
    virtual void UnlockSkill(int turn, Skills skill);
    static PlayerRemote* Deserialize(boost::property_tree::ptree playerNode);
};

