#pragma once
#include "PopUpWindow.h"
#include "ButtonText.h"

class SpawnUnitPopUp :
    public PopUpWindow
{
private:
    ButtonText* m_allButtons[8];

public:
    SpawnUnitPopUp(const char* windowName, int width, int height);
    ~SpawnUnitPopUp();

    bool handleEvent(SDL_Event& e);
    void ShowWindow(SDL_Renderer * rend);
};

