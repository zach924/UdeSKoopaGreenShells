#include "Position.h"
#include <sstream>

Position::Position(int x = -1, int y = -1)
	: X(x), Y(y)
{
}

Position::~Position()
{
}

std::string Position::ToString()
{
	std::stringstream ss;
	ss << "[ " << X << " ][ " << Y << " ]\n";
	return ss.str();
}
