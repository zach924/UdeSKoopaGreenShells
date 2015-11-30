#pragma once
#include "PopUpWindow.h"
#include "ButtonText.h"

class ConstructDistrictPopUp :
    public PopUpWindow
{
private:
    std::vector<ButtonText> m_allButtons;

public:
    ConstructDistrictPopUp(const char* windowName, int width, int height);
    ~ConstructDistrictPopUp();

    bool handleEvent(SDL_Event& e);
    void ShowWindow(SDL_Renderer * rend);
};


