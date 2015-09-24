#include "District.h"

#include <boost\property_tree\ptree.hpp>


District::District()
{
}

District::~District()
{
}

boost::property_tree::ptree District::Serialize()
{
    boost::property_tree::ptree districtNode;

    return districtNode;
}