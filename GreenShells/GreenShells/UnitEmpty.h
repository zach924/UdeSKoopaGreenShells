#pragma once
#include "Unit.h"

//IMPORTANT
//NOT TO BE PLACED IN MAP, FOR UI ONLY
class UnitEmpty : public Unit<UnitEmpty>
{
public:
    typedef Unit<UnitEmpty> tBase;

public:
    UnitEmpty(int owner);
    ~UnitEmpty();
    virtual UnitBase* Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual void Heal(int health);
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();
    virtual int GetUnitTier();

    virtual  boost::property_tree::ptree Serialize();
};