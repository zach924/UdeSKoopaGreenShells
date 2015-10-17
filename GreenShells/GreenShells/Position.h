#pragma once
#include <boost/serialization/access.hpp>
#include <string>

class Position
{
private:
	//Serialize
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & X;
		ar & Y;
	}
public:
	
	int X;
	int Y;

	Position(int x = -1, int y = -1);
	~Position();
	std::string ToString() const;

	friend std::ostream& operator<<(std::ostream& os, const Position& obj)
	{
		os << obj.ToString();
		return os;
	}
};