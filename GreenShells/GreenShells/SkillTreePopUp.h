#pragma once
#include <vector>
#include "PopUpWindow.h"
class ButtonText;

class SkillTreePopUp
    : public PopUpWindow
{
private:
    std::vector<std::shared_ptr<ButtonText>> m_buttons;

public:
    SkillTreePopUp(const char* windowName, int width, int height);
    ~SkillTreePopUp();

    void ShowWindow(SDL_Renderer* rend);

    bool handleEvent(SDL_Event& e);
};