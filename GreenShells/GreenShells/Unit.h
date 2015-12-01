#pragma once
#include "UnitBase.h"
#include "Texture.h"
#include <iostream>
#include <boost\property_tree\ptree.hpp>

template<class T>
class Unit : public UnitBase
{
public:
    static Texture m_unitTexture;
    static Texture m_boatTexture;
    virtual void LoadTexture() {};
    static bool m_forceLoading;

public:
    Unit(int ownerID, int health, int actionPoints, int attackRange, int attackDamage, int viewRange, const char* name, int typeAsInt, int weaponCost = 0, int upgradeType = NO_UPGRADE, int foodCost = 0)
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
    Texture* GetUnitTexture()
    {
        if (m_forceLoading)
        {
            ReloadTextures();
        }
        else if (!m_unitTexture.IsLoaded())
        {
            static_cast<T*>(this)->LoadTexture();
        }

        return &m_unitTexture;
    }

    //Every method must be define in header file because of the static polymorphism
    Texture* GetBoatTexture()
    {
        if (m_forceLoading)
        {
            ReloadTextures();

        }
        else if (!m_boatTexture.IsLoaded())
        {
            try
            {
                m_boatTexture.LoadFromFile("..\\Sprite\\Units\\64x64\\boat.bmp");
            }
            catch (std::exception e)
            {
                std::string msg{ e.what() };
                std::cout << msg << std::endl;
            }
        }
        return &m_boatTexture;
    }

    static void ForceReload()
    {
        m_forceLoading = true;
    }

private:
    void ReloadTextures()
    {
        m_forceLoading = false;
        static_cast<T*>(this)->LoadTexture();

        try
        {
            m_boatTexture.LoadFromFile("..\\Sprite\\Units\\64x64\\boat.bmp");
        }
        catch (std::exception e)
        {
            std::string msg{ e.what() };
            std::cout << msg << std::endl;
        }
    }
};