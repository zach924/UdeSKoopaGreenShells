#include "UnitArcherII.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"

const char* UnitArcherII::UNIT_NAME = "Archer MK2";

UnitArcherII::UnitArcherII(int owner)
    : Unit<UnitArcherII>(owner, HEALTH, MOVE_RANGE, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE)
{
}

UnitArcherII::~UnitArcherII()
{
}

UnitBase* UnitArcherII::Clone()
{
    return new UnitArcherII{ *this };
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
    Player* player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
    return player->GetArmySkillTree().RangerT3;
}

int UnitArcherII::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitArcherII::GetName()
{
    return UNIT_NAME;
}

int UnitArcherII::GetTypeAsInt()
{
    return UNIT_TYPE;
}

int UnitArcherII::GetViewRange()
{
    return VIEW_RANGE;
}

void UnitArcherII::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

UnitArcherII * UnitArcherII::Deserialize(boost::property_tree::ptree node)
{
    UnitArcherII* archer = new UnitArcherII(node.get<int>("<xmlattr>.O"));
    archer->m_health = node.get<int>("<xmlattr>.H");

    return archer;
}