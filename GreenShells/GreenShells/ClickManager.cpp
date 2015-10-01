#include "ClickManager.h"
#include "SelectionManager.h"
#include "Position.h"


ClickManager::ClickManager()
{
}


ClickManager::~ClickManager()
{
}

void ClickManager::ManageMapClick(const Position& position)
{
	SelectionManager::GetInstance().HandleSelection(position);
}

void ClickManager::ManageLeftMenuClick(const int & x, const int & y)
{
	//TODO
}

void ClickManager::ManageTopMenuClick(const int & x, const int & y)
{
	//TODO
}
