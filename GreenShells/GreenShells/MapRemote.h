#pragma once
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include "Map.h"
#include "RPCBase.h"

class MapRemote : public Map, public RPCBase
{
private:
	//Serialize
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		boost::serialization::base_object<Map>(*this);
	}

public:
	MapRemote();
	~MapRemote();

	virtual bool MoveUnit(int ownerID, Position unitLocation, Position newLocation);

    static MapRemote* Deserialize(boost::property_tree::ptree mapNode);
};
