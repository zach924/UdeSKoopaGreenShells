#include "Actor.h"
#pragma once
class District : public Actor
{
public:
	District();
	~District();

    boost::property_tree::ptree Serialize();
};

