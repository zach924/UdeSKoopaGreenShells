#pragma once
#include <vector>
#include "PopUpWindow.h"
class ButtonText;

class SkillTreePopUp
    : public PopUpWindow
{
private:
    const int HEADER_HEIGHT = 100;
    const int COST_WIDTH = 100;
    const int BUTTON_HEIGHT = 50;
    const int BUTTON_WIDTH = 130;
    int m_colomnWidth;
    int m_rowHeight;
    int m_heightSpacer;
    int m_widthSpace;
    std::shared_ptr<ButtonText> m_closeButton;
    std::vector<std::shared_ptr<ButtonText>> m_buttons;

    void ShowButton(std::shared_ptr<ButtonText> button);

public:
    SkillTreePopUp(const char* windowName, int width, int height);
    ~SkillTreePopUp();

    void ShowWindow(SDL_Renderer* rend);

    bool handleEvent(SDL_Event& e);
};