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

    void LoadTexture();

    virtual void Heal(int health);

    virtual  boost::property_tree::ptree Serialize();
};