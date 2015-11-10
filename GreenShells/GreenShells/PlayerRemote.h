#pragma once
#include "Player.h"
#include "RPCBase.h"

class PlayerRemote :
    public Player, public RPCBase
{

    virtual void RemoveRelation(int otherPlayerId);

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
    virtual void RemoveFoodMultiplier(double multiplier);
    virtual void RemoveScienceMultiplier(double multiplier);
    virtual void RemoveWeaponMultiplier(double multiplier);
    virtual void AddCityCenter(Position pos, int turn);
    virtual void RemoveCityCenter(Position pos);
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
    static PlayerRemote* Deserialize(boost::property_tree::ptree playerNode);
};

