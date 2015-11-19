#pragma once
#include "PopUpWindow.h"
#include "ButtonText.h"

class ConstructDistrictPopUp :
    public PopUpWindow
{
private:
    ButtonText* m_allButtons[7];

public:
    ConstructDistrictPopUp(const char* windowName, int width, int height);
    ~ConstructDistrictPopUp();

    bool handleEvent(SDL_Event& e);
    void ShowWindow(SDL_Renderer * rend);
};


