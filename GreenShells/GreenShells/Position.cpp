#include "Position.h"
#include <sstream>

Position::Position(int x, int y)
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
