#pragma once
#include "District.h"

class DistrictUniversity : public District<DistrictUniversity>
{
    static const int ATTACK_DAMAGE = 0;
    static const int HEALTH = 400;
    static const int VIEW_RANGE = 5;
    static constexpr char* NAME = "University";

public:
    typedef District<DistrictUniversity> tBase;
    static const int DISTRICT_TYPE = 13;
    static const int FOOD_COST = 1000;
    static constexpr double SCIENCE_BONUS = 0.1;

    DistrictUniversity(int owner);
    ~DistrictUniversity();
    virtual std::shared_ptr<DistrictBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    static std::shared_ptr<DistrictUniversity> Deserialize(boost::property_tree::ptree node);
};




