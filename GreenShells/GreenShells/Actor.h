#include "Position.h"

#pragma once

namespace boost
{
    namespace property_tree
    {
        template < class Key, class Data, class KeyCompare >
        class basic_ptree;

        typedef basic_ptree< std::string, std::string, std::less<std::string> > ptree;
    }
}

class Actor
{
    Position m_position;

    int m_foodCost;
    int m_scienceCost;
    int m_weaponCost;

    double m_foodRatioBonus;
    double m_scienceRatioBonus;
    double m_weaponRatioBonus;

public:
    Actor();
    ~Actor();

    boost::property_tree::ptree Serialize();
};

