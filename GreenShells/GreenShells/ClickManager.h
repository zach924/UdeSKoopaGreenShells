#pragma once
#include <vector>
#include "Button.h"

class Position;

class ClickManager
{
    ClickManager(ClickManager const&) = delete;
    void operator=(ClickManager const&) = delete;

    ClickManager();
    ~ClickManager();

    std::vector<Button*> m_buttons;

public:
    static ClickManager& GetInstance()
    {
        static ClickManager m_instance;
        return m_instance;
    }

    void AddButton(Button* button);
	void ClearButtons();
    const std::vector<Button*>& GetButtons();

    void ManageMapClick(const Position& position);
    void ManageMenuClick(const int& x, const int& y);
};
