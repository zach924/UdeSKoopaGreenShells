#include "DistrictEmpty.h"
#include <iostream>

DistrictEmpty::DistrictEmpty(int owner)
    : District<DistrictEmpty>(owner, 0, 0)
{
}

void DistrictEmpty::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\emptyDistrict.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

int DistrictEmpty::GetTypeAsInt()
{
    assert(false && "Should no try to serialize an empty district. It cannot be placed on the map");
    return -1;
}

DistrictEmpty::~DistrictEmpty()
{
}

void DistrictEmpty::Repair(int repairValue)
{
    assert(false && "Should not try to repair an empty district");
}

boost::property_tree::ptree DistrictEmpty::Serialize()
{
    assert(false && "Should never serialize an empty district. Don't add it to the map");
    return boost::property_tree::ptree();
}