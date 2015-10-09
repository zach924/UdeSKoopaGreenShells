#include <iostream>
#include "ClickManager.h"
#include "SelectionManager.h"
#include "Position.h"

#include "ButtonUnitAttack.h"


ClickManager::ClickManager()
{
}


ClickManager::~ClickManager()
{
}



void ClickManager::AddButton(Button* button, LeftMenuPart part)
{
	switch (part)
	{
	case GeneralPart:
		break;
	case UnitPart:
		m_unitButtons.emplace_back(button);
		break;
	case BuildingPart:
		m_buildingButtons.emplace_back(button);
		break;
	default:
		break;
	}
}

const std::vector<Button*>& ClickManager::GetUnitButton()
{
	return m_unitButtons;
}

void ClickManager::ManageMapClick(const Position& position)
{
	//std::cout << "Map clicked at pos X: " << position.X << " Y: " << position.Y << std::endl;
	SelectionManager::GetInstance().HandleSelection(position);
}

void ClickManager::ManageLeftMenuClick(const int & x, const int & y)
{
	for (Button* b : m_buildingButtons)
	{
		if (b->IsInside(x, y))
		{
			b->DoAction();
			break;
		}
	}

	for (Button* b : m_unitButtons)
	{
		if (b->IsInside(x, y))
		{
			b->DoAction();
			break;
		}
	}
}

void ClickManager::ManageTopMenuClick(const int & x, const int & y)
{
	//TODO
}
