#include "GameSession.h"
#include <iostream>
#include "DistrictFort.h"
#include "Player.h"
#include "Map.h"
#include "DistrictFortress.h"

DistrictFort::DistrictFort(int owner)
    : District<DistrictFort>(owner, HEALTH, ATTACK_DAMAGE, VIEW_RANGE, NAME, DISTRICT_TYPE, FOOD_COST, WEAPON_YIELD, FOOD_YIELD, SCIENCE_YIELD)
{
}

std::shared_ptr<DistrictBase> DistrictFort::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictFort{ *this } };
}

void DistrictFort::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\fort.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictFort::~DistrictFort()
{
}

bool DistrictFort::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GetOwnerID());
    return player->GetArmySkillTree().Fortress && player->HasEnoughFood(GetFoodCost());
}

void DistrictFort::Upgrade(Map * map)
{
    map->GetTile(GetPosition())->SetDistrict(std::shared_ptr<DistrictBase>{new DistrictFortress(GetOwnerID())});
}

std::shared_ptr<DistrictFort> DistrictFort::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictFort>{ new DistrictFort(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}

