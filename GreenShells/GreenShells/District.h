#pragma once
#include "DistrictBase.h"
#include "Texture.h"
#include <boost\property_tree\ptree.hpp>

template<class T>
class District : public DistrictBase
{
public:
    static Texture m_Texture;
    static bool m_forceLoading;
    void LoadTexture() {};

    virtual int GetTypeAsInt() = 0;

public:
    District(int ownerID, int health, int attackDamage, int viewRange, int foodCost = 0, int weaponYield = 0, int foodYield = 0, int scienceYield = 0)
        : DistrictBase(ownerID, health, attackDamage, viewRange, foodCost, weaponYield, foodYield, scienceYield)
    {
    }

    ~District()
    {
    }

    virtual DistrictBase* Clone() = 0;

    virtual District* Deserialize(boost::property_tree::ptree tileNode, Position pos = Position(-1, 0))
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
