#pragma once
#include "District.h"

//IMPORTANT
//NOT TO BE PLACED IN MAP, FOR UI ONLY
class DistrictEmpty :
    public District<DistrictEmpty>
{
    static constexpr char* NAME = "EMPTY_DISTRICT";

public:
    static const int DISTRICT_TYPE = -1;

    typedef District<DistrictEmpty> tBase;
    DistrictEmpty(int owner);
    ~DistrictEmpty();
    virtual std::shared_ptr<DistrictBase> Clone();
    virtual void ChangeOwner(int newOwner);
    virtual void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();
    virtual boost::property_tree::ptree Serialize();
    virtual AttackNotification ReceiveDamage(int damage);
};
