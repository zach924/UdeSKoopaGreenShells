#include "UnitAxeman.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"

const char* UnitAxeman::UNIT_NAME = "Axeman";

UnitAxeman::UnitAxeman(int owner)
    : Unit<UnitAxeman>(owner, HEALTH, MOVE_RANGE, ATTACK_RANGE, ATTACK_DAMAGE)
{
}

UnitAxeman::~UnitAxeman()
{
}

UnitBase* UnitAxeman::Clone()
{
    return new UnitAxeman{ *this };
}

void UnitAxeman::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\axe.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitAxeman::CanUpgrade()
{
    Player* player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
    return player->GetArmySkillTree().AxeT2;
}

int UnitAxeman::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitAxeman::GetName()
{
    return UNIT_NAME;
}

int UnitAxeman::GetTypeAsInt()
{
    return UNIT_TYPE;
}

void UnitAxeman::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

UnitAxeman * UnitAxeman::Deserialize(boost::property_tree::ptree node)
{
    UnitAxeman* axeman = new UnitAxeman(node.get<int>("<xmlattr>.O"));
    axeman->m_health = node.get<int>("<xmlattr>.H");

    return axeman;
}