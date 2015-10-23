#include "Position.h"
#include <sstream>

Position::Position(int column, int row)
	: Column(column), Row(row)
{
}

Position::~Position()
{
}

std::string Position::ToString() const
{
	std::stringstream ss;
	ss << "[ " << Column << " ][ " << Row << " ]";
	return ss.str();
}