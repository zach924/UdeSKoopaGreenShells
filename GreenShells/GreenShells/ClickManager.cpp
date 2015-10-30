#include <iostream>
#include "ClickManager.h"
#include "SelectionManager.h"
#include "Position.h"

#include "ButtonUnitAttack.h"

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
        m_generalButtons.emplace_back(button);
		break;
	case UnitPart:
		m_unitButtons.emplace_back(button);
		break;
	case DistrictPart:
		m_districtButtons.emplace_back(button);
		break;
	default:
		break;
	}
}

const std::vector<Button*>& ClickManager::GetUnitButtons()
{
	return m_unitButtons;
}

const std::vector<Button*>& ClickManager::GetDistrictButtons()
{
    return m_districtButtons;
}

const std::vector<Button*>& ClickManager::GetGeneralButtons()
{
    return m_generalButtons;
}

void ClickManager::ManageMapClick(const Position& position)
{
	//std::cout << "Map clicked at pos Column: " << position.Column << " Row: " << position.Row << std::endl;
	SelectionManager::GetInstance().HandleSelection(position);
}

void ClickManager::ManageLeftMenuClick(const int & x, const int & y)
{
    for (Button* b : m_generalButtons)
    {
        if (b->IsInside(x, y))
        {
            if (b->IsUnpressed())
            {
                //TODO put in back to unpressed when appropriate
                b->SetButtonState(ButtonState::Pressed);
                b->DoAction();
            }
            break;
        }
    }

	for (Button* b : m_districtButtons)
	{
		if (b->IsInside(x, y))
		{
            if (b->IsUnpressed())
            {
                //TODO put in back to unpressed when appropriate
                b->SetButtonState(ButtonState::Pressed);
                b->DoAction();
            }
			break;
		}
	}

	for (Button* b : m_unitButtons)
	{
		if (b->IsInside(x, y))
		{
            if (b->IsUnpressed()) 
            {
                //TODO put in back to unpressed when appropriate
                b->SetButtonState(ButtonState::Pressed);
                b->DoAction();
            }
			break;
		}
	}
}

void ClickManager::ManageTopMenuClick(const int & x, const int & y)
{
	//TODO
}
