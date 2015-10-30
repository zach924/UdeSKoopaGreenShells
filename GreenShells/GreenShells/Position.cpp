#include "Position.h"
#include <sstream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif // _DEBUG

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif
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