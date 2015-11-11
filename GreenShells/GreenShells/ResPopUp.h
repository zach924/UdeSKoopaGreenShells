#pragma once
#include "PopUpWindow.h"
#include "ButtonResSelect.h"
#include "ButtonQuit.h"
#include "ButtonSave.h"

class ResPopUp :
    public PopUpWindow
{
private:

    ButtonResSelect* m_allResButtons [5];
    ButtonQuit * m_quitButton;
    ButtonSave * m_saveButton;

public:
    ResPopUp(const char* windowName, int width, int height);
    ~ResPopUp();

    void ShowWindow(SDL_Renderer* rend);

    bool handleEvent(SDL_Event& e);
    void RenderButton(Button* button);

};

