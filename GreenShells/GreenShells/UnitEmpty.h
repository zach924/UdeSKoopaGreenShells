#pragma once
#include "Unit.h"

//IMPORTANT
//NOT TO BE PLACED IN MAP, FOR UI ONLY
class UnitEmpty : public Unit<UnitEmpty>
{
    static constexpr char* UNIT_NAME = "Unit_Empty";

public:
    typedef Unit<UnitEmpty> tBase;
    static const int UNIT_TYPE = -1;
    
    UnitEmpty(int owner);
    ~UnitEmpty();
    virtual std::shared_ptr<UnitBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    virtual  boost::property_tree::ptree Serialize();
    virtual AttackNotification Attack(std::shared_ptr<UnitBase> target);
    virtual AttackNotification Attack(std::shared_ptr<DistrictBase> target);
};