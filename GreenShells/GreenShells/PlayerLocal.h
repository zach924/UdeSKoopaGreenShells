#pragma once
#include "Player.h"
class PlayerLocal :
    public Player
{
protected:
    virtual void RemoveRelation(int otherPlayerId);

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
    virtual void AddNewRelation(int otherPlayerId, RelationStatus status = RelationStatus::Peace, int mustAnswerPlayerId = -1);
    virtual void SendPeaceProposition(int otherPlayerId);
    virtual void ReceivePeaceProposition(int otherPlayerId);
    virtual void RespondPeaceProposition(int otherPlayerId, bool answer);
    virtual void GoToPeace(int otherPlayerId);
    virtual void SendAllianceProposition(int otherPlayerId);
    virtual void ReceiveAllianceProposition(int otherPlayerId);
    virtual void RespondAllianceProposition(int otherPlayerId, bool answer);
    virtual void GoToAlliance(int otherPlayerId);
    virtual void GoToWar(int otherPlayerId);
    static PlayerLocal* Deserialize(boost::property_tree::ptree playerNode);
};

