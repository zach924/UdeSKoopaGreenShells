#pragma once
#include "Player.h"
#include "RPCBase.h"

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
    virtual void RemoveFoodMultiplier(double multiplier);
    virtual void RemoveScienceMultiplier(double multiplier);
    virtual void RemoveWeaponMultiplier(double multiplier);
    virtual void AddCityCenter(Position pos, int turn);
    virtual void RemoveCityCenter(Position pos);
    virtual void SetIsDisconnected(bool value = true);
    virtual void AddNewRelation(int otherPlayerId, int currentTurn = 0, RelationStatus status = RelationStatus::Peace, int mustAnswerPlayerId = -1);
    virtual void RemoveRelation(int otherPlayerId);
    virtual void SendPeaceProposition(int otherPlayerId, int currentTurn);
    virtual void ReceivePeaceProposition(int otherPlayerId, int currentTurn);
    virtual void RespondPeaceProposition(int otherPlayerId, int currentTurn, bool answer);
    virtual void GoToPeace(int otherPlayerId, int currentTurn);
    virtual void SendAllianceProposition(int otherPlayerId, int currentTurn);
    virtual void ReceiveAllianceProposition(int otherPlayerId, int currentTurn);
    virtual void RespondAllianceProposition(int otherPlayerId, int currentTurn, bool answer);
    virtual void GoToAlliance(int otherPlayerId, int currentTurn);
    virtual void GoToWar(int otherPlayerId, int currentTurn);
    static PlayerRemote* Deserialize(boost::property_tree::ptree playerNode);
  };

