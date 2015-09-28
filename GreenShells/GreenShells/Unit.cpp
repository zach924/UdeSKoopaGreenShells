#include "Unit.h"

#include <boost\property_tree\ptree.hpp>


Unit::Unit()
{
}

Unit::~Unit()
{
}

boost::property_tree::ptree Unit::Serialize()
{
    boost::property_tree::ptree unitXml;
    unitXml.add("Unit", "");
    return unitXml;
}
