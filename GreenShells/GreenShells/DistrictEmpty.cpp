#include "DistrictEmpty.h"
#include <iostream>

DistrictEmpty::DistrictEmpty(int owner)
    : District<DistrictEmpty>(owner, 0, 0, 0, NAME, DISTRICT_TYPE)
{
}

std::shared_ptr<DistrictBase> DistrictEmpty::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictEmpty{ *this } };
}

void DistrictEmpty::ChangeOwner(int newOwner)
{
    assert(false && "Don't try to change the owner of an empty district");
}

void DistrictEmpty::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("Resources\\Sprite\\Districts\\64x64\\emptyDistrict.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool DistrictEmpty::CanUpgrade()
{
    assert(false && "Should be in an Empty District. It cannot be placed on the map");
    return false;
}

DistrictEmpty::~DistrictEmpty()
{
}

void DistrictEmpty::Repair(int repairValue)
{
    assert(false && "Should be in an Empty District. It cannot be placed on the map");
}

boost::property_tree::ptree DistrictEmpty::Serialize()
{
    assert(false && "Should never serialize an empty district. Don't add it to the map");
    return boost::property_tree::ptree();
}

AttackNotification DistrictEmpty::ReceiveDamage(int damage)
{
    assert(false && "Should never serialize an empty district. Don't add it to the map");
    return AttackNotification(0, false, false);
}
