#pragma once
#include "District.h"

//IMPORTANT
//NOT TO BE PLACED IN MAP, FOR UI ONLY
class DistrictEmpty :
    public District<DistrictEmpty>
{
public:
    typedef District<DistrictEmpty> tBase;
    DistrictEmpty(int owner);
    ~DistrictEmpty();
    virtual std::shared_ptr<DistrictBase> Clone();
    virtual void ChangeOwner(int newOwner);
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();
    virtual bool CanUpgrade();

    virtual  boost::property_tree::ptree Serialize();
};
