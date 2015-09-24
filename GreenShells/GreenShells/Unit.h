#pragma once

#include "Actor.h"


class Unit : public Actor
{
public:
    Unit();
    ~Unit();

    boost::property_tree::ptree Serialize();
};

