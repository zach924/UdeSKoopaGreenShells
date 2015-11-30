#pragma once
#include "PopUpWindow.h"
#include "ButtonText.h"

class SpawnUnitPopUp :
    public PopUpWindow
{
private:
    std::vector<ButtonText> m_allButtons;

public:
    SpawnUnitPopUp(const char* windowName, int width, int height);
    ~SpawnUnitPopUp();

    bool handleEvent(SDL_Event& e);
    void ShowWindow(SDL_Renderer * rend);
};

