#pragma once
#include "Player.h"
class PlayerLocal :
    public Player
{
public:
    PlayerLocal();
    ~PlayerLocal();
    virtual Player* Clone();
    virtual void SetPlayerName(std::string name);
    virtual void SetPlayerID(int ID);
    virtual void NotifyNewTurn();
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
    virtual void RemoveFoodMultiplier(double multiplier);
    virtual void RemoveScienceMultiplier(double multiplier);
    virtual void RemoveWeaponMultiplier(double multiplier);
    virtual void AddCityCenter();
    virtual void RemoveCityCenter();
    virtual void SetIsDisconnected(bool value = true);
    static PlayerLocal* Deserialize(boost::property_tree::ptree playerNode);
};

