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
    virtual DistrictBase* Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual int GetTypeAsInt();

    virtual  boost::property_tree::ptree Serialize();
};
