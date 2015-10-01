#pragma once
#include "Position.h"
#include "Player.h"


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
protected:
	int m_ownerID;

private:
    Position m_position;

    int m_foodCost;
    int m_scienceCost;
    int m_weaponCost;

    double m_foodRatioBonus;
    double m_scienceRatioBonus;
    double m_weaponRatioBonus;

public:
    Actor(int ownerID, Position position = Position(-1,-1));
    ~Actor();

	void SetOwnerID(int ID);
	int GetOwnerID();

	virtual void NotifyNewTurn() = 0;
	virtual boost::property_tree::ptree Serialize() = 0;

};

