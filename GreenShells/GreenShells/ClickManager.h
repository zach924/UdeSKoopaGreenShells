#pragma once
#include <vector>
#include "Button.h"
class Position;

enum LeftMenuPart
{
    GeneralPart,
    UnitPart,
    DistrictPart
};

class ClickManager
{
    ClickManager(ClickManager const&) = delete;
    void operator=(ClickManager const&) = delete;

    ClickManager();
    ~ClickManager();

    std::vector<Button*> m_unitButtons;
    std::vector<Button*> m_districtButtons;
    std::vector<Button*> m_generalButtons;

public:
    static ClickManager& GetInstance()
    {
        static ClickManager m_instance;
        return m_instance;
    }

    void AddButton(Button* button, LeftMenuPart part);
	void CleatButtons();
    const std::vector<Button*>& GetUnitButtons();
    const std::vector<Button*>& GetDistrictButtons();
    const std::vector<Button*>& GetGeneralButtons();

    void ManageMapClick(const Position& position);
    void ManageLeftMenuClick(const int& x, const int& y);
    void ManageTopMenuClick(const int& x, const int& y);
};
