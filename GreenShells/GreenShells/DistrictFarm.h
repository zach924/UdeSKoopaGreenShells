#pragma once
#include "District.h"

class DistrictFarm : public District<DistrictFarm>
{
public:
    typedef District<DistrictFarm> tBase;
    static const int DISTRICT_TYPE = 1;

    static const int HEALTH = 75;

public:
    DistrictFarm(int owner);
    ~DistrictFarm();
    virtual DistrictBase* Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);

    virtual int GetTypeAsInt();

    static DistrictFarm* Deserialize(boost::property_tree::ptree node);
};