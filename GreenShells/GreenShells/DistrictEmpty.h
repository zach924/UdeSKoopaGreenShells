#pragma once
#include "District.h"

//IMPORTANT
//NOT TO BE PLACED IN MAP, FOR UI ONLY
class DistrictEmpty :
    public District<DistrictEmpty>
{
public:
    static const int DISTRICT_TYPE = -1;

    typedef District<DistrictEmpty> tBase;
    DistrictEmpty(int owner);
    ~DistrictEmpty();
    virtual DistrictBase* Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual bool CanUpgrade();

    virtual  boost::property_tree::ptree Serialize();
};
