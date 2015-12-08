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
    m_buttons.clear(); // std::vector::clear() calls destructor for each element in the vector.
}

const std::vector<Button*>& ClickManager::GetButtons()
{
    return m_buttons;
}

void ClickManager::ManageMapClick(const Position& position)
{
    SelectionManager::GetInstance().HandleSelection(position);
}

void ClickManager::ManageMapRightClickPressed(const Position & position)
{
    SelectionManager::GetInstance().HandleRightClickPressed(position);
}

void ClickManager::ManageMapRightClickUnpressed(const Position & position)
{
    SelectionManager::GetInstance().HandleRightClickUnpressed(position);
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