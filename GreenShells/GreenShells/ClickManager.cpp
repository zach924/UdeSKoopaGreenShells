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
    for (auto button : m_buttons)
    {
        delete button;
        button = nullptr;
    }
}

void ClickManager::AddButton(Button* button)
{
    m_buttons.emplace_back(button);
}

void ClickManager::ClearButtons()
{
    m_buttons.clear();
}

const std::vector<Button*>& ClickManager::GetButtons()
{
    return m_buttons;
}

void ClickManager::ManageMapClick(const Position& position)
{
    //std::cout << "Map clicked at pos Column: " << position.Column << " Row: " << position.Row << std::endl;
    SelectionManager::GetInstance().HandleSelection(position);
}


void ClickManager::ManageMenuClick(const int & x, const int & y)
{
    for (Button* b : m_buttons)
    {
        if (b->IsInside(x, y))
        {
            if (b->IsUnpressed())
            {
                b->SetButtonState(ButtonState::Pressed);
                b->DoAction();
            }
            break;
        }
    }
}