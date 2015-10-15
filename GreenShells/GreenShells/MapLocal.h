#pragma once
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include "Map.h"

class MapLocal : public Map
{
private:
	//Serialize
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		boost::serialization::base_object<MapLocal>(*this)
	}

public:
	MapLocal();
	~MapLocal();

	virtual bool MoveUnit(int ownerID, Position unitLocation, Position newLocation);

    static MapLocal* Deserialize(boost::property_tree::ptree mapNode);
};
