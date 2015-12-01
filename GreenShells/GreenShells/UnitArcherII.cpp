#include "UnitArcherII.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"

UnitArcherII::UnitArcherII(int owner, bool hasBonusActionPoint)
    : Unit<UnitArcherII>(owner, HEALTH, ACTION_POINTS, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE, UNIT_NAME, UNIT_TYPE, WEAPON_COST, NO_FOOD_COST, UPGRADE_TYPE)
{
    if (hasBonusActionPoint)
    {
        m_actionPointsLeft += 1;
    }
}

UnitArcherII::~UnitArcherII()
{
}

std::shared_ptr<UnitBase> UnitArcherII::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitArcherII{ *this } };
}

void UnitArcherII::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\bow2.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitArcherII::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GetOwnerID());
    return player->GetArmySkillTree().ArcherT3 && player->HasEnoughWeapons(GetWeaponCost());
}

std::shared_ptr<UnitArcherII> UnitArcherII::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitArcherII> archer = std::shared_ptr<UnitArcherII>{ new UnitArcherII(node.get<int>("<xmlattr>.O")) };
    archer->m_health = node.get<int>("<xmlattr>.H");
    archer->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return archer;
}