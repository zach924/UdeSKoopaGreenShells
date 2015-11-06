#pragma once
#include "PopUpWindow.h"

class SkillTreePopUp
    : public PopUpWindow
{

public:

    SkillTreePopUp(const char* windowName, int width, int height);
    ~SkillTreePopUp();

    void ShowWindow(SDL_Renderer* rend);

    bool handleEvent(SDL_Event& e);
};