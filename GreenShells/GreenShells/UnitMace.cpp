#include "UnitMace.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"

const char* UnitMace::UNIT_NAME = "Mace";

UnitMace::UnitMace(int owner)
    : Unit<UnitMace>(owner, HEALTH, MOVE_RANGE, ATTACK_RANGE, ATTACK_DAMAGE)
{
}

UnitMace::~UnitMace()
{
}

UnitBase* UnitMace::Clone()
{
    return new UnitMace{ *this };
}

void UnitMace::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\mace.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitMace::CanUpgrade()
{
    Player* player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
    return player->GetArmySkillTree().MaceT2;
}

int UnitMace::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitMace::GetName()
{
    return UNIT_NAME;
}

int UnitMace::GetTypeAsInt()
{
    return UNIT_TYPE;
}

void UnitMace::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

UnitMace * UnitMace::Deserialize(boost::property_tree::ptree node)
{
    UnitMace* mace = new UnitMace(node.get<int>("<xmlattr>.O"));
    mace->m_health = node.get<int>("<xmlattr>.H");

    return mace;
}