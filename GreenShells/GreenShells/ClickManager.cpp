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
		m_unitButton.emplace_back(button);
		break;
	case Building:
		m_buildingButton.emplace_back(button);
		break;
	default:
		break;
	}
}

const std::vector<Button*>& ClickManager::GetUnitButton()
{
	return m_unitButton;
}

void ClickManager::ManageMapClick(const Position& position)
{
	std::cout << "Map clicked at pos X: " << position.X << " Y: " << position.Y << std::endl;
	SelectionManager::GetInstance().HandleSelection(position);
}

void ClickManager::ManageLeftMenuClick(const int & x, const int & y)
{
	for (Button* b : m_buildingButton)
	{
		if (b->IsInside(x, y))
		{
			b->DoAction();
			break;
		}
	}

	for (Button* b : m_unitButton)
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
