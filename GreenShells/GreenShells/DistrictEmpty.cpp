#include "DistrictEmpty.h"
#include <iostream>

DistrictEmpty::DistrictEmpty(int owner)
    : District<DistrictEmpty>(owner, 0, 0)
{
}

DistrictBase* DistrictEmpty::Clone()
{
    return new DistrictEmpty{ *this };
}

void DistrictEmpty::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\emptyDistrict.bmp");
		std::cout << "Loading DISTRICT_EMPTY" << std::endl;


    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

int DistrictEmpty::GetTypeAsInt()
{
    assert(false && "Should be in an Empty District. It cannot be placed on the map");
    return -1;
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

int DistrictEmpty::GetMaxHealth()
{
	assert(false && "Should be in an Empty District. It cannot be placed on the map");
	return 0;
}

const char * DistrictEmpty::GetName()
{
	assert(false && "Should be in an Empty District. It cannot be placed on the map");
	return nullptr;
}

boost::property_tree::ptree DistrictEmpty::Serialize()
{
    assert(false && "Should never serialize an empty district. Don't add it to the map");
    return boost::property_tree::ptree();
}