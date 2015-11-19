#pragma once
#include "UnitBase.h"
#include "Texture.h"
#include <boost\property_tree\ptree.hpp>

template<class T>
class Unit : public UnitBase
{
public:
    static Texture m_Texture;
    void LoadTexture() {};
    static bool m_forceLoading;
    virtual int GetTypeAsInt() = 0;
    virtual int GetUnitTier() = 0;

public:
    Unit(int ownerID, int health, int moveRange, int attackRange, int attackDamage, int viewRange)
        : UnitBase(ownerID, health, moveRange, attackRange, attackDamage, viewRange)
    {
    }

    ~Unit()
    {
    }

    virtual UnitBase* Clone() = 0;

    virtual Unit* Deserialize(boost::property_tree::ptree tileNode, Position pos = Position(-1, 0))
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