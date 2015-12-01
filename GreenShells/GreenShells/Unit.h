#pragma once
#include "UnitBase.h"
#include "Texture.h"
#include <boost\property_tree\ptree.hpp>

template<class T>
class Unit : public UnitBase
{
public:
    static Texture m_Texture;
    virtual void LoadTexture() {};
    static bool m_forceLoading;

public:
    Unit(int ownerID, int health, int actionPoints, int attackRange, int attackDamage, int viewRange, const char* name, int typeAsInt, int weaponCost = -1, int foodCost = -1, int upgradeType = NO_UPGRADE)
        : UnitBase(ownerID, health, actionPoints, attackRange, attackDamage, viewRange, name, typeAsInt, weaponCost, foodCost, upgradeType)
    {
    }

    ~Unit()
    {
    }

    virtual std::shared_ptr<UnitBase> Clone() = 0;

    virtual std::shared_ptr<Unit> Deserialize(boost::property_tree::ptree tileNode, Position pos = Position(-1, 0))
    {
        return nullptr;
    }

    //Every method must be define in header file because of the static polymorphism
    Texture* GetTexture()
    {
        if (!m_Texture.IsLoaded() || m_forceLoading)
        {
            static_cast<T*>(this)->LoadTexture();
            m_forceLoading = false;
        }
        return &m_Texture;
    }

    static void ForceReload()
    {
        m_forceLoading = true;
    }
};